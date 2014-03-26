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

#include "auth_packets.h"
#include "client.h"
#include "net.h"

/**
 * Авторизовывает клиента на удалённом сервере - гостевой вход.
 * @param socket
 * @return -1 - ошибка, 0 - не авторизован, 1 - авторизован
 */
short guestAuthorize(int socket);

#endif /* AUTH_H_ */
