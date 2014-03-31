/*
 * service_packet.h
 *
 *  Created on: 30 марта 2014 г.
 *      Author: tihon
 */

#ifndef SERVICE_PACKET_H_
#define SERVICE_PACKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ss_error_packet.pb-c.h"

typedef struct
{
		int code;
		char message[100];
} Error;

/**
 * Декодирует двоичные данные в протобуфер-пакет.
 * Конфертирует протобуфер-пакет в нативный пакет.
 * Если после работы функции нативный пакет NULL, значит неверный формат пакета
 * или он повреждён.
 * @param raw - указатель на структуру бинарного пакета. Там содержится длина и данные.
 * @packet пакет, в который нужно декодировать.
 */
void decodeErrorPacket(ProtobufCBinaryData *, Error *);

#endif /* SERVICE_PACKET_H_ */
