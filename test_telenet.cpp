#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>

#define HOST_IP "128.149.23.134" //IP address of ssd.jpl.nasa.gov
#define PORTNUM 6775
#define BUFSIZE 512

int main() {
	
	int sockfd, n;
	struct sockaddr_in remote;
	char cmd[3];
	char buffer[BUFSIZE];
	//string host_ip = "ssd.jpl.nasa.gov";

	/* Clear out needed memory */
	memset(buffer, 0, BUFSIZE);
	memset(&remote, 0, sizeof(remote));
	
	/* Fill in required details in the socket structure */
	remote.sin_family = AF_INET;
	remote.sin_port = htons(PORTNUM);
	remote.sin_addr.s_addr = inet_addr(HOST_IP);

	/* Create a socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("bad socket");
		return -1;
	}

	/* Connect to remote host */
	if(connect(sockfd, (struct sockaddr *) &remote, sizeof(remote)) < 0) {
		perror("bad connection");
		return -1;
	}

	//cmd = "?\n";
	n = write(sockfd, "MB\n", 4);
	if (n < 0) perror("ERROR writing to socket");

    /* Receive date information and print it */
    if((n = read(sockfd, &buffer, BUFSIZE - 1)) > 0) {
    	buffer[n] = '\0'; // null terminate the string
	    printf("%s\n",buffer);
	    printf("%d\n",n);
    }
	if(n < 0) {
        perror("bad read");
        return -1;
	}
    if((n = read(sockfd, &buffer, BUFSIZE - 1)) > 0) {
    	buffer[n] = '\0'; // null terminate the string
	    printf("%s\n",buffer);
	    printf("%d\n",n);
    }
	if(n < 0) {
        perror("bad read");
        return -1;
	}

	std::cout << "Hello World!" << std::endl;
	std::cin.get();
	return 0;
}


