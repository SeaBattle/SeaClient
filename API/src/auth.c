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
	strcpy(request.guestAuthPacket.uid, "testUid");

	if(!sendPacket(&request, guestAuth, socket))
	{
		printf("Sending packet error!\n");
		return -1;
	}

	Packet responce;
	if(!recvPacket(&responce, socket))
	{
		printf("Receiving packet error!\n");
		return -1;
	}

	printf("packet type %d, code %d, msg %s\n", responce.header.type, responce.errorPacket.code, responce.errorPacket.reason);

	return 1;

//	ResponsePacket *authRespPack = malloc(sizeof(ResponsePacket));
//	if (!recvPacket(authRespPack, socket))
//	{
//		printf("Receiving packet error!\n");
//		free(authRespPack);
//		return -1;
//	}
//
//	if (authRespPack->header.type == authResp)
//	{ //get authorization packet
//		printf("Packet type = %d, protocol = %d, success = %d\n", authRespPack->header.type,
//		        authRespPack->header.protocolVersion, authRespPack->authRespPacket.success);
//		short authorised = authRespPack->authRespPacket.success;
//		free(authRespPack);
//		return authorised;
//	}
//	else
//	{ //get error packet (probably)
//		if (authRespPack->header.type == errorPacket)
//		{
//			printf("Got error when authorizing: [%d] : %s\n", authRespPack->errorPacket.code,
//			        authRespPack->errorPacket.message);
//		}
//		else
//		{
//			printf("Unknown packet type %d!\n", authRespPack->header.type);
//		}
//		return -1;
//	}
}
