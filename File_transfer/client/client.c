/*
@author Vikas Kamboj <kambojvikas0043@gmail.com>
@organisation Cluster Innovation Centre
*/

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
    //char IP_ADDRESS[20];
    //scanf("%s", IP_ADDRESS);
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    //char *hello = "Hello from client";
    char hii[200];
    char download_path[200];  
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }


    FILE *fptr;

    while (1)
    {
        printf("enter path\n");
        scanf("%s", hii);
        //send(sock , hello , strlen(hello) , 0 );
        send(sock , hii , strlen(hii) , 0 );
        printf("enter path where you want to download\n");
        scanf("%s", download_path);
        fptr = fopen(download_path,"w");

        //printf("Message sent\n");
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
        fprintf(fptr,"%s\n",buffer);
        fclose(fptr);

    }
    return 0;
}
