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

short sendPacket(PacketType type, void *packet, ssize_t packetLen, int socket)
{
	//create and fill header
	Header header = HEADER__INIT;
	header.type = type;
	header.apiversion = API_VERSION;
	header.protocol = PROTOCOL_VERSION;

	//create and fill binary tail
	ProtobufCBinaryData data;
	data.len = packetLen;
	data.data = packet;

	//attach binary tail to header
	header.packet = data;

	//pack header (and tail) to buffer
	ssize_t len = header__get_packed_size(&header);
	void *buf = malloc(len);
	header__pack(&header, buf);

	//send buffer
	ssize_t sent = send(socket, buf, len, 0);
	free(buf);
	return len != sent ? 0 : 1;
}

////получает пакет от сервера. Возвращает 0 в случае ошибки
short recvPacket(Header *header, int socket)
{
	void *buf = malloc(MAX_MSG_SIZE);
	ssize_t msg_len = read(socket, buf, MAX_MSG_SIZE);
	if (msg_len < 0)
	{
		free(buf);
		return 0;
	}

	header = header__unpack(NULL, msg_len, buf);
	free(buf);

	return header? 1 : 0;
}
