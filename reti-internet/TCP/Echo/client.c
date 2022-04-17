
#include <stdio.h>
#include <stdlib.h>     /* exit() */
#include <strings.h>    /* bzero(), bcopy() */
#include <string.h>    /* bzero(), bcopy() */
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    // Esercizio 1: stampare a schermo i dati di rete del processo (che posso sapere)
    struct sockaddr_in socket_address;
    getsockname(sockfd, (struct sockaddr *) &socket_address, (socklen_t *) (sizeof socket_address));
    char ip_socket[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(socket_address.sin_addr), ip_socket, INET_ADDRSTRLEN);
    int socket_port = ntohs(socket_address.sin_port);
    printf("La socket sta comunicando attraverso %s:%d\n", ip_socket, socket_port);
    // fin
    printf("Please enter the command: ");
	bzero(buffer,256);
    fgets(buffer,255,stdin);


	n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
         error("ERROR writing to socket");

	bzero(buffer,256);
	n = read(sockfd,buffer,255);
    if (n < 0)
         error("ERROR reading from socket");
    printf("%s\n",buffer);

	close(sockfd);

    return 0;
}
