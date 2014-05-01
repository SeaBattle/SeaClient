/*
 * user_actions.h
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */

#ifndef USER_ACTIONS_H_
#define USER_ACTIONS_H_

#include "client.h"
#include "auth.h"

#define UIDSIZE 30

short connectAndAuthorize(Client *);

short registerOnServer(Client *);

void getUid(char *uid);

#endif /* USER_ACTIONS_H_ */
