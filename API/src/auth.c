/*
 * auth.c
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */


#include "auth.h"

short authorize(Client *client)
{
	sleep(1);
	ssize_t packetLen = sizeof(GuestAuth) + sizeof(PacketHeader);
	Packet *authPacket = malloc(packetLen);
	authPacket->header.type = guestAuth;
	strcpy(authPacket->guestPacket.uid, "testUid");
	if (!sendPacket(authPacket, packetLen, client->socket))
	{
		printf("Sending packet error!\n");
		free(authPacket);
		return 0;
	}
	printf("No error\n");
	free(authPacket);

	Packet *authResp = malloc(sizeof(Packet));
	if(!recvPacket(authResp, client->socket))
	{
		printf("Receiving packet error!\n");
		free(authResp);
		return 0;
	}
	printf("No error\n");
	free(authResp);

	client->authorised = 1;
	return 1;
}
