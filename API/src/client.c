/*
 * client.c
 *
 *  Created on: 17 апр. 2014 г.
 *      Author: tihon
 */

#include "client.h"

//отправляет пакет на сервер. Возвращает 0 в случае ошибки
short sendPacket(Packet *packet, int socket)
{
	//encode packet
	NetPacket *rawPacket = encode(packet);
	if(!rawPacket)
		return 0;

	//send buffer
	short result = sendData(rawPacket, socket);

	//free buffers
	freePacket(rawPacket);

	return result;
}

//получает пакет от сервера. Возвращает 0 в случае ошибки
short recvPacket(Packet *packet, int socket)
{
	//get packet
	NetPacket *rawPacket = recvData(socket);
	if (!rawPacket)
	{
		return 0;
	}

	//decode packet
	short result = decode(packet, rawPacket);

	//free buffers
	freePacket(rawPacket);
	return result;
}
