/*
 * auth.c
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */

#include "auth.h"

/**
 * Авторизовывает клиента на удалённом сервере - гостевой вход.
 * @param client
 * @return -1 - ошибка, 0 - не авторизован, 1 - авторизован
 */
short guestAuthorize(int socket)
{
	Packet request;
	strcpy(request.guestAuthPacket.uid, "user's testUid");

	if (!sendPacket(&request, guestAuth, socket))
	{
		printf("Sending packet error!\n");
		return -1;
	}

	Packet responce;
	if (!recvPacket(&responce, socket))
	{
		printf("Receiving packet error!\n");
		return -1;
	}

	if (responce.header.type == authResp)
	{ //got authorization packet
		printf("Packet type = %d, protocol = %d, success = %d\n",
				responce.header.type, responce.header.protocolVersion,
				responce.authRespPacket.success);
		short authorised = responce.authRespPacket.success;
		return authorised;
	}
	else
	{ //got error packet (probably)
		if (responce.header.type == error)
		{
			printf("Got error when authorizing: [%d] : %s\n",
					responce.errorPacket.code, responce.errorPacket.message);
		}
		else
		{
			printf("Unknown packet type %d!\n", responce.header.type);
		}
		return -1;
	}
	return -1;
}
