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
	RequestPacket *authPacket = malloc(packetLen);
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

	ResponsePacket *authResp = malloc(sizeof(ResponsePacket));
	if(!recvPacket(authResp, client->socket))
	{
		printf("Receiving packet error!\n");
		free(authResp);
		return 0;
	}
	printf("Packet type = %d, protocol = %d, success = %d\n",
			authResp->header.type, authResp->header.protocolVersion, authResp->authRespPacket.success);
	free(authResp);

	client->authorised = authResp->authRespPacket.success;
	return 1;
}
