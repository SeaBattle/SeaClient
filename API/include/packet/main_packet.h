/*
 * main_packet.h
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */

#ifndef MAIN_PACKET_H_
#define MAIN_PACKET_H_

#define PROTOCOL_VERSION 1
#define API_VERSION 1

#include "auth_packets.h"

typedef enum
{
	guestAuth = 1,
	passwordAuth,
	authResp
} PacketType;

typedef struct
{
		PacketType type;
		int protocolVersion;
		int apiVersion;
} PacketHeader;

typedef struct
{
		PacketHeader header;
		union
		{
				GuestAuth guestPacket;
				PasswordAuth loginPacket;
				AuthResp authRespPacket;
		};
} Packet;

#endif /* MAIN_PACKET_H_ */
