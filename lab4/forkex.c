// Parent forks a child and runs in parallel with child, waiting for the child to complete.
// see manpages for fork, wait, sleep and exit system calls
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{
	pid_t fac_pid; // =int
	pid_t fib_pid;
	// fork a child process
	fac_pid = fork(); //fork creates a child and returns the pid of child to parent
	fib_pid = fork();
	if (fac_pid == 0) {
		int t = 1;
		int i;
		for (i = 2; i <= 5; i++) {
			t *= i;
		}
		printf("Factorial: %d\n", t);
	}
	if (fib_pid == 0){
		int f0 = 1;
		int f1 = 1;
		int i;
		for (i = 3; i <= 5; i++) {
			int t = f1;
			f1 = f1 + f0;
			f0 = t;
		}
		printf("Fibonacci: %d\n", f1);
	}
	//wait(NULL);
	//printf("Factorial id: %d\n",fac_pid);
	//printf("Fibonacci id: %d\n",fib_pid);

	return 0;
}