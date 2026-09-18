#pragma once

#include <stdint.h>

#define MAX_BUFF 128

#define EXIT_SUCCESS  0
#define EXIT_CMD_NF   1 // Command not found


enum env_var_type {
    ENV_TYPE_STR, // string
    ENV_TYPE_INT  // integer
};

typedef struct {
    char name[64];
    uint64_t value;
    enum env_var_type type;
} EnvironmentVariable;
