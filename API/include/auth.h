/*
 * auth.h
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */

#ifndef AUTH_H_
#define AUTH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"

/**
 * Авторизовывает клиента на удалённом сервере - гостевой вход.
 * @param socket
 * @return -1 - ошибка, 0 - не авторизован, 1 - авторизован
 */
short guestAuthorize(int);

/**
 * Авторизовывает клиента на удалённом сервере - парольный вход.
 * @param client
 * @return -1 - ошибка, 0 - не авторизован, 1 - авторизован
 */
short loginAuthorize(int, char *, char *);

/**
 * Выполняет авторизацию по заранее заполненному пакету
 * @param request -1 - ошибка, 0 - не авторизован, 1 - авторизован
 */
short processAuth(Packet *, int);

#endif /* AUTH_H_ */
