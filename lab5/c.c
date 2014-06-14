#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


void read(char* &p) {
	char buf[200];
	fgets(buf,200,stdin); 
	if (buf[0] == '&') { return 0;}

	int i=0;
	p[i] = (char*) strtok(buf," \n");
	while(p[i]!=NULL){
		p[++i] = (char *)strtok(NULL," \n");
	}
	return p;
}

int main(int argc,char* argv[]){
	printf("Enter command:\n");
	char * p[100];
	read();

	
	return 0;
}