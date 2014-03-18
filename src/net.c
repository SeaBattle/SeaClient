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

	if(inet_pton(AF_INET, host, sap->sin_addr)<=0)
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
		perror("Err! Can't connect to host %s:%d!\n", host, port);
		return -1;
	}

	return sock;
}

//получает нового клиента
int getNewClient(int *mainSocket)
{
	struct sockaddr_in client_sockaddr;
	int sin_size = sizeof(struct sockaddr_in);

	int sock = accept(*mainSocket, (struct sockaddr*) &client_sockaddr,
	        (socklen_t*) &sin_size);
	if (sock < 0)
	{
		printf("Err! Can't accept connection!\n");
		return -1;
	}
	else
	{
		if (noblock(sock))	//делаем сокет неблокирующим (обязательно)
			return sock;
		else
			return -1;
	}
}

//получает данные от клиента. Возвращает NULL в случае ошибки
char *getPacket(ClientStruct *client)
{
	int len = 65535;
	char buf[len];
	ssize_t recved;

	recved = recv(client->socket, buf, len, 0);

	if (recved < 0)
	{
		//free(buf);
		return NULL;
	}

	return NULL;
}
