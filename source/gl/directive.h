#pragma once
#include <cl/types.h>

// directive
#define DIRECTIVE_KEY_CAP 8
#define DIRECTIVE_VALUE_CAP 256

enum class DIRECTIVE_TYPE {
    INVALID,
    TYPE,
    INCLUDE_REL,
    INCLUDE_ABS
};

struct directive_t {
    DIRECTIVE_TYPE type;
    char key[DIRECTIVE_KEY_CAP];
    char value[DIRECTIVE_VALUE_CAP];
};

bool directive_scan(directive_t& directive, const char* line);
