/*
* Manos Chatzakis, csd4238@csd.uoc.gr
*/
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define set_deadlines(a1,a2,a3) syscall(341, a1,a2,a3)

int main(){

	pid_t pid1,pid2,pid3;

	/*Some trivial tests - For parent*/
	printf("[ERROR]  - Ret val: %d\n",set_deadlines(1,2,3));
	printf("[ERROR]  - Ret val: %d\n",set_deadlines(100,10,2));
	printf("[SUCCESS]- Ret val: %d\n",set_deadlines(-1,10,2));
	printf("[SUCCESS]- Ret val: %d\n",set_deadlines(getpid(),10,2));

	if((pid1 = fork()) == 0){
		//Child 1 call set_deadlines with a random pid.
		printf("[ERROR]  - Ret val: %d\n",set_deadlines(10000000,10,20));
		exit(0);
	}
	else{
		if((pid2 = fork()) == 0){
			if((pid3 = fork()) == 0){
				exit(0);
			}
			else{
				//Child 2 sets deadlines for its child.
				printf("[SUCCESS]- Ret val: %d\n",set_deadlines(pid3,15,5));
				exit(0);
			}
		}
		else{
			//Parent sets deadlines for his two children
			printf("[SUCCESS]- Ret val: %d\n",set_deadlines(pid1,5,2));
			printf("[SUCCESS]- Ret val: %d\n",set_deadlines(pid2,3,1));

		}
	}

	return 0;
}
