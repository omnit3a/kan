/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright (c) 2022, KanOS Contributors */
#include <string.h>

const char *strpbrk(const char *restrict s1, const char *restrict s2)
{
    while(*s1) {
        if(strchr(s2, *s1))
            return s1;
        s1++;
    }

    return NULL;
}
