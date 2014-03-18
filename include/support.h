/*
 * support.h
 *
 *  Created on: 01 нояб. 2013 г.
 *      Author: tihon
 */

#ifndef SUPPORT_H_
#define SUPPORT_H_

#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#include "http_parser.h"

//клиент, подключённый к серверу
typedef struct
{
	int socket;
	int number;	//номер клиента в списке
	short TTL; //по обращении в 0 - отключает клиента. При получении пакета - инкримент
	http_parser *parser;
	http_parser_settings settings;
} ClientStruct;

#endif /* SUPPORT_H_ */
