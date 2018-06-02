#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "utils.h"

#define SRV_IP "127.0.0.1"

int main(void)
{
	struct sockaddr_in si_other;
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);

	if (inet_aton(SRV_IP, &si_other.sin_addr) == 0)
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == -1)
	{
		exit_error("socket");
	}

	socklen_t sock_len = sizeof(si_other);
	char buf[BUFLEN];

	for (int i = 0; i < NPACK; i++)
	{
		printf("Sending packet %d\n", i);
		sprintf(buf, "This is packet %d\n", i);

		if (sendto(sock, buf, BUFLEN, 0, (struct sockaddr *) &si_other, sock_len) == -1)
		{
			exit_error("sendto()");
		}
	}

	close(sock);
	return 0;
}
