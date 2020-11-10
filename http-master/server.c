/*
    Project includes
*/
#include "functions.h"

/*
    Lib includes
*/

/*
    C includes
*/
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <pthread.h>

#include <arpa/inet.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char *argv[] )
{
    int socketDescriptorClient  = 0;
    int socketDescriptor        = 0;
    pthread_t thread            = 0;
    int socketLength            = 0;
    int socketPort              = 3000;

    struct sockaddr_in  s_server = { 0 };
    struct sockaddr_in  s_client = { 0 };

    if((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("Error creating the socket\n");
        return EXIT_FAILURE;
    }

    s_server.sin_family         = AF_INET;
    s_server.sin_addr.s_addr    = inet_addr("127.0.0.1");
    s_server.sin_port           = htons(socketPort);

    if(bind(socketDescriptor, (struct sockaddr *) &s_server, (socklen_t) sizeof(struct sockaddr_in)) == -1)
    {
        printf("Error at associate port and socket!\n");
        close(socketDescriptor);
        return EXIT_FAILURE;
    }

    if(listen(socketDescriptor, 5) == -1)
    {
        printf("Error at listen!\n");
        close(socketDescriptor);
        return EXIT_FAILURE;
    }

    while(1)
    {
        socketLength = sizeof(struct sockaddr_in);
        if((socketDescriptorClient = accept(socketDescriptor, (struct sockaddr *) &s_client, &socketLength)) != -1)
        {
            if(pthread_create(&thread, NULL, (void *) &fnc_process_request, (void *) ((long) socketDescriptorClient)) != 0)
            {
                fprintf(stderr, "SockedID: %d \t %s\n", socketDescriptorClient, "Error creating thread");
            }
        }
    }

    close(socketDescriptor);
    return EXIT_SUCCESS;
}
