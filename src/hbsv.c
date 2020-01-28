#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define PORT    5000

int main()
{
	int sock = 0;
	socklen_t addr_len = sizeof(struct sockaddr);
	ssize_t bytes_read;
	struct sockaddr_in server_addr, client_addr;
	unsigned short int idx = 0;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server_addr.sin_zero), 8);

	if (bind(sock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == -1) {
		perror(" bind");
		exit(1);
	}

	printf("\n Waiting for client on port 5000\n");
	while (1) {
		bytes_read = recvfrom(sock, &idx, sizeof(unsigned short), 0, (struct sockaddr *) &client_addr, &addr_len);
		if (bytes_read == -1) {
			perror("recvfrom");
			exit(1);
		}
		printf("receive %d bytes data from client: %d\n", bytes_read, idx);
	}
	return 0;
}
