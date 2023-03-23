/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright (c), 2023, KanOS Contributors */
#include <sys/debug.h>
#include <sys/initcall.h>
#include <sys/interrupt.h>
#include <sys/kprintf.h>
#include <sys/malloc.h>
#include <sys/pmem.h>
#include <sys/version.h>

static int int42_handler(cpu_ctx_t *restrict ctx, void *restrict arg)
{
    kprintf("test_kernel_stuff: interrupt 0x42 called");
    return 1;
}

static void test_kernel_stuff(void)
{
    void *p1;
    void *p2;
    void *p3;

    // Test interrupt handling
    add_interrupt_handler(allocate_interrupt(0x42), &int42_handler, NULL);
    add_interrupt_handler(allocate_interrupt(0x43), &int42_handler, NULL);
    add_interrupt_handler(allocate_interrupt(0x44), &int42_handler, NULL);
    asm volatile("int $0x42");
    asm volatile("int $0x43");
    asm volatile("int $0x44");

    // Test memory allocation
    p1 = malloc(64);
    p2 = malloc(64);
    kprintf("malloc test 1: p1=%p p2=%p", p1, p2);
    free(p1);
    p3 = malloc(128);
    kprintf("malloc test 2: p1=%p p3=%p", p1, p3);
    free(p2);
    free(p3);
    p1 = pmem_alloc_page_virt();
    kprintf("pmem_alloc_page_virt test 3: p1=%p", p1);
    pmem_free_page_virt(p1);
}

void __used __noreturn kmain(void)
{
    size_t i;

    // Print kernel version
    kprintf("sys: starting version %s", sys_version);

    // Initialize most of subsystems
    // FIXME: should this include SMP and scheduling?
    for(i = 0; initcalls[i].init_func; initcalls[i++].init_func());

    test_kernel_stuff();

    panic("sys: nothing else to do!");
    UNREACHABLE();
}
