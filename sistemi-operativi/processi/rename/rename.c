#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
int main (){
    int pipefd[2], status;
    pipe(pipefd);
    int pid = fork();
    if (pid == 0){
        char buffer[255];
        close(pipefd[1]);
        read(pipefd[0], buffer, sizeof(buffer));
        execl("/bin/mv", "mv", "test.from", buffer, '\0');
    }
    else{
        close(pipefd[0]);
        char nameto[] = "test.to";
        write(pipefd[1], nameto, sizeof(nameto));
        wait(&status);
    }
}