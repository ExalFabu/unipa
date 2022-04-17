#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, void* argv){
	int *status;
	pid_t pid = fork();
	if (pid == 0){
		printf("Child pid: %d\n", (int) getpid()); 
	}
	else {
		printf("Parent pid: %d\n", (int) getpid());
	}
	wait(status);
}
