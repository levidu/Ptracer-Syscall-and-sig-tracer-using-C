#define _POSIX_C_SOURCE 200112L

/* C standard library */
#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* POSIX */
#include <unistd.h>
#include <sys/user.h>
#include <sys/wait.h>

/* Linux */
#include <syscall.h>
#include <sys/ptrace.h>
#include <string.h>
#include <sys/reg.h>
#include <stdbool.h>

#define FATAL(...) \
    do { \
        fprintf(stderr, "strace: " __VA_ARGS__); \
        fputc('\n', stderr); \
        exit(EXIT_FAILURE); \
    } while (0)
void decToHexa(long n)
{
    // char array to store hexadecimal number
    char hexaDeciNum[100];
    // counter for hexadecimal number array
    long i = 0;
    while(n!=0)
    {
        // temporary variable to store remainder
        long temp  = 0;
        // storing remainder in temp variable.
        temp = n % 16;
        // check if temp < 10
        if(temp < 10)
        {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else
        {
            hexaDeciNum[i] = temp + 55;
            i++;
        }
        n = n/16;
    }
    // printing hexadecimal number array in reverse order
    for(long j=i-1; j>=0; j--)
        printf("%s\n",hexaDeciNum[j]);
}


bool print_to_file = false;


const int long_size = sizeof(long);
void getdata(pid_t pid, long addr,
             char *str, int len)
{   char *laddr;
    int i, j;
    union u {
            long val;
            char chars[long_size];
    }data;
    i = 0;
    j = len / long_size;
    laddr = str;
    while(i < j) {
        data.val = ptrace(PTRACE_PEEKDATA,
                          pid, addr + i * 8,
                          NULL);
        memcpy(laddr, data.chars, long_size);
        ++i;
        laddr += long_size;
    }
    j = len % long_size;
    if(j != 0) {
        data.val = ptrace(PTRACE_PEEKDATA,
                          pid, addr + i * 8,
                          NULL);
        memcpy(laddr, data.chars, j);
    }
    str[len] = '\0';
}
int main(int argc, char **argv)
{
    if (argc <= 1)
        FATAL("too few arguments: %d", argc);
    int file_path_argv;
    const char * file_path;
    for(int iter=1;iter<argc;iter++){
      if(strcmp(argv[iter],"-h")==0){
    fprintf(stderr,"Help Summary\n");
    }
        if(strcmp(argv[iter],"-f")==0) {
            print_to_file = true;
            file_path_argv = iter+1;
            file_path = argv[file_path_argv];
            
        }
    }
    pid_t pid = fork();
    switch (pid) {
        case -1: /* error */
            FATAL("%s", strerror(errno));
        case 0:  /* child */
            ptrace(PTRACE_TRACEME, 0, 0, 0);
            execvp(argv[1], argv + 1);
            FATAL("%s", strerror(errno));
    }

    /* parent */
    waitpid(pid, 0, 0); // sync with PTRACE_TRACEME
    ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_EXITKILL);

    for (;;) {
        /* Enter next system call */
        if (ptrace(PTRACE_SYSCALL, pid, 0, 0) == -1)
            FATAL("%s", strerror(errno));
        if (waitpid(pid, 0, 0) == -1)
            FATAL("%s", strerror(errno));

        /* Gather system call arguments */
        struct user_regs_struct regs;
        if (ptrace(PTRACE_GETREGS, pid, 0, &regs) == -1)
            FATAL("%s", strerror(errno));
        long syscall = regs.orig_rax;

    if(syscall == 1) {
        //write system call
        char *str;
        long params[3];
         params[0] = ptrace(PTRACE_PEEKUSER,pid,8*RDI,NULL);
                 params[1] = ptrace(PTRACE_PEEKUSER,pid,8*RSI,NULL);
                 params[2] = ptrace(PTRACE_PEEKUSER,pid,8*RDX,NULL);
   
                    str = (char*)malloc(params[2]+1);
                    memset(str,0,params[2]+1);
                    getdata(pid,params[1],str,params[2]);
                    printf("\nwrite(%ld,%s)\n",(long)regs.rdi,str);
                    free(str);
    }else if(syscall ==0){
        //read system call
        char *str_read;
            long params_read[3];

             params_read[0]=ptrace(PTRACE_PEEKUSER,pid,8*RDI,NULL);
         params_read[1]=ptrace(PTRACE_PEEKUSER,pid,8*RSI,NULL);
         params_read[2]=ptrace(PTRACE_PEEKUSER,pid,8*RDX,NULL);
        // fprintf(stderr,"debugging RSI address:%ld\n",params_read[1]);
        // fprintf(stderr,"debugging RSI from regs:%ld\n",(long)regs.rsi);

         str_read=(char*)malloc(params_read[2]+1);
         memset(str_read,0,params_read[2]+1);
         getdata(pid,params_read[1],str_read,params_read[2]);
         printf("\nread(%ld, %s)\n",(long)regs.rdi,str_read);
         free(str_read);
    }else if (syscall ==231){
        //exit_group system call
         fprintf(stderr,"exit_group(%ld)\n",(long)regs.rdi);
        if(print_to_file) {
            FILE * file_pointer;
            file_pointer = fopen(file_path,"a");
            fprintf(file_pointer,"exit_group(%ld)\n",(long)regs.rdi);
        }
    }else if(syscall == 3){
        //close system call
     fprintf(stderr,"close(%ld)",(long)regs.rdi);
      //dup system call
    }else if(syscall==32){
         fprintf(stderr,"dup %ld",(long)regs.rdi);
      //dup2 system call
    }else if(syscall==33) {
            fprintf(stderr,"dup2 %ld %ld",(long)regs.rdi,(long)regs.rsi);
       //fstat system call
    }else if(syscall == 5){
            struct s{
         long rsi_size;
         long rsi_mode;
         }s1;
         s1.rsi_size = ptrace(PTRACE_PEEKDATA,pid,regs.rsi+16,NULL);
        s1.rsi_mode = ptrace(PTRACE_PEEKDATA,pid,regs.rsi+24,NULL);
            fprintf(stderr,"fstat(%ld, st_size:%ld, st_mode:%ld)\n",(long)regs.rdi,(long)s1.rsi_size,(long)s1.rsi_mode);
    }
    // open syscall
    else if(syscall ==2) {
        char *str;
        long params[3];
         params[0] = ptrace(PTRACE_PEEKUSER,pid,8*RDI,NULL);
                 params[1] = ptrace(PTRACE_PEEKUSER,pid,8*RSI,NULL);
                 params[2] = ptrace(PTRACE_PEEKUSER,pid,8*RDX,NULL);
                    str = (char*)malloc(params[2]+1);
                    memset(str,0,params[2]+1);
                    getdata(pid,params[0],str,params[2]);
                    printf("\nopen(%ld,%ld,%s)\n",(long)regs.rdi,(long)regs.rsi,str);
                    free(str);

    }
    else{
        //Print the registers of unhandled system calls
    fprintf(stderr,"%ld(%ld, %ld, %ld, %ld %ld %ld)",syscall, (long)regs.rdi,(long)regs.rsi,(long)regs.rdx,(long)regs.r10,(long)regs.r8,(long)regs.r9);
    }

        /* Run system call and stop on exit */
        if (ptrace(PTRACE_SYSCALL, pid, 0, 0) == -1)            FATAL("%s", strerror(errno));
        if (waitpid(pid, 0, 0) == -1)
            FATAL("%s", strerror(errno));

        /* Get system call result */
        if (ptrace(PTRACE_GETREGS, pid, 0, &regs) == -1) {
            fputs(" = ?\n", stderr);
            if (errno == ESRCH)
                exit(regs.rdi); // system call was _exit(2) or similar
            FATAL("%s", strerror(errno));
        }

        /* Print system call result */
        fprintf(stderr, " = %ld\n", (long)regs.rax);
    }
}

