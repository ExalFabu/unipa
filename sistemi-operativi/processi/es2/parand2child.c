#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, void* argv){
	int *status;
	pid_t pid1, pid2;
	if (pid1 = fork() == 0){
		printf("Child pid: %d\n", (int) getpid()); 
	}
	else {
		if (pid2 = fork() == 0){
			printf("Child pid: %d\n", (int) getpid()); 
		}
		else{
		printf("Parent pid: %d\n", (int) getpid());
		}
	}
	waitpid(pid1, status, 0);
	waitpid(pid2, status, 0);
}
