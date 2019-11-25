#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    
    if(argc == 1) {
        fprintf(stderr,"Usage: ptrace -h for help summary\n");
        fprintf(stderr,"Usage: ptrace -f <filename> command [args]\n");
    }
    else {
        for(int i = 1; i<argc;i++) {
            if(strcmp(argv[i],"-h") == 0) {
                fprintf(stdout,"Help Summary\n");
            }
        }
    }
    return 0;
}
