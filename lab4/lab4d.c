#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc,char* argv[]){
	
	pid_t x;
	int ok = 1;
	char * p[100];
	
	printf("Enter command: ");
	char buf[200];
	fgets(buf,200,stdin); 
	if (buf[0] == '&') { return 0;}

	int i=0;
	p[i] = (char*) strtok(buf," \n");
	while(p[i]!=NULL){
		p[++i] = (char *)strtok(NULL," \n");
	}
	x = fork();	

	while (ok) {
		if (x == 0) {
			execvp(p[0], &p[0]);
			exit(0);
		} else {
			wait(NULL);
			printf("Enter command: ");
			char buf[200];
			fgets(buf,200,stdin); 
			
			
			// tokenizing the string the C way :)			
			int i=0;
			p[i] = (char*) strtok(buf," \n");
			while(p[i]!=NULL){
				p[++i] = (char *)strtok(NULL," \n");
			}
			
			if (p[i-1][0] == '&') { ok=0; return 0; }
			x = fork();	
		}
	}

	return 0;
}