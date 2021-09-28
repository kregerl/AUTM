#include "Renderer2D.h"
#include "RenderSystem.h"
#include "Texture2D.h"

#include <ext/matrix_transform.hpp>


struct RendererData {
    glm::mat4 viewProjectionMatrix;
    std::shared_ptr<VertexArray> quadVertexArray;
    std::shared_ptr<VertexArray> lineVertexArray;
    std::shared_ptr<Shader> textureShader;
    std::shared_ptr<Shader> lineShader;
    std::shared_ptr<Texture2D> arrowTexture;
    std::shared_ptr<Texture2D> whiteTexture;
};


static RendererData s_data;

// TODO: Switch this to a batched renderer instead
void Renderer2D::init() {
    s_data.arrowTexture = std::make_shared<Texture2D>(
            R"(C:\Users\kregerl\CLionProjects\Autm\assets\images\play32xwhite.png)");

    s_data.whiteTexture = std::make_shared<Texture2D>(1, 1);
    int white = 0xFFFFFFFF;
    s_data.whiteTexture->setData(sizeof(int), &white);

    s_data.textureShader = std::make_shared<Shader>(
            R"(C:\Users\kregerl\CLionProjects\Autm\assets\shaders\TextureVertex.glsl)",
            R"(C:\Users\kregerl\CLionProjects\Autm\assets\shaders\TextureFragment.glsl)");

    s_data.lineShader = std::make_shared<Shader>(
            R"(C:\Users\kregerl\CLionProjects\Autm\assets\shaders\FlatColorVertex.glsl)",
            R"(C:\Users\kregerl\CLionProjects\Autm\assets\shaders\FlatColorFragment.glsl)");

//  --------------------------
//  ---------- Quad ----------
//  --------------------------

    float quadVertices[4 * 9] = {
//             Position(vec3)      TexCoords(vec2)     Color(vec3)    Tiling Factor(Float)
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 10.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 10.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 10.0f
    };


    unsigned int quadIndices[2 * 3] = {
            0, 1, 3,
            1, 2, 3
    };


    s_data.quadVertexArray = std::make_shared<VertexArray>();
    s_data.quadVertexArray->bind();
    std::shared_ptr<VertexBuffer> quadVertexBuffer = std::make_shared<VertexBuffer>(quadVertices,
                                                                                    sizeof(quadVertices));
    quadVertexBuffer->setLayout({
                                        {ShaderDataType::Vec3f, "a_pos",          false},
                                        {ShaderDataType::Vec2f, "a_texCoord",     false},
                                        {ShaderDataType::Vec3f, "a_color",        false},
                                        {ShaderDataType::Float, "a_tilingFactor", false}
                                });

    s_data.quadVertexArray->addVertexBuffer(quadVertexBuffer);
    std::shared_ptr<IndexBuffer> quadIndexBuffer = std::make_shared<IndexBuffer>(quadIndices,
                                                                                 sizeof(quadIndices) /
                                                                                 sizeof(unsigned int));
    s_data.quadVertexArray->setIndexBuffer(quadIndexBuffer);

//  --------------------------
//  ---------- Line ----------
//  --------------------------

    float lineVertices[2 * 6] = {
//          Position(vec3)      Color(Vec3)
            -0.5f, -0.5f, 0.0f, 0.3f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.3f, 0.8f, 1.0f
    };

    unsigned int lineIndices[2] = {
            0, 1
    };
    s_data.lineVertexArray = std::make_shared<VertexArray>();

    s_data.lineVertexArray->bind();
    std::shared_ptr<VertexBuffer> lineVertexBuffer = std::make_shared<VertexBuffer>(lineVertices,
                                                                                    sizeof(lineVertices));
    lineVertexBuffer->setLayout({
                                        {ShaderDataType::Vec3f, "a_pos",   false},
                                        {ShaderDataType::Vec3f, "a_color", false},
                                });

    s_data.lineVertexArray->addVertexBuffer(lineVertexBuffer);

    std::shared_ptr<IndexBuffer> lineIndexBuffer = std::make_shared<IndexBuffer>(lineIndices,
                                                                                 sizeof(lineIndices) /
                                                                                 sizeof(unsigned int));
    s_data.lineVertexArray->setIndexBuffer(lineIndexBuffer);

    s_data.lineVertexArray->unbind();
}

void Renderer2D::shutdown() {

}

void Renderer2D::begin(OrthographicCamera camera) {
    s_data.viewProjectionMatrix = camera.getViewProjectionMatrix();
}

void Renderer2D::end() {

}

void Renderer2D::drawQuad(glm::vec3 position, glm::vec2 size, float rotation) {

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, {size.x, size.y, 1.0f});

    s_data.quadVertexArray->bind();
    s_data.textureShader->bind();
    s_data.textureShader->setMat4("u_viewProjectionMatrix", s_data.viewProjectionMatrix);
    s_data.textureShader->setMat4("u_modelMatrix", modelMatrix);

    s_data.arrowTexture->bind();

    RenderSystem::draw(s_data.quadVertexArray);
    s_data.quadVertexArray->unbind();
}

void Renderer2D::drawLine(glm::vec3 position, glm::vec2 size, float rotation, float lineWidth) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, {size.x, size.y, 1.0f});

    s_data.lineVertexArray->bind();
    s_data.lineShader->bind();
    s_data.lineShader->setMat4("u_viewProjectionMatrix", s_data.viewProjectionMatrix);
    s_data.lineShader->setMat4("u_modelMatrix", modelMatrix);

    glLineWidth(lineWidth);
    RenderSystem::draw(s_data.lineVertexArray, GL_LINES);
}


