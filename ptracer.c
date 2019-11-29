#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    long orig_eax;
    
    if(argc == 1) {
        fprintf(stderr,"Usage: ptrace -h for help summary\n");
        fprintf(stderr,"Usage: ptrace -f <filename> command [args]\n");
        //ammy should add the returns
//        return 1;
    }
    else {
        for(int i = 1; i<argc;i++) {
            if(strcmp(argv[i],"-h") == 0) {
                //need to write a proper help summary
                fprintf(stdout,"Help Summary\n");
            }
        }
    }
    //start forking from here
    pid_t pid = fork();
    if(pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if(pid == 0) {
        //child process starts here
        printf("Hello from child!\n");
        printf("%d\n",pid);
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execlp("ls","ls",NULL);
        printf("child stopping!\n");

    }
    else {
        //parent process starts here
        //  - should have the [-f file] functionality in this process
        printf("Hello from parent!\n");
        printf("%d\n",pid);
        wait(NULL);
        orig_eax = ptrace(PTRACE_PEEKUSER,
                          pid, 4 * ORIG_EAX,
                          NULL);
        printf("The child made a "
               "system call %ld\n", orig_eax);
        ptrace(PTRACE_CONT, pid, NULL, NULL);
        printf("parent stopping!\n");
        
    }
    
    
    return 0;
}
