#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define BUFSIZE 256
#define ERR -1
#define SERVER_PORT 50000

void usage(void);
char* command_name;
char* rindex(const char* s int c);

void main(int argc, char* argv[]){
    int sockfd;
    struct sockaddr_in server;
    struct hostnet* hp;
    char buf[BUFSIZE];
    int msglen;

    if((command_name = rindex(argv[0], '/')) != NULL){
        command_name++;
    }
    else{
        command_name = argv[0];
    }

    if(argc != 3){
        usage();
    }

    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == ERR){
        perror("client : socket");
        exit(1);
    }

    bzero((char*)&server, sizeof(server));
    server.sin_family = PF_INET;
    server.sin_port = htons(SERVER_PORT);
    
    if((hp = gethostbyname(argv[1])) == NULL){
        herror("client : gethostbyname");
        exit(1);
    }
    bcopy(hp->h_addr, (char*)&server.sin_addr, hp->h_length);

    if(connect(sockfd, (struct sockaddr*)&server, sizeof(server)) == ERR){
        perror("client : connect");
        exit(1);
    }

    msglen = strlen(argv[2]) + 1;
    if(write(sockfd, argv[2], msglen) == ERR){
        perror("client : write");
        exit(1);
    }

    if(read(sockfd, buf, BUFSIZE) == ERR){
        perror("client : read");
        exit(1);
    }

    printf("\n<client> message from server : %s\n\n", buf);
    
    close(sockfd);

    exit(0);
}

void usage(void){
    fprintf(stderr, "Usage : %s server_hostname message(CtoS)\n", command_name);
    exit(1);
}