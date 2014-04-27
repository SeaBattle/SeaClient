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

#include "ss_auth_packet.pb-c.h"

typedef struct
{
		char uid[30];
} GuestAuthPacket;

typedef struct
{
		char login[30];
		char password[30];
} LoginAuthPacket;

typedef struct
{
		char success;
} AuthRespPacket;

/**
 * Конвертирует нативный пакет Packet в протобуфер-пакет.
 * Кодирует протобуфер-пакет в буфер.
 * @packetLen указатель на длину кодированного пакета. Будет заполнена после определения длины.
 * @packet пакет, который нужно закодировать
 * @return буффер-источник, куда нужно записать кодированный пакет
 * !Важно: буффер должен быть освобождён в конце.
 */
void *encodeGuestPacket(ssize_t *, GuestAuthPacket *);

/**
 * Конвертирует нативный пакет Packet в протобуфер-пакет.
 * Кодирует протобуфер-пакет в буфер.
 * @packetLen указатель на длину кодированного пакета. Будет заполнена после определения длины.
 * @packet пакет, который нужно закодировать
 * @return буффер-источник, куда нужно записать кодированный пакет
 * !Важно: буффер должен быть освобождён в конце.
 */
void *encodeLoginPacket(ssize_t *, LoginAuthPacket *);

/**
 * Пакует пакет в буфер, вычисляет длину пакета
 * @param packetLen
 * @param authPacket
 */
void *encodeAuthPacket(ssize_t *, AuthPacket *);

#endif /* AUTH_PACKETS_H_ */
