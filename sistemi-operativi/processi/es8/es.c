#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

int main(int argc, void* argv){
	int *status;
	int pipef1[2];
	int pipef2[2];
	pipe(pipef1);
	pid_t f1 = fork();
	if (f1 == 0){
        // F1
		close(pipef1[0]);
		int num;
        printf("F1: Inserisci il numero del segnale: ");
        scanf("%d", &num);
		write(pipef1[1], &num, sizeof(int));
	}
	else {
		pipe(pipef2);
		pid_t f2 = fork();
		if (f2 == 0){
            // F2
			close(pipef2[1]);
			int signum;
			read(pipef2[0], &signum, sizeof(int));
            printf("F2: Inserisci il PID del processo a cui vuoi mandare (%d): ", signum);
            int pid_num;
            scanf("%d", &pid_num);
            kill(pid_num, signum);
			printf("kill(%d, %d);\n", pid_num, signum);
		}
		else{
            // P
			int num_rcvd;
			close(pipef1[1]);
			read(pipef1[0], &num_rcvd, sizeof(int));
			printf("P: Numero letto da F1: %d\n", num_rcvd);
			close(pipef2[0]);
			write(pipef2[1], &num_rcvd, sizeof(int));
            waitpid(f2, status, 0);
		}
	}
	
}
