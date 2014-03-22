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

typedef enum {
	errorPacket = 1,
	guestAuth,
	passwordAuth,
	authResp
}PacketType;

typedef struct {
		PacketType type;
		int protocolVersion;
		int apiVersion;
}PacketHeader;

typedef struct {
		PacketType type;
		int protocolVersion;
		short successfulResponce;
}ServerHeader;

#endif /* MAIN_PACKET_H_ */
