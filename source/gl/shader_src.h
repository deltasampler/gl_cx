#pragma once
#include <stdlib.h>
#include <cl/dstr.h>

// shader source
enum class SHADER_TYPE {
    INVALID,
    VERTEX,
    FRAGMENT
};

SHADER_TYPE shader_type_from_cstr(const char* cstr);

struct shader_src_t {
    SHADER_TYPE type;
    dstr_t source;
};

// program source
#define PROG_SRC_SHADER_CAP 4

struct prog_src_t {
    shader_src_t shaders[PROG_SRC_SHADER_CAP];
    usize len;
};

void prog_src_load(prog_src_t& prog_src, const char* path);
void prog_src_del(prog_src_t& prog_src);
