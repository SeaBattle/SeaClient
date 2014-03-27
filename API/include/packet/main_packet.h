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
#include "service_packets.h"

typedef enum
{
	guestAuth = 1,
	passwordAuth,
	authResp,
	errorPacket
} PacketType;

typedef struct
{
		PacketType type;
		int protocolVersion;
		int apiVersion;
} PacketHeader;

typedef struct
{
		PacketType type;
		int protocolVersion;
} ResponseHeader;

typedef struct
{
		PacketHeader header;
		union
		{
				GuestAuth guestPacket;		//type 1
				PasswordAuth loginPacket;	//type 2
				Error errorPacket;			//type 4
		};
} RequestPacket;

typedef struct
{
		ResponseHeader header;
		union
		{
				AuthResp authRespPacket;	//type 3
				Error errorPacket;			//type 4
		};
} ResponsePacket;

#endif /* MAIN_PACKET_H_ */
