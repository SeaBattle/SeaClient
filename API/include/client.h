/*
 * client.h
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include "net.h"
#include "player_packet.h"

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
		Player player;
		//TODO wall
		//TODO ships
} Client;

//отправляет пакет на сервер. Возвращает 0 в случае ошибки
short sendPacket(Packet *, int);

//получает пакет от сервера. Возвращает 0 в случае ошибки
short recvPacket(Packet *, int);

#endif /* CLIENT_H_ */
