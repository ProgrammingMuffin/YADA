#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main( )
{
	int sock, cli, *len;
    int bytes;
    struct sockaddr_in Server, Client;
    char cmd[50];
    char msg[] = "Deepak Ramachandran is a really cool computer programmer.";
    
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error creating socket: ");
        exit(-1);
    }
    
    Server.sin_port = htons(9001);
    Server.sin_addr.s_addr = INADDR_ANY;
    Server.sin_family = AF_INET;
    
    if(bind(sock, (struct sockaddr *)&Server, sizeof(Server)) == -1)
    {
        perror("Error binding address to a socket: ");
        exit(-1);
    }
    
    if(listen(sock, 10) == -1)
    {
        perror("Error listening: ");
        exit(-1);
    }
    
    RELISTEN:
    
    if((cli = accept(sock, (struct sockaddr *)&Client, len)) == -1)
    {
        perror("Error accepting connection: ");
        exit(-1);
    }
    
    bytes = send(cli, msg, strlen(msg), 0);
    printf("\n\t%d bytes sent to client\n", bytes);
    bytes = recv(cli, cmd, 50, 0);
    printf("\n\t%d bytes recieved from client\n", bytes);
    
    if(strcmp(cmd, "continue") == 0)
        goto RELISTEN;
    else
        printf("\n\tClient told me to quit, so I did. Bye!\n");
    
    close(sock);
    
	return 0;
}
