#include <stdio.h>
#include <cl/cstr.h>
#include "directive.h"

#include "shader_src.h"

SHADER_TYPE shader_type_from_cstr(const char* cstr) {
    if (cstr_cmp(cstr, "vertex")) {
        return SHADER_TYPE::VERTEX;
    }

    if (cstr_cmp(cstr, "fragment")) {
        return SHADER_TYPE::FRAGMENT;
    }

    return SHADER_TYPE::INVALID;
}

void prog_src_load(prog_src_t& prog_src, const char* path) {
    FILE* file = fopen(path, "r");
    size_t cap = 0;
    char* line = nullptr;
    size_t line_len = 0;

    if (file == nullptr) {
        return;
    }

    directive_t directive;
    SHADER_TYPE type = SHADER_TYPE::INVALID;
    ssize_t i = -1;

    for (size_t i = 0; i < PROG_SRC_SHADER_CAP; i += 1) {
        prog_src.shaders[i].type = SHADER_TYPE::INVALID;
    }

    while ((line_len = getline(&line, &cap, file)) != -1) {
        if (directive_scan(directive, line, line_len)) {
            if (directive.type == DIRECTIVE_TYPE::TYPE) {
                type = shader_type_from_cstr(directive.value);

                if (type != SHADER_TYPE::INVALID) {
                    i += 1;

                    continue;
                }
            }
        }

        if (i > -1 && i < PROG_SRC_SHADER_CAP) {
            shader_src_t& shader_src = prog_src.shaders[i];

            if (shader_src.type == SHADER_TYPE::INVALID) {
                shader_src.type = type;
                dstr_new(shader_src.source, 256);
                dstr_assign(shader_src.source, line);
            } else {
                dstr_concat(shader_src.source, line);
            }
        }
    }

    prog_src.len = i + 1;

    fclose(file);

    if (line) {
        free(line);
    }
}

void prog_src_del(prog_src_t& prog_src) {
    for (size_t i = 0; i < prog_src.len; i++) {
        shader_src_t& shader_src = prog_src.shaders[i];
        dstr_del(shader_src.source);
    }
}
