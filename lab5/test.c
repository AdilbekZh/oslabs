#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc,char* argv[]){
	printf("Enter command:\n");
	char buf[200];
	fgets(buf,200,stdin); 

	/*--------------- READ FROM TERMINAL ----------------------*/
	int i=0;
	int status;
	char * p0[100];
	p0[i] = (char*) strtok(buf,"|");
	while(p0[i]!=NULL){
		p0[++i] = (char *)strtok(NULL,"|\n");
	}

	int n = i;
	int fd[2];
	int fd_old[2];
	pid_t pid;
	int fd_in = 0;

	for (i = 0; i < n; i++) {
		int j = 0;
		char * p1[100];
		p1[j] = (char*) strtok(p0[i]," ");
		while(p1[j]!=NULL){
			p1[++j] = (char *)strtok(NULL," \n");
		}
		pipe(fd);
		pid=fork();
		if(pid == 0) {
			if (i > 0) {
				dup2(fd_old[0], 0);
				close(fd_old[0]);
				close(fd_old[1]);
			}
			if (i + 1 < n) {
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
			}
			execvp(p1[0], p1);
			exit(0);
		} else {
			wait(NULL);
			if (i > 0){
				close(fd_old[0]);
				close(fd_old[1]);
			}
			if (i + 1 < n) {
				fd_old[0] = fd[0];
				fd_old[1] = fd[1];
			}
		}
	}
	if (n > 0) {
		close(fd_old[0]);
		close(fd_old[1]);
	}
	return 0;
}