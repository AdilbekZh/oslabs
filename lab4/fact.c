#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char* argv[]){
	int m=3;
	
	if (argc > 2) {
		char * t = (char*) strtok(argv[2], "fact=");
		m = atoi(t);
	}

	int t = 1;
	int i;
	for (i = 2; i <= m; i++) {
		t *= i;	
	}
	printf("fact(%d) = %d\n", m, t);
	printf("Good job\n");

	return 0;
}
