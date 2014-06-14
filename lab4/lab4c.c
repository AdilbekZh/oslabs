#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc,char* argv[]){
	printf("Enter command: ");
	char buf[200];
	fgets(buf,200,stdin); 

	// tokenizing the string the C way :)
	char * p[200];
	int i=0;
	p[i] = (char*) strtok(buf," \n");
	while(p[i]!=NULL){
		p[++i] = (char *)strtok(NULL," \n");
	}
	
	pid_t x;
	x = fork();

	if (x == 0) {
		execvp(p[0], &p[0]);
		exit(0);
	} 

	return 0;
}