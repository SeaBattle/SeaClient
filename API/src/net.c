/*
 * net.c
 *
 *  Created on: 01 нояб. 2013 г.
 *      Author: tihon
 */

#include "net.h"

//настраивет порт/адрес/протокол сервера. Возвращает -1 в случае ошибки. 0 - если всё нормально.
short set_address(char *host, int port, struct sockaddr_in *sap)
{
	bzero(sap, sizeof(*sap));
	sap->sin_family = AF_INET;
	sap->sin_port = htons(port);	//задаём порт

	if (inet_pton(AF_INET, host, &sap->sin_addr) <= 0)
	{
		printf("\n inet_pton error occured\n");
		return -1;
	}
	return 0;
}

//делает указанный сокет неблокирующим. Возвращает 0 в случае ошибки.
short noblock(int sfd)
{
	int flags, s;

	flags = fcntl(sfd, F_GETFL, 0);
	if (flags == -1)
	{
		printf("Err! fcntl (noblock)\n");
		return 0;
	}

	flags |= O_NONBLOCK;
	s = fcntl(sfd, F_SETFL, flags);
	if (s == -1)
	{
		printf("Err! fcntl (noblock with flag)\n");
		return 0;
	}

	return 1;
}

//настраивает серверный сокет. Возвращает -1 в случае ошибки. Сокет - в другом случае.
int create_client_sock(char *host, int port)
{
	struct sockaddr_in serv_addr;
	int sock;
	const int on = 1;

	set_address(host, port, &serv_addr);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("Err! Can't make the socket!\n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
	{
		printf("Err! Can't connect to host %s:%d!\n", host, port);
		return -1;
	}

	return sock;
}

//отправляет пакет на сервер. Возвращает 0 в случае ошибки
short sendPacket(void *packet, ssize_t len, int socket)
{
	char *buf = packet;

	while (len > 0)
	{
		ssize_t written = send(socket, buf, len, 0);
		if (written < 0) return 0;
		len -= written;
		buf += written;
	}
	return 1;
}

//получает пакет от сервера. Возвращает NULL в случае ошибки
void *recvPacket(int socket)
{
	int size = 0;
	if (recv(socket, &size, 512, 0) < 0) return 0;

	char *packet = malloc(size);

	int readbytes = 0;
	char buf[512];
	ssize_t read = 0;
	do
	{
		readbytes = recv(socket, buf, 512, 0);
		if (readbytes < 0)	//ERROR
		{
			free(packet);
		    return NULL;
		}
		if (readbytes >= 0)	//DATA | EOF
		{
			for (int i = 0; i < readbytes; i++)
			{
				*packet++ = buf[i];
			}
		}
	} while (readbytes > 0);

	return packet;
}
