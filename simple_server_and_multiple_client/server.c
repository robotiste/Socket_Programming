/*
@author Vikas Kamboj <kambojvikas0043@gmail.com>
@organisation Cluster Innovation Centre
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#define PORT 8080

#define MAX_SIZE 50
#define NUM_CLIENT 100

void *connection_handler(void *threadid)
{
	int threadnum = *((int*)(&threadid));
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "   ";

     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        
       
        printf("thread number : %d\n", threadnum);
        valread = read( new_socket , buffer, 1024);
        printf("%s\n",buffer );
       
        send(new_socket , hello , strlen(hello) , 0 );
       
        
    }
    return 0;
}

     

int main(int argc, char const *argv[])
{
    pthread_t thread;

    for(int i = 1; i<= NUM_CLIENT; i++)
    {
    	if(pthread_create(&thread, NULL, connection_handler,(void*)i) < 0)
    	{
    		perror("thread is not created");
    		return 1;
    	}
    	sleep(3);
    }
    pthread_exit(NULL);
    return 0;
}

    
      
    