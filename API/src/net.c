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
short sendPacket(Packet *packet, ssize_t len, int socket)
{
	packet->header.apiVersion = API_VERSION;
	packet->header.protocolVersion = PROTOCOL_VERSION;
	ssize_t sent = send(socket, packet, len, 0);
	return len != sent ? 0 : 1;
}

//получает пакет от сервера. Возвращает 0 в случае ошибки
short recvPacket(Packet *packet, int socket)
{
	int readbytes = 0;
	char buf[sizeof(Packet)];
	char *raw;
	int rawSize = 0;
	do
	{
		readbytes = recv(socket, buf, 512, 0);
		if (readbytes < 0)	//ERROR
		{
			free(packet);
			if(raw)
				free(raw);
			return 0;
		}
		if (readbytes >= 0)	//DATA | EOF
		{
			raw = realloc(raw, rawSize + readbytes);
			for (int i = 0; i < readbytes; i++)
				raw[rawSize+i] = buf[i];
			rawSize+= readbytes;
		}
	} while (readbytes > 0);
	memcpy(packet, raw, rawSize);
	if(raw)
		free(raw);
	return 1;
}
