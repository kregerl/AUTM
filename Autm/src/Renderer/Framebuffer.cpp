#include "Framebuffer.h"

#include <glad/glad.h>
#include <Core/Log.h>


Framebuffer::Framebuffer(FramebufferSpecification spec) : m_specification(std::move(spec)) {
    for (auto attachment_spec: m_specification.attachments.attachments) {
        if (attachment_spec.texture_format != FramebufferTextureSpecification::TextureFormat::DEPTH24STENCIL8) {
            m_color_attachment_specifications.emplace_back(attachment_spec);
        } else {
            m_depth_attachment_specification = attachment_spec;
        }
    }

    invalidate();
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_renderer_id);
    glDeleteTextures((GLsizei) m_color_attachments.size(), m_color_attachments.data());
    glDeleteTextures(1, &m_depth_attachment);
}

static void attach_color_texture(uint32_t id, uint32_t samples, GLenum internalFormat, GLenum format, uint32_t width,
                                 uint32_t height, uint32_t index) {
    bool multisample = samples > 1;
    if (multisample) {
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, (GLsizei) samples, internalFormat, (GLsizei) width,
                                (GLsizei) height, GL_FALSE);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, (GLsizei) internalFormat, (GLsizei) width, (GLsizei) height, 0, format,
                     GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index,
                           multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, id, 0);
}

static void attach_depth_texture(uint32_t id, uint32_t samples, GLenum format, GLenum attachmentType, uint32_t width,
                                 uint32_t height) {
    bool multisample = samples > 1;
    if (multisample) {
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, (GLsizei) samples, format, (GLsizei) width, (GLsizei) height,
                                GL_FALSE);
    } else {
        glTexStorage2D(GL_TEXTURE_2D, 1, format, (GLsizei) width, (GLsizei) height);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, id,
                           0);
}


void Framebuffer::invalidate() {
    if (m_renderer_id) {
        glDeleteFramebuffers(1, &m_renderer_id);
        glDeleteTextures((GLsizei) m_color_attachments.size(), m_color_attachments.data());
        glDeleteTextures(1, &m_depth_attachment);

        m_color_attachments.clear();
        m_depth_attachment = 0;
    }

    glCreateFramebuffers(1, &m_renderer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);

    bool multisample = m_specification.samples > 1;
    GLsizei texture_type = multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;

    if (!m_color_attachment_specifications.empty()) {
        m_color_attachments.resize(m_color_attachment_specifications.size());
        glCreateTextures(texture_type, (GLsizei) m_color_attachments.size(),
                         m_color_attachments.data());

        for (size_t i = 0; i < m_color_attachments.size(); i++) {
            glBindTexture(texture_type, m_color_attachments[i]);
            switch (m_color_attachment_specifications[i].texture_format) {
                case FramebufferTextureSpecification::TextureFormat::RGBA8: {
                    attach_color_texture(m_color_attachments[i], m_specification.samples, GL_RGBA8, GL_RGBA,
                                         m_specification.width, m_specification.height, i);
                    break;
                }
                case FramebufferTextureSpecification::TextureFormat::RED_INTEGER: {
                    attach_color_texture(m_color_attachments[i], m_specification.samples, GL_R32I, GL_RED_INTEGER,
                                         m_specification.width, m_specification.height, i);
                    break;
                }
                default:break;
            }
        }
    }

    if (m_depth_attachment_specification.texture_format != FramebufferTextureSpecification::TextureFormat::None) {
        glCreateTextures(texture_type, 1, &m_depth_attachment);
        glBindTexture(texture_type, m_depth_attachment);
        switch (m_depth_attachment_specification.texture_format) {
            case FramebufferTextureSpecification::TextureFormat::DEPTH24STENCIL8:
                attach_depth_texture(m_depth_attachment, m_specification.samples, GL_DEPTH24_STENCIL8,
                                     GL_DEPTH_STENCIL_ATTACHMENT, m_specification.width, m_specification.height);
                break;
            default: break;
        }
    }


    if (m_color_attachments.size() > 1) {
        ASSERT(m_color_attachments.size() <= 4, "Framebuffer must have at 4 or less color attachments.");
        GLenum buffers[4] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
        glDrawBuffers((GLsizei) m_color_attachments.size(), buffers);
    } else if (m_color_attachments.empty()) {
        // Only depth-pass
        glDrawBuffer(GL_NONE);
    }
    ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete.");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);
    glViewport(0, 0, (GLsizei) m_specification.width, (GLsizei) m_specification.height);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::resize(uint32_t width, uint32_t height) {
    constexpr uint32_t max_framebuffer_size = 8192;
    if (width == 0 || height == 0 || width > max_framebuffer_size || height > max_framebuffer_size) {
        AUTM_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
        return;
    }
    m_specification.width = width;
    m_specification.height = height;

    invalidate();
}

void Framebuffer::clear_attachment(uint32_t attachmentIndex, int value) {
    ASSERT(attachmentIndex < m_color_attachments.size(),
           "Attachment index out of bounds for framebuffer color attachments.");

    auto& spec = m_color_attachment_specifications[attachmentIndex];
    GLsizei format = GL_NONE;
    switch (spec.texture_format) {
        case FramebufferTextureSpecification::TextureFormat::RGBA8: {
            format = GL_RGBA8;
            break;
        }
        case FramebufferTextureSpecification::TextureFormat::RED_INTEGER: {
            format = GL_RED_INTEGER;
            break;
        }
        default: break;
    }
    glClearTexImage(m_color_attachments[attachmentIndex], 0,
                    format, GL_INT, &value);
}

uint32_t Framebuffer::get_color_attachment_id(uint32_t index) const {
    ASSERT(index < m_color_attachments.size(), "Index out of bounds for framebuffer color attachments");
    return m_color_attachments[index];
}

void Framebuffer::bind_color_attachment_id(uint32_t index) const {
    ASSERT(index < m_color_attachments.size(), "Index out of bounds for framebuffer color attachments");
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_color_attachments[index]);
}

void Framebuffer::set_color_attachment_id(uint32_t index, uint32_t value) {
    ASSERT(index < m_color_attachments.size(), "Index out of bounds for framebuffer color attachments");
    m_color_attachments[index] = value;
    glBindTexture(GL_TEXTURE_2D, m_color_attachments[index]);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_color_attachments[index], 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


