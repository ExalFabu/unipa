#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>


int main(int argc, void* argv){
	int *status;
	int pipefd[2];
	pipe(pipefd);
	pid_t pid = fork();
	if (pid == 0){
		srand(time(NULL));
		pid_t child_pid = getpid();
		close(pipefd[0]);
		int num = rand() % 100;
		write(pipefd[1], &num, sizeof(int));
	}
	else {
		int num_rcvd;
		close(pipefd[1]);
		read(pipefd[0], &num_rcvd, 4);
		printf("Numero randomico: %d\n", num_rcvd);
	}
	wait(status);
}
