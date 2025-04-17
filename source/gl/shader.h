#pragma once
#include <stdlib.h>
#include "shader_src.h"

u32 shader_type(SHADER_TYPE type);

u32 shader_create(u32 type, const char* source);
s32 shader_get_compile_status(u32 shader);
void shader_print_info_log(u32 shader);
char* shader_get_info_log(u32 shader);

u32 program_create(prog_src_t& prog_src);
s32 program_get_link_status(u32 program);
void program_print_info_log(u32 program);
char* program_get_info_log(u32 program);
