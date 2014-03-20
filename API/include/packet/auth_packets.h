/*
 * auth_packet.h
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */

#ifndef AUTH_PACKETS_H_
#define AUTH_PACKETS_H_

typedef struct {
		char uid[30];
}GuestAuth;

typedef struct {
		char login[30];
		char password[30];
}PasswordAuth;

#endif /* AUTH_PACKETS_H_ */
