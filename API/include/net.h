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

#include "packet.h"

//настраивет порт/адрес/протокол сервера. Возвращает -1 в случае ошибки. 0 - если всё нормально.
short set_address(char *, int, struct sockaddr_in *);

//делает указанный сокет неблокирующим. Возвращает 0 в случае ошибки.
short noblock(int);

//настраивает серверный сокет. Возвращает -1 в случае ошибки. Сокет - в другом случае.
int create_client_sock(char *, int);

//отправляет пакет по сокету до тех пор, пока не отправит всё.
//возвращает 1 - если всё хорошо и 0 при ошибке
short sendData(NetPacket *, int);

//получает весь пакет формата {длина, данные}. Возвращает пакет в случае успеха
//и NULL в случае ошибки. Important! Returned packet should be freed later.
NetPacket * recvData(int);

//создаёт бинарный сетевой пакет и возвращает его структуру
NetPacket *encode(Packet *, PacketType );

//декодирует бинарный пакет в протобуф пакет, а потом в нативный Packet.
//Возвращает 1 в случае успеха и 0 в случае ошибки.
short decode(Packet *, NetPacket *);

//освобождает память, занимаемую пакетом
void freePacket(NetPacket *);

#endif /* NET_H_ */
