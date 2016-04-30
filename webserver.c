#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int createSocket, newSocket;
    socklen_t addrlen;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    struct sockaddr_in address;

    if((createSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket failed!");
        return 1;
    }else {
        printf("The socket was created\n");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(15000);

    if(bind(createSocket, (struct sockaddr *) &address, sizeof(address)) == 0){
        printf("Binding Socket\n");
    }

    while(1){
        if (listen(createSocket, 10) < 0){
            perror("server: listen");
            exit(1);
        }

    if(newSocket = accept(createSocket,(struct sockaddr *) &address, &addrlen) < 0){
        perror("server : accept");
        exit(1);
    }

    if(newSocket > 0){
        printf("The client is connected...\n");
    }

    recv(newSocket, buffer, bufsize, 0);
    printf("%s\n", buffer);
    write(newSocket, "Hello World\n", 12);
    close(newSocket);

}close(createSocket);
return 0;
}
