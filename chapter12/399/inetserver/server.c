#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define BUFSIZE     256
#define ERR         -1
#define SERVER_PORT 50000

void usage(void);
char* command_name;
//char* rindex(const char* s, int c);

void main(int argc, char* argv[]){
    int sockfd;
    int ns;
    struct sockaddr_in server;
    struct sockaddr_in client;

    int fromlen;
    char buf[BUFSIZE];
    int msglen;
    
    if((command_name = rindex(argv[0], '/')) != NULL){
        command_name++;
    }
    else{
        command_name = argv[0];
    }

    if(argc != 2){
        usage();
    }

    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == ERR){
        perror("server : socket");
        exit(1);
    }

    bzero((char*)&server, sizeof(server));
    server.sin_family = PF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr*)&server, sizeof(server)) == ERR){
        perror("server : bind");
        exit(1);
    }

    if(listen(sockfd, 5) == ERR){
        perror("server : listen");
        exit(1);
    }

    fromlen = sizeof(client);
    if((ns = accept(sockfd, (struct sockaddr*)&client, &fromlen)) == ERR){
        perror("server : accept");
        exit(1);
    }

    printf("\nconnect request from : %s\n", inet_ntoa(client.sin_addr));
    printf("port : %d\n", ntohs(client.sin_port));

    if(read(ns, buf, BUFSIZE) == ERR){
        perror("server : read");
        exit(1);
    }

    printf("\n<server> message from client : %s\n", buf);
    
    msglen = strlen(argv[1]) + 1;

    if(write(ns,argv[1], msglen) == ERR){
        perror("server : write");
        exit(1);
    }

    close(ns);
    close(sockfd);

    exit(0);
}

void usage(void){
    fprintf(stderr, "Usage : %s message(StoC)\n", command_name);
    exit(1);
}