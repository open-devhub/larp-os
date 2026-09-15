#pragma once

#include <common.h>

#define SYS_EXIT  0
#define SYS_READ  1
#define SYS_WRITE 2


int8_t invoke_syscall(int no, int64_t arg1, int64_t arg2, int64_t arg3, int64_t arg4);
