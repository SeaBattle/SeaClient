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
 * @param buffer - буффер-источник, куда нужно записать кодированный пакет
 * @packet пакет, который нужно закодировать
 */
void encodeGuestPacket(void *buffer, GuestAuthPacket *packet)
{
	GuestAuth authPacket = GUEST_AUTH__INIT;
	authPacket.uid = packet->uid;
	ssize_t packetLen = guest_auth__get_packed_size(&authPacket);
	buffer = malloc(packetLen);
	guest_auth__pack(&authPacket, buffer);
}
