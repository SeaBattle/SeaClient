/*
 * auth_packet.h
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */
#ifndef AUTH_PACKETS_H_
#define AUTH_PACKETS_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "ss_guest_auth.pb-c.h"

typedef struct
{
		char uid[30];
} GuestAuthPacket;

/**
 * Конвертирует нативный пакет Packet в протобуфер-пакет.
 * Кодирует протобуфер-пакет в буфер.
 * @param buffer - буффер-источник, куда нужно записать кодированный пакет
 * @packet пакет, который нужно закодировать
 */
void encodeGuestPacket(void *, GuestAuthPacket *);

typedef struct
{
		char login[30];
		char password[30];
} LoginAuthPacket;

typedef struct
{
		char success;
} AuthRespPacket;



#endif /* AUTH_PACKETS_H_ */
