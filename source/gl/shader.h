#pragma once
#include <stdlib.h>
#include <stdint.h>
#include "shader_src.h"

uint32_t shader_type(SHADER_TYPE type);

uint32_t shader_create(uint32_t type, const char* source);
int32_t shader_get_compile_status(uint32_t shader);
void shader_print_info_log(uint32_t shader);
char* shader_get_info_log(uint32_t shader);

uint32_t program_create(prog_src_t& prog_src);
int32_t program_get_link_status(uint32_t program);
void program_print_info_log(uint32_t program);
char* program_get_info_log(uint32_t program);
