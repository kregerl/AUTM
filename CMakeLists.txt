cmake_minimum_required(VERSION 3.20)
project(Autm)

find_package(OpenGL REQUIRED)

add_subdirectory(vendor/glfw)
include_directories(vendor/glfw/include)

add_subdirectory(vendor/glm)
include_directories(vendor/glm/glm)

add_subdirectory(vendor/stb_image)
include_directories(vendor/stb_image)

include_directories(vendor/glad/include)

include_directories(src)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES vendor/glad/src/glad.c src/main.cpp src/Core/Window.cpp src/Core/Window.h src/App/Application.cpp src/App/Application.h src/Renderer/Shader.cpp src/Renderer/Shader.h src/Renderer/ComputeShader.cpp src/Renderer/ComputeShader.h src/Renderer/VertexBuffer.cpp src/Renderer/VertexBuffer.h src/Renderer/IndexBuffer.cpp src/Renderer/IndexBuffer.h src/Renderer/Buffer.h src/Renderer/VertexBufferLayout.cpp src/Renderer/VertexBufferLayout.h src/Renderer/VertexArray.cpp src/Renderer/VertexArray.h src/Renderer/OrthographicCamera.cpp src/Renderer/OrthographicCamera.h src/Core/Event/Event.h src/Core/Event/KeyEvents.h src/Core/Event/MouseEvents.h src/Core/Input.cpp src/Core/Input.h src/Renderer/Renderer2D.cpp src/Renderer/Renderer2D.h src/Renderer/OrthographicCameraController.cpp src/Renderer/OrthographicCameraController.h src/Core/KeyCodes.h src/Renderer/Texture2D.cpp src/Renderer/Texture2D.h src/Renderer/RenderSystem.cpp src/Renderer/RenderSystem.h)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

set(PCHFILES src/autmpch.cpp src/autmpch.cpp)
add_library(pch ${PCHFILES})
target_precompile_headers(pch PUBLIC src/autmpch.h)

target_link_libraries(${CMAKE_PROJECT_NAME} glfw glm stb_image ${OPENGL_LIBRARY})
