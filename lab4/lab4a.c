#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char* argv[]){
	int n=3;
	int m=1;
	if (argc > 1) {
		char * t = (char*) strtok(argv[1], "fib=");
		n = atoi(t);
	}
	if (argc > 2) {
		char * t = (char*) strtok(argv[2], "fact=");
		m = atoi(t);
	}
	
	pid_t x;
	x = fork();
	
	if (x == 0) {
		int f0 = 1;
		int f1 = 1;
		int i;
		for (i = 3; i <= n; i++) {
			int t = f1;
			f1 = f1 + f0;
			f0 = t;
		}
		printf("fib(%d) = %d\n",n, f1);
		
	} else {
		wait(NULL);
		int t = 1;
		int i;
		for (i = 2; i <= m; i++) {
			t *= i;	
		}
		printf("fact(%d) = %d\n", m, t);
		
		printf("Good job\n");
	}

	return 0;
}
