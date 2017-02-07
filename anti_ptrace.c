#include <stdio.h>
#include <sys/ptrace.h>

#include <unistd.h>

int main()
{
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
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
