project(Autm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(OpenGL REQUIRED)

add_subdirectory(vendor/glfw)
include_directories(vendor/glfw/include)

add_subdirectory(vendor/glm)
include_directories(vendor/glm/glm)

add_subdirectory(vendor/stb_image)
include_directories(vendor/stb_image)

add_subdirectory(vendor/spdlog)
include_directories(vendor/spdlog)

add_subdirectory(vendor/imgui)
include_directories(vendor/imgui)

add_subdirectory(vendor/glad)

add_subdirectory(vendor/entt)
include_directories(vendor/entt/include)

add_subdirectory(vendor/box2d)
include_directories(vendor/box2d/include)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

file(COPY ../assets DESTINATION ${CMAKE_BINARY_DIR})

set(PCHFILES src/autmpch.cpp src/autmpch.cpp src/Autm.h)
add_library(pch ${PCHFILES})
target_precompile_headers(pch PUBLIC src/autmpch.h)

set(SOURCE_FILES src/Core/Window.cpp src/Core/Window.h src/App/Application.cpp src/App/Application.h src/Renderer/Shader.cpp src/Renderer/Shader.h src/Renderer/ComputeShader.cpp src/Renderer/ComputeShader.h src/Renderer/VertexBuffer.cpp src/Renderer/VertexBuffer.h src/Renderer/IndexBuffer.cpp src/Renderer/IndexBuffer.h src/Renderer/Buffer.h src/Renderer/VertexBufferLayout.cpp src/Renderer/VertexBufferLayout.h src/Renderer/VertexArray.cpp src/Renderer/VertexArray.h src/Renderer/OrthographicCamera.cpp src/Renderer/OrthographicCamera.h src/Event/Event.h src/Event/KeyEvents.h src/Event/MouseEvents.h src/Core/Input.cpp src/Core/Input.h src/Renderer/Renderer2D.cpp src/Renderer/Renderer2D.h src/Renderer/OrthographicCameraController.cpp src/Renderer/OrthographicCameraController.h src/Core/KeyCodes.h src/Renderer/Texture2D.cpp src/Renderer/Texture2D.h src/Renderer/RenderSystem.cpp src/Renderer/RenderSystem.h src/Event/WindowEvents.h src/Core/Log.cpp src/Core/Log.h src/Renderer/OpenGLContext.cpp src/Renderer/OpenGLContext.h src/Core/Layer.cpp src/Core/Layer.h src/Core/LayerStack.cpp src/Core/LayerStack.h src/Imgui/ImGuiLayer.h src/Imgui/ImGuiLayer.cpp src/Scene/Scene.cpp src/Scene/Scene.h src/Scene/Components.h src/Scene/Entity.cpp src/Scene/Entity.h src/Renderer/UniformBuffer.cpp src/Renderer/UniformBuffer.h src/Core/UUID.cpp src/Core/UUID.h src/Scene/EntityContactListener.cpp src/Scene/EntityContactListener.h src/Core/Assert.h src/Util/Gradient.cpp src/Util/Gradient.h src/Renderer/Framebuffer.cpp src/Renderer/Framebuffer.h src/Util/Primitives.cpp src/Util/Primitives.h
        src/Physics/Vertex.cpp
        src/Physics/Vertex.h
        src/Physics/Edge.cpp
        src/Physics/Edge.h
        src/Physics/PhysicsWorld.cpp
        src/Physics/PhysicsWorld.h
        src/Physics/PhysicsBody.cpp
        src/Physics/PhysicsBody.h
        src/Core/Thread/ThreadPool.h
        src/Util/Coordinate.h
        src/Core/Thread/TaskQueue.h
        src/Core/Thread/Worker.h
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} glad glfw glm spdlog imgui stb_image entt box2d ${OPENGL_LIBRARY} -ggdb)
target_include_directories(${PROJECT_NAME} PUBLIC src vendor)
