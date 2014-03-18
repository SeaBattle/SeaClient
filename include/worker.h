/*
 * worker.h
 *
 *  Created on: 01 нояб. 2013 г.
 *      Author: tihon
 */

#ifndef WORKER_H_
#define WORKER_H_

#include <sys/epoll.h>

#include "client.h"
#include "support.h"
#include "http_parser.h"

#define ClientsPerThread 200

void processNewConnection(int *, int *, struct epoll_event *);
void processEvent(void *);
void processDisconnect(void *, int);

int on_url(http_parser* _, const char* at, size_t length);

int on_header_field(http_parser* _, const char* at, size_t length);

#endif /* WORKER_H_ */
