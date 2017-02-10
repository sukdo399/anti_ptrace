#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t child;
    child = fork();

    if(child == 0)
    {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        //execl("/bin/ls", "ls", NULL);
    }
    else
    {
        wait(NULL);

        printf("exit, pid: %d \n", child);
        ptrace(PTRACE_CONT, child, NULL, NULL);
        return 0;
    }
    system("ls");

    printf("exit, pid: %d \n", child);

    return 0;
}
