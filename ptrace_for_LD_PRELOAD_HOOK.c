#include <stdio.h>

long int ptrace(int request, int pid, void *addr, void *data)
{
    printf("[!] ptrace() replaced\n");

    /* refer to /sys/ptrace.h */
    if( request == 16 )
    {
        /* PTRACE_ATTACH */
        printf("ptrace_attach with pid %d \n", pid);
    }


    return 0;
}
