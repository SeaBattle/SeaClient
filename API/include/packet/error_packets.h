/*
 * error_packets.h
 *
 *  Created on: 22 марта 2014 г.
 *      Author: tihon
 */

#ifndef ERROR_PACKETS_H_
#define ERROR_PACKETS_H_

#include "main_packet.h"

typedef struct {
		PacketHeader header;
		char message[100];
}ErrorPacket;

#endif /* ERROR_PACKETS_H_ */
