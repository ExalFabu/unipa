#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>    /* bzero(), bcopy() */
#include <time.h>       /* funzioni time() e ctime() */
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>  /* tipi di dati di sistema */
#include <sys/socket.h> /* definizioni utili per le socket() */
#include <netinet/in.h>
#include <arpa/inet.h>

int error(char *msg){
    fprintf(stderr, "Error: %s\n", msg);
    return -1;
}

int main(int argc, char *argv[]) {
    int portno = 0;
    if (argc < 2){
        printf("usage: %s port\n", argv[0]);
        return -1;
    }
    else{
        portno = atoi(argv[1]);
    }
    // socket creation
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // setup socket attributes before binding
    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof socket_address);
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(portno);
    inet_aton("0.0.0.0", &socket_address.sin_addr);
    // end of setup, now bind
    if(bind(sockfd, (struct sockaddr *) &socket_address, (socklen_t) (sizeof socket_address)) < 0)
        return error("bind failed");
    fprintf(stdout, "Succesfully binded to port %d\n", portno);
    
    listen(sockfd, 10);

    // setup client sockaddr variable
    struct sockaddr_in client_address;
    int client_address_len = sizeof client_address;
    memset(&socket_address, 0, client_address_len);
    //fin
    pid_t pid;
    while (1){
        int new_sockfd = accept(sockfd,(struct sockaddr *) &client_address, (socklen_t *) &client_address_len);
        pid = fork();
        if (pid == 0){
            close(sockfd);
            int MAXLEN = 4096;
            char buffer[MAXLEN];
            int byteread = read(new_sockfd, buffer, MAXLEN - 1);
            buffer[byteread] = '\0';
            char *l = buffer;
            while(*l){
                *l = toupper(*l);
                l++;
            }
            int bytesent = write(new_sockfd, buffer, MAXLEN);
            fprintf(stdout, "Echoed %s", buffer);
            close(new_sockfd);
            return 0;
        }
        close(new_sockfd);

    }
}