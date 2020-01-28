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
	ssize_t bytes_read;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_len = sizeof(struct sockaddr_in);
	fd_set fds, readfds;
	struct timeval tv;
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

	FD_ZERO(&readfds);
	FD_SET(sock, &readfds);

	printf("\n Waiting for client on port 5000\n");
	while (1) {
		tv.tv_sec = 0;
		tv.tv_usec = 100 * 1000; // 100ms
		memcpy(&fds, &readfds, sizeof(fd_set));
		if ( 0 > select(sock + 1, &fds, NULL, NULL, &tv)) {
			perror("select");
			exit(1);
		}
		if (FD_ISSET(sock, &fds)) {
			bytes_read = recvfrom(sock, &idx, sizeof(unsigned short), 0, (struct sockaddr *) &client_addr, &addr_len);
			if (bytes_read == -1) {
				perror("recvfrom");
				exit(1);
			}
			printf("receive %d bytes data from client: %d\n", bytes_read, idx);
		} else {
			printf("#### TIMEOUT ####\n");
		}
	}
	close(sock);
	return 0;
}
