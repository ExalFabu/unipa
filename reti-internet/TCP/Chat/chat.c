
//Il numero di porta è passato come parametro

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
// #include <string.h>
#include <time.h>       /* funzioni time() e ctime() */
#include <unistd.h>
#include <sys/types.h>  /* tipi di dati di sistema */
#include <sys/socket.h> /* definizioni utili per le socket() */
#include <netinet/in.h>

void error(char *msg){
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[]) {

  if (argc < 2){
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }

  // creo la socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0){
    error("ERROR opening socket");
  }

  // binding. La socket è ancora CLOSED
  struct sockaddr_in serv_addr;
  bzero((char *) &serv_addr, sizeof(serv_addr));
  int portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if (bind(sockfd, &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");

  // listen
  listen(sockfd, 5);

  int newsockfd1, newsockfd2;
  pid_t pid;
  int clilen;
  char buffer[256];
  struct sockaddr_in cli_addr[2];
  int n;
  int counter = 0;

  do{
    // accept 1
    clilen = sizeof(cli_addr[0]);
    newsockfd1 = accept(sockfd, (struct sockaddr *) &cli_addr[0], (socklen_t *)&clilen);
    if (newsockfd1 < 0)
      error("ERROR on accept");
    // fputs("Primo client connesso con successo", stdout);
    // write(newsockfd1, "In attesa dell'altro...", 24);
    // accept 2
    newsockfd2 = accept(sockfd, (struct sockaddr *) &cli_addr[1], (socklen_t *)&clilen);
    if (newsockfd2 < 0)
      error("ERROR on accept");
    // fputs("Secondo client connesso con successo", stdout);

    // fork
    pid = fork();

    // se pid == 0 siamo nella socket figlia
    if (pid == 0){
      close(sockfd);
      while(1){
        bzero(buffer, 256);
        write(newsockfd1, "Manda un messaggio: ", 20);
        n = read(newsockfd1, buffer, 255);
        if(strcmp("QUIT\n", buffer) == 0) break;
        if (n < 0)
          error("ERROR reading from socket");
        write(newsockfd2, buffer, n+1);

        bzero(buffer, 256);
        write(newsockfd2, "Manda un messaggio: ", 20);
        n = read(newsockfd2, buffer, 255);
        if(strcmp("QUIT\n", buffer) == 0) break;
        if (n < 0)
          error("ERROR reading from socket");
        write(newsockfd1, buffer, n+1);
      }
    close(newsockfd1);
    close(newsockfd2);
    return 0;
    }
    close(newsockfd1);
    close(newsockfd2);
  } while (1);
  return 0;
}
