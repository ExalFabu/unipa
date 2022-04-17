#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, void* argv){
	int *status;
	int pipefd[2];
	pipe(pipefd);
	pid_t pid = fork();
	if (pid == 0){
		pid_t child_pid = getpid();
		close(pipefd[0]);
		write(pipefd[1], (int *)&child_pid, 4);
	}
	else {
		pid_t child_pid_rcvd;
		close(pipefd[1]);
		read(pipefd[0], &child_pid_rcvd, 4);
		printf("Parent pid: %d\n", (int) child_pid_rcvd);
	}
	wait(status);
}
