set(
    GL_SOURCE
    "source/gl/gl.c"
)

add_library(gl ${GL_SOURCE})
target_include_directories(gl PUBLIC "source/")
