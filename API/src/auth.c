/*
 * auth.c
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */


#include "auth.h"

short authorize(Client *client)
{
	GuestAuth *authPacket = malloc(sizeof(GuestAuth));
	fillHeader(&authPacket->header, guestAuth);
	strcpy(authPacket->uid, "testUid");
	if (!sendPacket(authPacket, sizeof(GuestAuth), client->socket))
	{
		printf("Sending packet error!\n");
		free(authPacket);
		return 0;
	}
	printf("No error\n");
	free(authPacket);

	char *rawData = recvPacket(client->socket);
	if(!rawData)
	{
		printf("Receiving packet error!\n");
		return 0;
	}
	printf("No error\n");

	AuthResp *authRespPacket = malloc(sizeof(AuthResp));
	memcpy(authRespPacket, rawData, sizeof(AuthResp));
	free(rawData);

	if(authRespPacket->header.type == authResp)
	{

		client->authorised = authRespPacket->success;
	}

	free(authRespPacket);
	return 1;
}
