set(
    GLAD_SOURCE
    "source/glad/gl.c"
)

set(
    GL_SOURCE
    "source/gl/directive.cpp"
    "source/gl/shader_src.cpp"
    "source/gl/shader.cpp"
)

add_library(gl ${GLAD_SOURCE} ${GL_SOURCE})
target_include_directories(gl PUBLIC "source/")
target_link_libraries(gl cl)
