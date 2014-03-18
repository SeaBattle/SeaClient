/*
 * net.h
 *
 *  Created on: 01 нояб. 2013 г.
 *      Author: tihon
 */

#ifndef NET_H_
#define NET_H_



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

#include "support.h"

//протокол, по которому происходит подключение клиента
typedef enum _Protocol
{
	TCP, UDP, HTTP
} Protocol;

#define NLISTEN 1000

//заставляет сокет слушать
short Listen(int, int);

//настраивет порт/адрес/протокол сервера. Возвращает -1 в случае ошибки. 0 - если всё нормально.
short set_address(char *, int, struct sockaddr_in *);

//делает указанный сокет неблокирующим. Возвращает 0 в случае ошибки.
short noblock(int);

//настраивает серверный сокет. Возвращает -1 в случае ошибки. Сокет - в другом случае.
int create_client_sock(char *, int);

//получает нового клиента
int getNewClient(int *);

//получает данные от клиента и парсит их. Возвращает NULL в случае ошибки
char *getPacket(ClientStruct *client);

#endif /* NET_H_ */
