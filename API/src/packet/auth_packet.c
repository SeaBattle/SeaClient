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
void *encodeGuestPacket(ssize_t *packetLen, GuestAuthPacket *packet)
{
	AuthPacket authPacket = AUTH_PACKET__INIT;
	authPacket.uid = packet->uid;
	return encodeAuthPacket(packetLen, &authPacket);
}

/**
 * Конвертирует нативный пакет Packet в протобуфер-пакет.
 * Кодирует протобуфер-пакет в буфер.
 * @packetLen указатель на длину кодированного пакета. Будет заполнена после определения длины.
 * @packet пакет, который нужно закодировать
 * @return буффер-источник, куда нужно записать кодированный пакет
 * !Важно: буффер должен быть освобождён в конце.
 */
void *encodeLoginPacket(ssize_t *packetLen, LoginAuthPacket *packet)
{
	AuthPacket authPacket = AUTH_PACKET__INIT;
	authPacket.uid = packet->login;
	authPacket.password = packet->password;
	return encodeAuthPacket(packetLen, &authPacket);
}

/**
 * Пакует пакет в буфер, вычисляет длину пакета
 * @param packetLen
 * @param authPacket
 */
void *encodeAuthPacket(ssize_t *packetLen, AuthPacket *authPacket)
{
	*packetLen = auth_packet__get_packed_size(authPacket);
	void *buffer = malloc(*packetLen);
	auth_packet__pack(authPacket, buffer);
	return buffer;
}
