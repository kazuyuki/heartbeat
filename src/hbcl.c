#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PORT	5000

int main()
{
	int sock;
	struct sockaddr_in server_addr;
	struct hostent *host;
	host = (struct hostent *) gethostbyname((char *) "127.0.0.1");
	unsigned short int idx = 65000;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr = *((struct in_addr *) host->h_addr);
	bzero(&(server_addr.sin_zero), 8);

	while (1) {
		printf("send data to server: %d\n", idx++);
		sendto(sock, &idx, sizeof(short), 0, (struct sockaddr *) &server_addr, sizeof(struct sockaddr));
		usleep(10000);
	}
}
