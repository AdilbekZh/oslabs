#include <stdio.h>
#include <string.h>

int main(int argc,char* argv[]){
	int n=1;
	int m=1;
	if (argc > 1) {
		char * t = (char*) strtok(argv[1], "fib=");
		n = atoi(t);
	}
	if (argc > 2) {
		char * t = (char*) strtok(argv[2], "fact=");
		m = atoi(t);
	}
	
	printf("fib(%d) = \n",n);
	printf("fact(%d) = \n",m);
	
	return 0;
}
