/*
 * player_packet.c
 *
 *  Created on: 29 апр. 2014 г.
 *      Author: tihon
 */

#include "player_packet.h"

/**
 * Декодирует двоичные данные в протобуфер-пакет.
 * Конфертирует протобуфер-пакет в нативный пакет.
 * Если после работы функции нативный пакет NULL, значит неверный формат пакета
 * или он повреждён.
 * @param raw - указатель на структуру бинарного пакета. Там содержится длина и данные.
 * @packet пакет, в который нужно декодировать.
 */
void decodePlayerPacket(ProtobufCBinaryData *raw, Player *packet)
{
	PlayerPacket *playerPack = player_packet__unpack(NULL, raw->len, raw->data);
	if (!playerPack)
	{
		perror("Error converting packet!");
		packet = NULL;
		return;
	}
	packet->level = playerPack->level;
	packet->banType = playerPack->ban_type;
	if (packet->banType != no_ban) packet->banEnd = playerPack->ban_end;
	if (playerPack->name) strcpy(packet->name, playerPack->name);
	if (playerPack->icon) strcpy(packet->icon, playerPack->icon);
	player_packet__free_unpacked(playerPack, NULL);
}
