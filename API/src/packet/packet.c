/*
 * packet.c
 *
 *  Created on: 17 апр. 2014 г.
 *      Author: tihon
 */

#include "packet.h"

//Кодирует тело пакета согласно типу.
ProtobufCBinaryData encodePacketBody(Packet *packet)
{
	//form and create packet body
	void *bodyRaw;
	ssize_t len;

	ProtobufCBinaryData data;

	//encode packet body, depending on type
	switch (packet->header.type)
	{
		case guestAuth:
			bodyRaw = encodeGuestPacket(&len, &packet->guestAuthPacket);
			break;
		case loginAuth:
			bodyRaw = encodeLoginPacket(&len, &packet->loginAuthPacket);
			break;
		default:
			perror("Unknown packet type!");
			data.data = NULL;
			return data;
	}

	//create and fill binary tail
	data.len = len;
	data.data = bodyRaw;	//is freed here, on line 74
	return data;
}

//Декодирует тело пакета согласно типу.
short decodePacketBody(Header *header, Packet *packet)
{
	switch (packet->header.type)
	{
		case error:
			decodeErrorPacket(&header->packet, &packet->errorPacket);
			if (!&packet->errorPacket) return 0;
			break;
		case authResp:
			break;
		default:
			perror("Unknown packet type!");
			return 0;
	}
	return 1;
}

//Упаковывает пакет в структуру {длина, бинарные данные}
NetPacket *composePacket(Header *header)
{
	//pack header (and tail) to buffer
	ssize_t bodyLen = header__get_packed_size(header);
	char *body = malloc(bodyLen);
	header__pack(header, body);

	//make a header - sizeof byte body
	long lenToSend = isBigEndian() ? htonl(bodyLen) : bodyLen;
	char size[HEADER_LENGTH];
	longToByte(size, lenToSend);

	//compose packet: first 4 bytes - length of packet, rest - packet's body
	char *fullPacket = malloc(HEADER_LENGTH + bodyLen);
	for (int i = 0; i < HEADER_LENGTH; i++)
		fullPacket[i] = size[i];
	for (int i = 0; i < bodyLen; i++)
		fullPacket[HEADER_LENGTH + i] = body[i];

	//free unneeded data
	free(header->packet.data);
	free(body);

	//compose net packet
	NetPacket *pack = malloc(sizeof(NetPacket));
	pack->len = HEADER_LENGTH + bodyLen;
	pack->body = fullPacket;
	return pack;
}

//Переводит long-значение в 4-е байта
void longToByte(char *result, long value)
{
	result[0] = (int) ((value & 0xFF000000) >> 24);
	result[1] = (int) ((value & 0x00FF0000) >> 16);
	result[2] = (int) ((value & 0x0000FF00) >> 8);
	result[3] = (int) ((value & 0X000000FF));
}

//Переводит 4-е байта в long-значение
long byteToLong(char *value)
{
	return ((value[0] << 24) + (value[1] << 16) + (value[2] << 8) + (value[3]));
}

//Проверяет endianness. 0 - little, 1 - big
short isBigEndian()
{
	int i = 1;
	char *p = (char *) &i;
	return 1 - p[0];
}
