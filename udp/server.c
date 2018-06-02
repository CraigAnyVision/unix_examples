#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "utils.h"

int main(void)
{
	struct sockaddr_in si_me;
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == -1)
	{
		exit_error("socket");
	}

	if (bind(sock, (const struct sockaddr *) &si_me, sizeof(si_me)) == -1)
	{
		exit_error("bind");
	}

	struct sockaddr_in si_other;
	socklen_t sock_len = sizeof(si_other);
	char buf[BUFLEN];

	for (int i = 0; i < NPACK; i++)
	{
		if (recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &sock_len) == -1)
		{
			exit_error("recvfrom()");
		}

		printf("Received packet from %s:%d\nData: %s\n\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);
	}

	close(sock);
	return 0;
}
