/*
 * auth_packet.c
 *
 *  Created on: 31 марта 2014 г.
 *      Author: tihon
 */

#include "auth_packet.h"

/**
 * Конвертирует нативный пакет Packet в протобуфер-пакет.
 * Кодирует протобуфер-пакет в буфер.
 * @packet пакет, который нужно закодировать
 * @return буффер-источник, куда нужно записать кодированный пакет
 * !Важно: буффер должен быть освобождён в конце.
 */
void *encodeGuestPacket(GuestAuthPacket *packet)
{
	GuestAuth authPacket = GUEST_AUTH__INIT;
	authPacket.uid = packet->uid;
	ssize_t packetLen = guest_auth__get_packed_size(&authPacket);
	void *buffer = malloc(packetLen);
	guest_auth__pack(&authPacket, buffer);
	return buffer;
}
