/*
 * client.h
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */

#ifndef CLIENT_H_
#define CLIENT_H_

typedef enum
{
	disconnected = -1,
	connected,
	authorized,
	in_game
} State;

typedef struct
{
		State state;
		int socket;
} Client;

#endif /* CLIENT_H_ */
