#include <cl/cstr.h>

#include "directive.h"

bool directive_scan(directive_t& directive, const char* line, size_t len) {
    directive.type = DIRECTIVE_TYPE::INVALID;

    // minimal directive: #type vertex
    if (len < 12) {
        return false;
    }

    size_t i = 0;
    char c = line[i++];

    // skip whitespace
    while (is_space(c) && i < len) {
        c = line[i++];
    }

    if (c != '#') {
        return false;
    }

    // reached end
    if (i >= len) {
        return false;
    }

    // next char
    c = line[i++];

    if (!is_alpha(c)) {
        return false;
    }

    // extract key
    size_t key_len = 0;

    while (is_alpha(c) && i < len && key_len < DIRECTIVE_KEY_CAP) {
        directive.key[key_len++] = c;
        c = line[i++];
    }

    directive.key[key_len] = '\0';

    // skip whitespace
    while (is_space(c) && i < len) {
        c = line[i++];
    }

    DIRECTIVE_TYPE type = DIRECTIVE_TYPE::INVALID;

    if (cstr_cmp(directive.key, "type")) {
        type = DIRECTIVE_TYPE::TYPE;
    } else if (cstr_cmp(directive.key, "include")) {
        if (c == '"') {
            type = DIRECTIVE_TYPE::INCLUDE_REL;
        } else if (c == '<') {
            type = DIRECTIVE_TYPE::INCLUDE_ABS;
        }
    }

    // extract value
    size_t value_len = 0;

    if (type == DIRECTIVE_TYPE::INVALID) {
        return false;
    } else if (type == DIRECTIVE_TYPE::TYPE) {
        if (!is_alpha(c)) {
            return false;
        }

        while (is_alpha(c) && i < len && value_len < DIRECTIVE_VALUE_CAP) {
            directive.value[value_len++] = c;
            c = line[i++];
        }

        directive.value[value_len] = '\0';

        if (!cstr_cmp(directive.value, "vertex") && !cstr_cmp(directive.value, "fragment")) {
            return false;
        }
    } else if (type == DIRECTIVE_TYPE::INCLUDE_REL) {
        c = line[i++];

        while (c != '"' && i < len && value_len < DIRECTIVE_VALUE_CAP) {
            directive.value[value_len++] = c;
            c = line[i++];
        }

        directive.value[value_len] = '\0';

        if (value_len < 1) {
            return false;
        }
    } else if (type == DIRECTIVE_TYPE::INCLUDE_ABS) {
        c = line[i++];

        while (c != '>' && i < len && value_len < DIRECTIVE_VALUE_CAP) {
            directive.value[value_len++] = c;
            c = line[i++];
        }

        directive.value[value_len] = '\0';

        if (value_len < 1) {
            return false;
        }
    }

    directive.type = type;

    return true;
}
