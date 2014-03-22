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

short authorize(Client *client);

#endif /* AUTH_H_ */
