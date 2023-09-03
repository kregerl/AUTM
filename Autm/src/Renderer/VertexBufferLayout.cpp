#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout(const std::initializer_list<VertexBufferElement> &elements)
        : m_elements(elements) {
    compute_stride_and_offset();
}

const std::vector<VertexBufferElement> &VertexBufferLayout::get_elements() const {
    return m_elements;
}

void VertexBufferLayout::compute_stride_and_offset() {
    size_t offset = 0;
    m_stride = 0;
    for (auto &element: m_elements) {
        element.offset = offset;
        offset += element.size;
        m_stride += element.size;
    }
}

size_t VertexBufferLayout::get_stride() const {
    return m_stride;
}
