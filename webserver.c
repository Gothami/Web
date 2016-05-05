#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>


#define LENGTH 512

int main(){
    int createSocket, newSocket;
    socklen_t addrlen;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    struct sockaddr_in address;
    struct stat stat_buf;
    //int lenght;

    if((createSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket failed!");
    }else {
        return 1;
        printf("The socket was created\n");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8014);
    if(bind(createSocket, (struct sockaddr *) &address, sizeof(address)) == 0){
        printf("Binding Socket\n");
    }

    while(1){
        if (listen(createSocket, 10) < 0){
            perror("server: listen");
            exit(1);
        }

    if((newSocket = accept(createSocket,(struct sockaddr *) &address, &addrlen)) < 0){
        perror("server : accept");
        exit(1);
    }

    if(newSocket > 0){
        printf("The client is connected...\n");

}
    recv(newSocket, buffer, bufsize, 0);
    char *token = strtok(buffer, " ");
        token = strtok(NULL, " ");
        //printf("%s\n",token);
        char fullpath[20];
        char sdbuf[LENGTH];
        char *type;
        char *extension;
        char phpCommand[50];
        FILE* f;
        FILE* pipein_fp;
        FILE* pipeout_fp;
        char readbuf[800];

        if(strcmp(token,"/")==0)
        {
            strcpy(fullpath, "/home/gothami/Desktop/WebServer/Files");
            strcat(fullpath, "/index.html");
            type = "text/html";
            //printf("%s\n",fullpath);
        }
        else{
            strcpy(fullpath, "/home/gothami/Desktop/WebServer/Files");
            char* filename = token;
            strcat(fullpath, token);
            printf("%s\n",fullpath);
            extension = strsep(&token, ".");
            printf("%s\n",token);
            int s=strlen(token);
            printf("%d\n",s);
            if(strcmp(token, "html")==0)
            {
                type = "text/html";
                printf("%s\n",type);
            }
            else if(strcmp(token, "txt")==0)
            {
                type = "text/plain";
            }
            else if(strcmp(token, "jpeg")==0)
            {
                type = "image/jpeg";
            }
            else if(strcmp(token, "png")==0)
            {
                type = "image/png";
            }
            else if(strcmp(token, "mp4")==0)
            {
                type = "video/mp4";
            }
            else if(strcmp(token, "php")==0)
            {
                //strcpy(phpCommand,"php -f ")
                type = "text/php";
                printf(" PHP interpret",1);

            }
            else{
            type = "text/nf";
            printf("Not found");
            }
        }

    off_t offset = 0;
    char header[100];
    int fd = open(fullpath, O_RDONLY);
    int msgSize = sizeof(fd);
    if (fd == -1) {
      sprintf(header, "HTTP/1.1 404 FILE NOT FOUND\n Content-Type: %s; charset=utf-8  \n\n", type);
    }

    else{
    fstat(fd, &stat_buf);
    sprintf(header, "HTTP/1.1 200 OK\n Content-Type: %s; charset=utf-8  \n\n", type);}
    int sizeMsg = strlen(header);
    write(newSocket, header, sizeMsg);

    /* copy file using sendfile */
    offset = 0;
    printf("SEND FILE interpret");
    sendfile (newSocket, fd, &offset, stat_buf.st_size);
    close(newSocket);
    close(fd);
}
return 0;
}

