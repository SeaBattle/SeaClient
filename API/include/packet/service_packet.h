/*
 * service_packet.h
 *
 *  Created on: 30 марта 2014 г.
 *      Author: tihon
 */

#ifndef SERVICE_PACKET_H_
#define SERVICE_PACKET_H_

typedef struct
{
		int code;
		char reason[100];
} Error;

#endif /* SERVICE_PACKET_H_ */
