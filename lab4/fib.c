#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char* argv[]){
	int n=3;
	if (argc > 1) {
		char * t = (char*) strtok(argv[1], "fib=");
		n = atoi(t);
	}

	int f0 = 1;
	int f1 = 1;
	int i;
	for (i = 3; i <= n; i++) {
		int t = f1;
		f1 = f1 + f0;
		f0 = t;
	}
	printf("fib(%d) = %d\n",n, f1);
	

	return 0;
}
