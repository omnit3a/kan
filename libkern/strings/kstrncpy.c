/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright (c) 2022, KanOS Contributors */
#include <strings.h>

/* The standard function, strncpy, uses the size
 * limiter as the size of source, not destination.
 * Because no one would EVER need to specify destination size!
 * Yes, this comment is is copied from kstrncat... Too bad! */
char *kstrncpy(char *restrict s1, const char *restrict s2, size_t n)
{
    char *save = s1;
    while(*s2 && n--)
        *s1++ = *s2++;
    if(n)
        *s1 = 0;
    return save;
}
