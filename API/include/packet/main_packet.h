/*
 * main_packet.h
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */

#ifndef MAIN_PACKET_H_
#define MAIN_PACKET_H_

#include "auth_packets.h"

typedef struct {
		int header;
		union {
				GuestAuth guestPacket;
				PasswordAuth loginPacket;
		};
}Packet;

#endif /* MAIN_PACKET_H_ */
