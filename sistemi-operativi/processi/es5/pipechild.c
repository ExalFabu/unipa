#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>


int main(int argc, void* argv){
	int *status;
	int pipef1[2];
	int pipef2[2];
	pipe(pipef1);
	pid_t f1 = fork();
	if (f1 == 0){
		srand(time(NULL));
		pid_t child_pid = getpid();
		close(pipef1[0]);
		int num = rand() % 100;
		write(pipef1[1], &num, sizeof(int));
	}
	else {
		pipe(pipef2);
		pid_t f2 = fork();
		if (f2 == 0){
			close(pipef2[1]);
			int num_echoed;
			read(pipef2[0], &num_echoed, sizeof(int));
			printf("Num echoed: %d\n", num_echoed);
		}
		else{
			int num_rcvd;
			close(pipef1[1]);
			read(pipef1[0], &num_rcvd, 4);
			printf("Numero letto da P: %d\n", num_rcvd);
			close(pipef2[0]);
			write(pipef2[1], &num_rcvd, sizeof(int));
		}
	}
	
}
