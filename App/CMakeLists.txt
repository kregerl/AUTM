project(App)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(${PROJECT_NAME} src/App.cpp src/Mandelbrot.cpp src/Mandelbrot.h src/DemoLayer.cpp src/DemoLayer.h src/RayMarching.cpp src/RayMarching.h src/EntityLayer.cpp src/EntityLayer.h src/CustomShader.cpp src/CustomShader.h)
target_link_libraries(${PROJECT_NAME} PUBLIC Autm)