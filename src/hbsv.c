/*
 * Usage:
 *
 *	hbsv PORT_SELF PORT_TARGET
 *
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
	int sock = 0;
	ssize_t bytes_read;
	struct hostent *host;
	struct sockaddr_in server_addr, client_addr, reply_addr;
	socklen_t addr_len = sizeof(struct sockaddr_in);
	fd_set fds, readfds;
	struct timeval tv;
	unsigned short int idx = 0;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	host = (struct hostent *) gethostbyname((char *) "127.0.0.1");
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(atoi(argv[2]));
	client_addr.sin_addr = *((struct in_addr*) host->h_addr);
	bzero(&(client_addr.sin_zero), 8);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[1]));
	server_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server_addr.sin_zero), 8);
	if (bind(sock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == -1) {
		perror(" bind");
		exit(1);
	}

	FD_ZERO(&readfds);
	FD_SET(sock, &readfds);

	printf("\nReceiving on port %s\n", argv[1]);
	while (1) {
		// fds ad tv need to re-set cz these are destroyed on select()
		tv.tv_sec = 0;
		tv.tv_usec = 3000 * 1000;	// 3000ms
		memcpy(&fds, &readfds, sizeof(fd_set));
		if (0 > select(sock + 1, &fds, NULL, NULL, &tv)) {
			perror("select");
			exit(1);
		}
		if (FD_ISSET(sock, &fds)) {
			addr_len = sizeof(struct sockaddr_in);
			bytes_read = recvfrom(sock, &idx, sizeof(unsigned short), 0, (struct sockaddr *) &reply_addr, &addr_len);
			if (bytes_read == -1) {
				perror("recvfrom");
				exit(1);
			}
			//printf("receive %d bytes data from %s:%d idx = %d\n",
			//	bytes_read, inet_ntoa(reply_addr.sin_addr), ntohs(reply_addr.sin_port), idx);

			idx++;

		}
		else {
			printf("#### TIMEOUT ####\n");
		}

		addr_len = sizeof(struct sockaddr_in);
		sendto(sock, &idx, sizeof(unsigned short), 0, (struct sockaddr*) &client_addr, addr_len);
		printf("sent    %d bytes data to   %s:%d idx = %d\n",
			sizeof(short), inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), idx);

		usleep(2000*1000);	// 2000ms
	}
	close(sock);
	return 0;
}
