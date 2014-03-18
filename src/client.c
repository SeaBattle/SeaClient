/*
 * client.c
 *
 *  Created on: 01 нояб. 2013 г.
 *      Author: tihon
 */

#include "client.h"

//подсоединяет клиента к потоку обработки клиентов
ClientStruct * createClient(int *mainSocket, int *epollSD, struct epoll_event *epollEvent)
{
	ClientStruct *client = malloc(sizeof(ClientStruct));

	//принимаем входящее соединение
	client->socket = getNewClient(mainSocket);	//принимаем соединение
	if (client->socket < 0)
	{
		free(client);
		printf("Can't get client!\n");
		return NULL;
	}
	client->TTL = 30;	//выставляем TTL для клиента

	return client;
}

//подсоединяет указанного клиента к фабрике событий указанного потока. Возвращает 0 в случае ошибки
short addClientToEpoll(int *epollSD, struct epoll_event *event,
		ClientStruct *client)
{
	//подключаем клиента к фабрике событий
	event->data.ptr = client; //ставим указатель на клиента
	event->events = EPOLLIN | EPOLLET | EPOLLRDHUP; //указываем - на какие события реагировать

	//добавляем сокет клиента в фабрику событий
	int rc = epoll_ctl(*epollSD, EPOLL_CTL_ADD, client->socket, event);
	return (rc == -1) ? 0 : 1;
}

//отключает указанного клиента по всем правилам
void killClient(ClientStruct *client)
{
	close(client->socket);	//закрываем сокет клиента
	free(client);//освобождаем занимаемую память
}
