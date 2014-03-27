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
	GuestAuth authPacket = GUEST_AUTH__INIT;
	authPacket.header->type = guestAuth;
	strcpy(authPacket.uid, "testUid");

	ssize_t len = guest_auth__get_packed_size(&authPacket);
	void *buf = malloc(len);

	guest_auth__pack(&authPacket, buf);

	if (!sendPacket(buf, len, socket))
	{
		printf("Sending packet error!\n");
		return -1;
	}
	printf("No error\n");
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
