#include <stdio.h>
#include <sys/ptrace.h>

#include <unistd.h>

#define SYS_PTRACE 101
long my_ptrace(long request, long pid, void *addr, void *data)
{
    long ret;
    __asm__ volatile(
    "mov %0, %%rdi\n"
    "mov %1, %%rsi\n"
    "mov %2, %%rdx\n"
    "mov %3, %%r10\n"
    "mov $SYS_PTRACE, %%rax\n"
    "syscall" : : "g"(request), "g"(pid),
    "g"(addr), "g"(data));
    __asm__ volatile("mov %%rax, %0" : "=r"(ret));

    printf("my_ptrace, ret: %d \n", ret);
    return ret;
}

int main()
{
    if (my_ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
    {
        printf("don't trace me !!\n");
        return 1;
    }

    while(1)
    {

        printf("nomal execution \n");
        sleep(1);
    }

    return 0;
}
