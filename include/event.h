/*
 * events.h
 *
 *  Created on: 01 нояб. 2013 г.
 *      Author: tihon
 */

#ifndef EVENTS_H_
#define EVENTS_H_

#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "support.h"
#include "worker.h"

#define MAXEVENTS 256	//количество одновременных событий

void waitForNewEvents(int *, int *,	struct epoll_event *, struct epoll_event *);

//создаёт и настраивает дескриптор Epoll. Возвращает 0 в случае ошибки.
short epollInit(int *, int *, struct epoll_event *);

#endif /* EVENTS_H_ */
