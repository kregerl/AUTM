#ifndef AUTM_FRAMEBUFFER_H
#define AUTM_FRAMEBUFFER_H

#include "autmpch.h"
#include <glm/glm.hpp>
#include <Core/Assert.h>


struct FramebufferTextureSpecification {
    enum class TextureFormat {
        None = 0,

        // Color
        RGBA8,
        RED_INTEGER,

        // Depth/stencil
        DEPTH24STENCIL8,

        // Defaults
        Depth = DEPTH24STENCIL8
    };

    FramebufferTextureSpecification() = default;

    explicit FramebufferTextureSpecification(TextureFormat format)
            : texture_format(format) {}

    TextureFormat texture_format = TextureFormat::None;
};

struct FramebufferAttachmentSpecification {
    FramebufferAttachmentSpecification() = default;

    explicit FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
            : attachments(attachments) {}

    std::vector<FramebufferTextureSpecification> attachments;
};

struct FramebufferSpecification {
    uint32_t width = 0, height = 0;
    FramebufferAttachmentSpecification attachments;
    uint32_t samples = 1;
};

class Framebuffer {
public:
    explicit Framebuffer(FramebufferSpecification spec);

    ~Framebuffer();

    void invalidate();

    void bind();

    void unbind();

    void resize(uint32_t width, uint32_t height, bool preserve_attachments = false);

//    int ReadPixel(uint32_t attachmentIndex, int x, int y);

    void clear_attachment(uint32_t attachmentIndex, int value);

    uint32_t get_color_attachment_id(uint32_t index = 0) const;

    void bind_color_attachment_id(uint32_t index = 0) const;

    void set_color_attachment_id(uint32_t index, uint32_t value);

    const FramebufferSpecification& get_specification() const { return m_specification; }

private:
    uint32_t m_renderer_id = 0;
    FramebufferSpecification m_specification;

    std::vector<FramebufferTextureSpecification> m_color_attachment_specifications;
    FramebufferTextureSpecification m_depth_attachment_specification = FramebufferTextureSpecification(
            FramebufferTextureSpecification::TextureFormat::None);

    std::vector<uint32_t> m_color_attachments;
    uint32_t m_depth_attachment = 0;
};

#endif //AUTM_FRAMEBUFFER_H
