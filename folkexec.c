#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(void) {
  pid_t child;
  int cstatus;  /* Exit status of child. */
  pid_t c;      /* Pid of child to be returned by wait. */

  if ((child = fork()) == 0) {

    /* Child process. To begin with, it prints its pid. */
    printf("Child: PID of Child = %ld\n", (long) getpid());

    /* Child will now execute the grep command. */
    execlp("grep", "grep", "--color=auto", "-n", "fork", "man2fork.txt", NULL);

    /* If the child process reaches this point, then  */
    /* execlp must have failed.                       */
    fprintf(stderr, "Child process could not do execlp.\n");
    exit(1);
  }
  else { /* Parent process. */
    if (child == (pid_t)(-1)) {
      fprintf(stderr, "Fork failed.\n"); exit(1);
    }
    else {
      c = wait(&cstatus); /* Wait for child to complete. */
      printf("Parent: Child %ld exited with status = %d\n", c, WEXITSTATUS(cstatus));
    }
  }
  return 0;
}

