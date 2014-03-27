/*
 * net.h
 *
 *  Created on: 01 нояб. 2013 г.
 *      Author: tihon
 */

#ifndef NET_H_
#define NET_H_

#define API_VERSION 1
#define PROTOCOL_VERSION 1

#include <sys/types.h>		//для работы сокетов
#include <sys/socket.h>		//для работы сокетов
#include <netinet/in.h>		//для работы сокетов

#include <arpa/inet.h>		//для работы сокетов
#include <netdb.h>			//для работы сокетов
#include <string.h>			//для strcmp
#include <strings.h>		//для bzero
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

#include "ss_guest_auth.pb-c.h"

typedef enum {
	guestAuth,
	loginAuth
}PacketType;

//настраивет порт/адрес/протокол сервера. Возвращает -1 в случае ошибки. 0 - если всё нормально.
short set_address(char *, int, struct sockaddr_in *);

//делает указанный сокет неблокирующим. Возвращает 0 в случае ошибки.
short noblock(int);

//настраивает серверный сокет. Возвращает -1 в случае ошибки. Сокет - в другом случае.
int create_client_sock(char *, int);

//заполняет заголовок статической информацией (версии протокола и библиотеки)
void fillHeaders(Header *);

//отправляет пакет на сервер. Возвращает 0 в случае ошибки
short sendPacket(char *, ssize_t , int );

//получает пакет от сервера. Возвращает 0 в случае ошибки
//short recvPacket(ResponsePacket *packet, int socket);

#endif /* NET_H_ */
