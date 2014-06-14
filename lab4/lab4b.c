#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char* argv[]){
	pid_t x;
	x = fork();
	
	if (x == 0) {
		execvp("./fib", argv);
	} else {
		wait(NULL);
		execvp("./fact", argv);
		//printf("Good job\n");
	}

	return 0;
}