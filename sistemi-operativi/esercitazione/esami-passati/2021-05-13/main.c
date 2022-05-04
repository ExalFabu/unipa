#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void catch_function(int signo) {
    printf("P3: Ricevuto segnale: %d\n", signo);
}


int main(){

    int pipefd01[2];
    int pipefd12[2];
    int pipefd21[2];
    pipe(pipefd01);
    pipe(pipefd12);
    pipe(pipefd21);

    char buffer[12];
            
    int pid1 = fork();
    if (pid1==0){
        int pid3 = fork();
        if (pid3 == 0){
            // P3
            signal(SIGCONT, catch_function);
            signal(SIGINT, catch_function);
            signal(SIGTERM, catch_function);
            while(1){}        
        }
        else{
            // P1
            read(pipefd01[0], buffer, 12);
            printf("P1: Ricevuto %s\n", buffer);
            int sent = write(pipefd12[1], buffer, 12);
            printf("P1: Sent %d\n", sent);
            int signal_to_send = 0;
            sleep(1);
            read(pipefd21[0], &signal_to_send, 4);
            kill(pid3, signal_to_send);
        }
        
    }
    else{
        int pid2 = fork();
        if (pid2 == 0){
            // P2
            memset(buffer, '\0', 12);
            read(pipefd12[0], buffer, 12);
            printf("P2: Ricevuto %s\n", buffer);
            int signal_to_send = 0;
            switch (buffer[3]){
                case 'T':
                    signal_to_send = 15;
                    break;
                case 'C':
                    signal_to_send = 12;
                    break;
                case 'I': 
                    signal_to_send = 2;
                    break;
                default:
                    signal_to_send = -1;
                    break;
            }
            if (signal_to_send == -1) {
                printf("Inseriscilo giusto, scemo\n");
                exit(-1);
            }
            printf("Signal: %d\n", signal_to_send);
            write(pipefd21[1], &signal_to_send, 4);
        }
        else{
            // P0
            printf("Inserisci il nome del signal tra SIGTERM, SIGCONT, SIGINT: ");
            scanf("%s", buffer);
            printf("Hai inserito %s\n", buffer);
            write(pipefd01[1], buffer, 12);
            
        }
     }
}
     