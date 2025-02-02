/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright (c) 2023, KanOS Contributors */
#include <printf.h>

int snprintf(char *restrict s, size_t n, const char *restrict fmt, ...)
{
    int r;
    va_list ap;
    va_start(ap, fmt);
    r = vsnprintf(s, n, fmt, ap);
    va_end(ap);
    return r;
}
