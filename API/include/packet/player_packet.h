/*
 * player_packet.h
 *
 *  Created on: 29 апр. 2014 г.
 *      Author: tihon
 */

#ifndef PLAYER_PACKET_H_
#define PLAYER_PACKET_H_

#include <stdio.h>
#include <string.h>

#include "ss_player_packet.pb-c.h"

typedef enum
{
	no_ban,
	chat_ban,
	wall_ban,
	privat_ban,
	social_ban,
	login_ban
} BanType;

typedef struct
{
		int level;
		BanType banType;
		long banEnd;
		char name[30];
		char icon[100];
} Player;

typedef struct
{
		char name[30];
		char description[100];
}Reward;

typedef struct
{
		//TODO fill
} Statistics;

typedef struct
{
		char motto[100];
		Reward rewards[100];
		long created;
		long rate;
		Statistics statistics[100]; //TODO рассчитать кол-во статистики - макс. кол-во комбинаций правил
} Wall;

/**
 * Декодирует двоичные данные в протобуфер-пакет.
 * Конфертирует протобуфер-пакет в нативный пакет.
 * Если после работы функции нативный пакет NULL, значит неверный формат пакета
 * или он повреждён.
 * @param raw - указатель на структуру бинарного пакета. Там содержится длина и данные.
 * @packet пакет, в который нужно декодировать.
 */
void decodePlayerPacket(ProtobufCBinaryData *, Player *);

#endif /* PLAYER_PACKET_H_ */
