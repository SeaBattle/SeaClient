/*
 * events.c
 *
 *  Created on: 01 нояб. 2013 г.
 *      Author: tihon
 */

#include "event.h"

void waitForNewEvents(int *listenSocket, int *mainEpollSD,
		struct epoll_event *events, struct epoll_event *event)
{
	int n = epoll_wait(*mainEpollSD, events, MAXEVENTS, -1);
	for (int i = 0; i < n; i++)
	{
		if ((events[i].events & EPOLLERR)
				|| (events[i].events & EPOLLHUP)
				|| (!(events[i].events & EPOLLIN))
				|| (events[i].events & EPOLLRDHUP))
		{
			processDisconnect(events[i].data.ptr, events[i].data.fd);
			continue;
		}
		else if (*listenSocket == events[i].data.fd) //если подключается новый клиент. (событие на главном сокете)
		{
			processNewConnection(listenSocket, mainEpollSD, event);
			continue;
		}
		else	//событие на другом сокете (пришли данные)
		{
			processEvent(events[i].data.ptr);
			continue;
		}
	}
}

//создаёт и настраивает дескриптор Epoll. Возвращает 0 в случае ошибки.
short epollInit(int *socketServ, int *epollSD, struct epoll_event *servEvent)
{
	//создание
	short rc = 0;
	*epollSD = epoll_create1(0);
	if (*epollSD == -1)
	{
		printf("Err! Error in epoll create\n");
		return 0;
	}

	//настройка
	servEvent->data.fd = *socketServ;
	servEvent->events = EPOLLIN | EPOLLET | EPOLLRDHUP;
	rc = epoll_ctl(*epollSD, EPOLL_CTL_ADD, *socketServ, servEvent);
	if (rc == -1)
	{
		printf("Err! Error in epoll control\n");
		return 0;
	}

	return 1;
}
