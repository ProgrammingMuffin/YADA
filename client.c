#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<errno.h>

int main( )
{
    int sock, bytes;
    struct in_addr p;
    struct sockaddr_in Server;
    char msg[100];
    char cmd[50];
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error creating a socket: ");
        exit(-1);
    }
    
    Server.sin_addr.s_addr = INADDR_ANY;
    Server.sin_port = htons(9001);
    Server.sin_family = AF_INET;
    
    if(connect(sock, (struct sockaddr *)&Server, sizeof(Server)) == -1)
    {
        perror("Error connecting to server: ");
        exit(-1);
    }
    
    bytes = recv(sock, msg, 100, 0);
    printf("\n\t%d bytes sent from server\n", bytes);
    printf("\n\tMessage: %s\n", msg);
    printf("\n\tEnter the command: ");
    scanf("%s", cmd);
    bytes = send(sock, cmd, strlen(cmd), 0);
    printf("\n\t%d bytes sent to server\n", bytes);
    
    close(sock);
    
    return 0;
}
