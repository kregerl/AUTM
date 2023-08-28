#include <Core/Log.h>
#include "Framebuffer.h"

#include <glad/glad.h>

Framebuffer::Framebuffer(const FramebufferSpecification& specification) {
    // TODO: Depth attachments
    for (auto spec: specification.attachments) {
        m_color_attachment_specifications.emplace_back(spec);
    }
    invalidate();
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_renderer_id);
    glDeleteTextures((GLsizei) m_color_attachments.size(), m_color_attachments.data());
}

void Framebuffer::invalidate() {
    if (m_renderer_id) {
        glDeleteFramebuffers(1, &m_renderer_id);
        glDeleteTextures((GLsizei) m_color_attachments.size(), m_color_attachments.data());

        m_color_attachments.clear();
    }
    glCreateFramebuffers(1, &m_renderer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);

    bool multisampling = m_specification.samples > 1;

    if (!m_color_attachment_specifications.empty()) {
        m_color_attachments.resize(m_color_attachment_specifications.size());
        auto texture_type = multisampling ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
        glCreateTextures(texture_type, (GLsizei) m_color_attachments.size(), m_color_attachments.data());
        for (uint32_t i = 0; i < m_color_attachments.size(); i++) {
            glBindTexture(texture_type, m_color_attachments[i]);

            switch (m_color_attachment_specifications.at(i).texture_format) {
                case FramebufferTextureSpecification::TextureFormat::RGBA8: {
                    if (multisampling) {
                        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,
                                                (GLsizei) m_specification.samples, GL_RGBA8,
                                                (GLsizei) m_specification.width, (GLsizei) m_specification.height,
                                                GL_FALSE);
                    } else {
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
                                     (GLsizei) m_specification.width,
                                     (GLsizei) m_specification.height,
                                     0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                    }

                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, texture_type,
                                           m_color_attachments[i], 0);
                    break;
                }
                default: break;
            }
        }

        if (m_color_attachments.size() > 1) {
            ASSERT(m_color_attachments.size() <= 4, "Too many color attachments");
            GLenum buffers[4] = {
                    GL_COLOR_ATTACHMENT0,
                    GL_COLOR_ATTACHMENT1,
                    GL_COLOR_ATTACHMENT2,
                    GL_COLOR_ATTACHMENT3
            };
            glDrawBuffers((GLsizei) m_color_attachments.size(), buffers);
        } else if (m_color_attachments.empty()) {
            glDrawBuffer(GL_NONE);
        }
        ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");
        glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);
    }
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_renderer_id);
    glViewport(0, 0, (GLsizei) m_specification.width, (GLsizei) m_specification.height);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::resize(uint32_t width, uint32_t height) {
    constexpr uint32_t max_size = 8192;
    if (width == 0 || height == 0 || width > max_size || height > max_size) {
        AUTM_WARN("Invalid attempt to resize framebuffer to ({}, {})", width, height);
        return;
    }
    invalidate();
}

void Framebuffer::clear_attachments(uint32_t attachment_index, int value) {
    ASSERT(attachment_index < m_color_attachments.size(), "Index out of bounds for color attachments");

    auto& spec = m_color_attachment_specifications.at(attachment_index);
    uint32_t texture_type = 0;
    switch (spec.texture_format) {
        case FramebufferTextureSpecification::TextureFormat::RGBA8: {
            texture_type = GL_RGBA8;
            break;
        }
        default: break;
    }
    glClearTexImage(m_color_attachments[attachment_index], 0, texture_type, GL_INT, &value);
}


