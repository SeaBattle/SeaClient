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
#include <string.h>

#include "ss_auth_packet.pb-c.h"

typedef struct
{
		char uid[30];
} GuestAuth;

typedef struct
{
		char login[30];
		char password[30];
} LoginAuth;

typedef struct
{
		LoginAuth loginData;
		char uid[30];
		char name[30];
		char icon[100];
		char motto[100];
}Register;

/**
 * Конвертирует нативный пакет Packet в протобуфер-пакет.
 * Кодирует протобуфер-пакет в буфер.
 * @packetLen указатель на длину кодированного пакета. Будет заполнена после определения длины.
 * @packet пакет, который нужно закодировать
 * @return буффер-источник, куда нужно записать кодированный пакет
 * !Важно: буффер должен быть освобождён в конце.
 */
void *encodeGuestPacket(ssize_t *, GuestAuth *);

/**
 * Конвертирует нативный пакет Packet в протобуфер-пакет.
 * Кодирует протобуфер-пакет в буфер.
 * @packetLen указатель на длину кодированного пакета. Будет заполнена после определения длины.
 * @packet пакет, который нужно закодировать
 * @return буффер-источник, куда нужно записать кодированный пакет
 * !Важно: буффер должен быть освобождён в конце.
 */
void *encodeLoginPacket(ssize_t *, LoginAuth *);

/**
 * Пакует пакет в буфер, вычисляет длину пакета
 * @param packetLen
 * @param authPacket
 */
void *encodeAuthPacket(ssize_t *, AuthPacket *);

/**
 * Конвертирует нативный пакет Packet в протобуфер-пакет.
 * Кодирует протобуфер-пакет в буфер.
 * @packetLen указатель на длину кодированного пакета. Будет заполнена после определения длины.
 * @packet пакет, который нужно закодировать
 * @return буффер-источник, куда нужно записать кодированный пакет
 * !Важно: буффер должен быть освобождён в конце.
 */
void *encodeRegisterPacket(ssize_t *, Register *);

#endif /* AUTH_PACKETS_H_ */
