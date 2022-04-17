
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

int main(int argc, char const *argv[])
{
    /*
    server udp:
        - socket
        - bind
        - recvfrom/sendto
    client udp:
        - socket
        - sendto/recvfrom
    */
    if (argc < 2) return -1;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // creo la struttura dati per poterlo bindare
    struct sockaddr_in myaddr;
    int addrlen = sizeof myaddr;
    memset(&myaddr, 0, addrlen);
    myaddr.sin_port = htons(atoi(argv[1]));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = INADDR_ANY;
    if ( bind(sockfd, &myaddr, addrlen) < 0) return -1; // cast implicito :)
    printf("bind funzionato\n");
    return 0;
}
