/*
 * auth.c
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */


#include "auth.h"

short authorize(Client *client)
{
	Packet *authPacket = malloc(sizeof(Packet));
	strcpy(authPacket->guestPacket.uid, "testUid");
	if (!sendPacket(authPacket, client->socket))
	{
		printf("Sending packet error!\n");
		free(authPacket);
		return 0;
	}
	printf("No error\n");
	free(authPacket);

	//todo get responce

	return 1;
}
