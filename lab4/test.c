#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc,char* argv[]){
/*

	10 - parent id
	11 - 1st child id
	12 - p2 child id
	13 - second p2 child id

	  10
	/  | 
   11  12
        |
        13

*/
	int x = 4;
	pid_t p1, p2;
	p1 = fork(); // 4234
	printf("%d\n", x); 
	if (p1 != 0) {
		// parent
		if (p2=fork()) { // 0 = false, 0!= true
			x -= 2;
			wait(NULL);
			printf("%d\n", x);
			exit(0);
		}
		x += 1;
		printf("%d\n", x);
		p2 = fork();
		if (p2 == 0) {
			x++;
			printf("%d\n", x);
			exit(0);
		} else x += 7;
		wait(NULL);
		printf("%d\n", x);
		exit(0);
	}
	return 0;
}