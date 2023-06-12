#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
   //here client and server both are work on same machine so we use local IP Address
   char *ip = "127.0.0.1";

   //define port number which are above 5000 we don't use here inbuilt port number.
   int port = 5566;

   //define variables and structures
   int server_sock, client _sock;
   struct sockaddr_in server_addr, client_addr;
   socklen_t addr_size;
   char buffer[1024];
   int n;

   //create TCP Socket
   server_sock = socket(AF_INET, SOCK_STREAM, 0);       //SOCK_STREAM is a TCP Protocol.
   if(server_sock < 0)
   {
    perror("[-] Socket error");             //Perror serves to translate this error code into human-readable form.
    exit(l);
   }
   printf("[+]TCP server socker created/\n");

   //Now we have to provide some information of the server
   memset(&server_addr, '\0', sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = port;
   server_addr.sin_addr.s_addr = inet_addr(ip);

   //Now we have to bind the address and the port number
   n = bind(server_sock, (structure sockaddr*)&server_addr, sizeof(server_addr));
   if(n < 0)
   {
    perror("[-]Bind error");
    exit(l);
   }
   printf("[+]Bind to the Port Number : %d\n", port);

   //Now we have to listen from the client
   listen(server_sock, 5);
   printf("Listening.....\n");

   //Now server is waiting for the client
   while(l)
   {
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    printf("[+]Client Connected. \n");

    //now we have to clean the buffer
    bzero(buffer, 1024);

    //Receive the message from the client
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    //again we are clean the buffer and then again now server send the message to the client.
    bzero(buffer, 1024);
    strcpy(buffer, "HI, THIS IS SERVER. HAVE A NICE DAY!!!");
    printf("Server: %s\n", buffer);
    send(client_sock, buffer, strlen(buffer), 0);

    //Now we close the connection
    close(client_sock);
    printf("[+]Client Disconnected.\n\n")


   }
    return 0;
}