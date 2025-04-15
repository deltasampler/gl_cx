#include <stdio.h>
#include <glad/gl.h>

#include "shader.h"

uint32_t shader_type(SHADER_TYPE type) {
    if (type == SHADER_TYPE::VERTEX) {
        return GL_VERTEX_SHADER;
    } else if (type == SHADER_TYPE::FRAGMENT) {
        return GL_FRAGMENT_SHADER;
    }

    return 0;
}

uint32_t shader_create(uint32_t type, const char* source) {
    uint32_t shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);

    if (!shader_get_compile_status(shader)) {
        shader_print_info_log(shader);
        glDeleteShader(shader);

        return 0;
    }

    return shader;
}

int32_t shader_get_compile_status(uint32_t shader) {
    int32_t compile_status = false;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

    return compile_status;
}

void shader_print_info_log(uint32_t shader) {
    char* info_log = shader_get_info_log(shader);
    printf("%s\n", info_log);
    delete info_log;
}

char* shader_get_info_log(uint32_t shader) {
    int32_t info_log_length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);

    char* info_log = new char[info_log_length];
    glGetShaderInfoLog(shader, info_log_length, &info_log_length, info_log);

    return info_log;
}

uint32_t program_create(prog_src_t& prog_src) {
    uint32_t shaders[PROG_SRC_SHADER_CAP];
    size_t shaders_len = 0;

    for (size_t i = 0; i < prog_src.len; i += 1) {
        shader_src_t& shader_src = prog_src.shaders[i];
        uint32_t shader = shader_create(shader_type(shader_src.type), shader_src.source.data);

        if (!shader) {
            for (int j = 0; j < shaders_len; j += 1) {
                glDeleteShader(shaders[j]);
            }

            return 0;
        }

        shaders[shaders_len++] = shader;
    }

    uint32_t program = glCreateProgram();

    for (size_t i = 0; i < shaders_len; i += 1) {
        glAttachShader(program, shaders[i]);
    }

    glLinkProgram(program);

    for (size_t i = 0; i < shaders_len; i += 1) {
        uint32_t shader = shaders[i];
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }

    if (!program_get_link_status(program)) {
        program_print_info_log(program);
        glDeleteProgram(program);

        return 0;
    }

    return program;
}

int32_t program_get_link_status(uint32_t program) {
    int32_t link_status;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);

    return link_status;
}

void program_print_info_log(uint32_t program) {
    char* info_log = program_get_info_log(program);
    printf("%s\n", info_log);
    delete info_log;
}

char* program_get_info_log(uint32_t program) {
    int32_t info_log_length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

    char* info_log = new char[info_log_length];
    glGetProgramInfoLog(program, info_log_length, &info_log_length, info_log);

    return info_log;
}
