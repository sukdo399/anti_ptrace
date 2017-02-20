#include <stdio.h>
#include <signal.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


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
    int status;
    pid_t child;
    int fd;
    int ret;

    child = fork();
    if (child == 0) {
        printf("child : pid=%d\n",getpid());
        //kill child when parent exits.
        prctl(PR_SET_PDEATHSIG, SIGHUP);
        //if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
        if (my_ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
        {
            printf("don't trace me !!\n");
            return 1;
        }
        printf("before system #1 @@@@\n");
        system("ls");
        printf("after system #1 @@@@\n");

        sleep(3);

        printf("before system #2 @@@@\n");
        system("ls -al");
        printf("after system #2 @@@@\n");
    } else
        while (1) {
            printf("before wait ^^^^\n");
            ret = wait(&status);
            printf("after wait ^^^^\n");
            printf("parent : pid=%d status=%d child pid=%d\n",getpid(),status,child);
            if ( ret == -1 ) exit(0);
            ptrace(PTRACE_CONT, child, NULL, NULL);
        }

    fd = open("./data",O_CREAT |  O_WRONLY, 0644);
    write(fd,"12345",5);
    printf("child: nomal execution child=%d \n",child);
    while (1) {
        sleep(10);
    }

    return 0;
}
