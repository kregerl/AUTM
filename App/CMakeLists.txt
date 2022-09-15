project(App)

add_executable(${PROJECT_NAME} src/App.cpp src/Mandelbrot.cpp src/Mandelbrot.h)
target_link_libraries(${PROJECT_NAME} PUBLIC Autm)