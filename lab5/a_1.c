#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc,char* argv[]){
	
	printf("Enter command:\n");
	char buf[200];
	fgets(buf,200,stdin); 
	if (buf[0] == '&') { return 0;}

	int i=0;
	char * p[100];
	p[i] = (char*) strtok(buf," \n");
	while(p[i]!=NULL){
		p[++i] = (char *)strtok(NULL," \n");
	}

	int type = -1; // 0=stdin, 1=stdout, 2=stderr
	int j;
	for (j = 0; j<i; j++) {
		if (p[j][0] == '>') {
			type=0;
		} else if (p[j][0] == '<') {
			type=1;
		} else if (p[j][0] == '2' && p[j][1] == '>') {
			type=2;
		}
		if (type != -1) {
			p[j++] = NULL;
			break;
		}
	}

	if (type == 0) {
		int fd = open(p[j], O_CREAT|O_TRUNC|O_WRONLY);
		pid_t pid = fork();
		if (pid == 0) {
			close(1);
			dup2(fd, 1);
			close(fd);
			execvp(p[0], p);
		} else if (pid != 0){
			wait(NULL);
		}
	} else if (type == 1) {
		int fd = open(p[j], O_RDONLY);
		pid_t pid = fork();
		if (pid == 0) {
			close(0);
			dup2(fd, 0);
			close(fd);
			execvp(p[0], p);
		} else if (pid != 0){
			wait(NULL);
		}
	} else if (type == 2) {
		int fd = open(p[j], O_CREAT|O_TRUNC|O_WRONLY);
		pid_t pid = fork();
		if (pid == 0) {
			close(2);
			dup2(fd, 2);
			close(fd);
			execvp(p[0], p);
		} else if (pid != 0){
			wait(NULL);
		}
	}

	while (ok) {
		wait(NULL);
			
		if (type == 0) {
			int fd = open(p[j], O_CREAT|O_TRUNC|O_WRONLY);
			pid_t pid = fork();
			if (pid == 0) {
				close(1);
				dup2(fd, 1);
				close(fd);
				execvp(p[0], p);
			} else if (pid != 0){
				wait(NULL);
			}
		} else if (type == 1) {
			int fd = open(p[j], O_RDONLY);
			pid_t pid = fork();
			if (pid == 0) {
				close(0);
				dup2(fd, 0);
				close(fd);
				execvp(p[0], p);
			} else if (pid != 0){
				wait(NULL);
			}
		} else if (type == 2) {
			int fd = open(p[j], O_CREAT|O_TRUNC|O_WRONLY);
			pid_t pid = fork();
			if (pid == 0) {
				close(2);
				dup2(fd, 2);
				close(fd);
				execvp(p[0], p);
			} else if (pid != 0){
				wait(NULL);
			}
		}
	}

	return 0;
}