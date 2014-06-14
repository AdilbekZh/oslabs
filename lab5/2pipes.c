#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include<malloc.h>
#include<ctype.h>
#include <unistd.h>

 
int main()
{

  char *cmd[2][3];
  cmd[0][0] = "cat"; cmd[0][1] = "test.c"; cmd[0][2] =NULL;
  cmd[1][0] = "grep"; cmd[1][1] = "\"main\""; cmd[1][2] =NULL;

  int fd[2];
  pid_t pid;
  pipe(fd);
  pid = fork();
  if (pid == 0) {
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    execvp(cmd[1][0], cmd[1]);
  } else {
    //wait(NULL);
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);
    execvp(cmd[0][0], cmd[0]);
  }
  return 0; 
} // for main
