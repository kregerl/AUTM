project(glad)

add_library(${PROJECT_NAME} src/glad.c include/glad/glad.h)
target_include_directories(${PROJECT_NAME} PUBLIC include)