#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    char *ip = "127.0.0.l";
    int port = 5566;

    int sock;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("[-]Socket error");
        exit(l);
    }
    printf("[+]TCP server socket created.\n");

    memset(&server_addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);

    //Now Connect to the server
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    printf("Connected to the server. \n");

    //So Till now we successfully connect the client to the server and client can send message to the server.

    //Now we are going to empty the buffer
    bzero(buffer, 1024);
    //Copy some value to the buffer
    strcpy(buffer, "HELLO, THIS IS CLIENT");
    printf("CLIENT: %s\n", buffer);

    //Now we send this message to the server
    send(sock, buffer, strlen(buffer), 0);

    //Receive message from the server
    //for that first of all clean the buffer
    bzero(buffer, 1024);
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    //Now we are going to disconnect
    close(sock);
    printf("Disconnected from the server. \n\n");

    return 0;
}