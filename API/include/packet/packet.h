/*
 * packet.h
 *
 *  Created on: 30 марта 2014 г.
 *      Author: tihon
 */

#ifndef PACKET_H_
#define PACKET_H_

#include "auth_packet.h"
#include "service_packet.h"

typedef enum
{
	guestAuth = 1,
	loginAuth,		//2
	authResp, 		//3
	error			//4
} PacketType;

typedef struct
{
	PacketType type;
	int protocolVersion;
	int apiVersion;
}PacketHeader;

typedef struct
{
		PacketHeader header;
		union
		{
				GuestAuthPacket guestAuthPacket;	//type 1
				LoginAuthPacket loginAuthPacket; 	//type 2
				AuthRespPacket authRespPacket;		//type 3
				Error errorPacket;					//type 4
		};
} Packet;

#endif /* PACKET_H_ */
