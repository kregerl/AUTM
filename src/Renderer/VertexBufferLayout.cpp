#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout(const std::initializer_list<VertexBufferElement> &elements)
        : m_elements(elements) {
    computeStrideAndOffsets();
}

const std::vector<VertexBufferElement> &VertexBufferLayout::getElements() const {
    return m_elements;
}

void VertexBufferLayout::computeStrideAndOffsets() {
    size_t offset = 0;
    m_stride = 0;
    for (auto &element: m_elements) {
        element.offset = offset;
        offset += element.size;
        m_stride += element.size;
    }
}

size_t VertexBufferLayout::getStride() const {
    return m_stride;
}
