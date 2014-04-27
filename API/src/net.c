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

//создаёт бинарный сетевой пакет и возвращает его структуру
NetPacket *encode(Packet *packet)
{
	//create and fill header
	Header header = HEADER__INIT;
	header.type = packet->header.type;
	header.apiversion = API_VERSION;
	header.protocol = PROTOCOL_VERSION;

	//attach binary tail to header
	ProtobufCBinaryData data = encodePacketBody(packet);
	if(!data.data)
		return NULL;
	header.packet = data;

	//compose and return packet
	return composePacket(&header);
}

//декодирует бинарный пакет в протобуф пакет, а потом в нативный Packet.
//Возвращает 1 в случае успеха и 0 в случае ошибки.
short decode(Packet *packet, NetPacket *rawPacket)
{
	//unpack header
	Header *header = header__unpack(NULL, rawPacket->len, rawPacket->body);
	if(!header)
	{
		perror("Can't unpack header!");
		return 0;
	}

	//fill native packet's header
	packet->header.type = header->type;
	packet->header.protocolVersion = header->protocol;
	packet->header.apiVersion = header->apiversion;

	//decode packet's body
	if(!decodePacketBody(header, packet))
	{
		header__free_unpacked(header, NULL);
		return 0;
	}

	//free header
	header__free_unpacked(header, NULL);
	return 1;
}

//отправляет пакет формата {длина, данные} по сокету до тех пор, пока не отправит всё
//возвращает 1 - если всё хорошо и 0 при ошибке
short sendData(NetPacket *packet, int socket)
{
	ssize_t dataToSend = packet->len;
	ssize_t sentData = 0;

	while (dataToSend > 0)
	{
		ssize_t ret = send(socket, &packet->body[sentData], dataToSend, 0);

		if (ret == 0) break;
		if (ret == -1)
		{
			perror("Error sending data!\n");
			return 0;
		}
		dataToSend -= ret;
		sentData += ret;
	}
	return 1;
}

//получает весь пакет формата {длина, данные}. Возвращает пакет в случае успеха
//и NULL в случае ошибки. Important! Returned packet should be freed later.
NetPacket * recvData(int socket)
{
	char msgLen[4];
	ssize_t readDataLen = read(socket, msgLen, 4);
	if (readDataLen <= 0)
	{
		perror("Can't read data!\n");
		return 0;
	}
	ssize_t packetLen = byteToLong(msgLen);
	ssize_t dataToRead = packetLen;
	ssize_t readData = 0;

	char *buf = malloc(packetLen);

	while (dataToRead > 0)
	{
		ssize_t ret = read(socket, &buf[readData], dataToRead);

		if (ret == 0) break;
		if (ret == -1)
		{
			perror("Error sending data!\n");
			free(buf);
			return NULL;
		}

		dataToRead -= ret;
		readData += ret;
	}

	NetPacket *rawData = malloc(sizeof(NetPacket));
	rawData->len = packetLen;
	rawData->body = buf;

	return rawData;
}

//освобождает память, занимаемую пакетом
void freePacket(NetPacket *packet)
{
	free(packet->body);
	free(packet);
}
