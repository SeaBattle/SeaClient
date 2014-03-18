/*
 * client.h
 *
 *  Created on: 01 нояб. 2013 г.
 *      Author: tihon
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <sys/epoll.h>

#include "support.h"
#include "net.h"

//создаёт клиента, принимает сокет
ClientStruct * createClient(int *mainSocket, int *epollSD, struct epoll_event *epollEvent);

short addClientToEpoll(int *epollSD, struct epoll_event *event,
		ClientStruct *client);

void showError(ClientStruct *client);

//отключает указанного клиента по всем правилам
void killClient(ClientStruct *client);

#endif /* CLIENT_H_ */
