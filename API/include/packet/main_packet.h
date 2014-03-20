/*
 * main_packet.h
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */

#ifndef MAIN_PACKET_H_
#define MAIN_PACKET_H_

#include "auth_packets.h"

typedef enum {
	guestAuth = 1,
	passwordAuth,
	authResp
}PacketType;

typedef struct {
		PacketType header;
		int protocolVersion;
		int apiVersion;
		union {
				GuestAuth guestPacket;
				PasswordAuth loginPacket;
				AuthResp authRespPacket;
		};
}Packet;

#endif /* MAIN_PACKET_H_ */
