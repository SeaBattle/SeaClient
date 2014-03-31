/*
 * service_packet.с
 *
 *  Created on: 31 марта 2014 г.
 *      Author: tihon
 */


#include "service_packet.h"

/**
 * Декодирует двоичные данные в протобуфер-пакет.
 * Конфертирует протобуфер-пакет в нативный пакет.
 * Если после работы функции нативный пакет NULL, значит неверный формат пакета
 * или он повреждён.
 * @param raw - указатель на структуру бинарного пакета. Там содержится длина и данные.
 * @packet пакет, в который нужно декодировать.
 */
void decodeErrorPacket(ProtobufCBinaryData *raw, Error *packet)
{
	ErrorPacket *errorPack = error_packet__unpack(NULL, raw->len, raw->data);
	if(!errorPack)
	{
		printf("Error converting packet!");
		packet=NULL;
		return;
	}
	packet->code = errorPack->code;
	strcpy(packet->message, errorPack->descr);
	error_packet__free_unpacked(errorPack, NULL);
}
