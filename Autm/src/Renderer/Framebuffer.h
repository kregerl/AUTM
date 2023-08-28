#ifndef AUTM_FRAMEBUFFER_H
#define AUTM_FRAMEBUFFER_H

#include "autmpch.h"
#include <glm/glm.hpp>
#include <Core/Assert.h>

struct FramebufferTextureSpecification {
    enum class TextureFormat {
        None = 0,
        RGBA8
    };

    FramebufferTextureSpecification() = default;

    explicit FramebufferTextureSpecification(TextureFormat texture_format) : texture_format(texture_format) {}

    TextureFormat texture_format = TextureFormat::None;
};

struct FramebufferSpecification {
    uint32_t width = 0, height = 0;
    std::vector<FramebufferTextureSpecification> attachments;
    uint32_t samples;
};

class Framebuffer {
public:
    explicit Framebuffer(const FramebufferSpecification& specification);

    ~Framebuffer();

    void invalidate();

    void bind();

    void unbind();

    void resize(uint32_t width, uint32_t height);

    void resize(const glm::ivec2& size) { resize(size.x, size.y); }

    void clear_attachments(uint32_t attachment_index, int value);

    [[nodiscard]] uint32_t get_color_attachment_id(uint32_t index = 0) const {
        ASSERT(index < m_color_attachments.size(), "Index out of bounds for framebuffer color attachments.");
        return m_color_attachments.at(index);
    }

    [[nodiscard]] const FramebufferSpecification& get_specification() const { return m_specification; }

private:
    uint32_t m_renderer_id = 0;
    FramebufferSpecification m_specification;
    std::vector<FramebufferTextureSpecification> m_color_attachment_specifications;
    std::vector<uint32_t> m_color_attachments;
};


#endif //AUTM_FRAMEBUFFER_H
