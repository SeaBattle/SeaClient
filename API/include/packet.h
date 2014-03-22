/*
 * packet.h
 *
 *  Created on: 22 марта 2014 г.
 *      Author: tihon
 */

#ifndef PACKET_H_
#define PACKET_H_

#include "error_packets.h"
#include "auth_packets.h"


/**
 * Заполняет заголовок пакета. Вставляет константы и тип, переданный параметром
 * @param header - Заголовок, который необходимо заполнить
 * @param type - тип пакета - enum
 */
void fillHeader(PacketHeader *header, PacketType type);

#endif /* PACKET_H_ */
