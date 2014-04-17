/*
 * packet.h
 *
 *  Created on: 30 марта 2014 г.
 *      Author: tihon
 */

#ifndef PACKET_H_
#define PACKET_H_

#define HEADER_LENGTH 4

#include <netinet/in.h>

#include "ss_packet_header.pb-c.h"
#include "auth_packet.h"
#include "service_packet.h"

//тип пакета
typedef enum
{
	guestAuth = 1,
	loginAuth,		//2
	authResp, 		//3
	error			//4
} PacketType;

//заголовок пакета
typedef struct
{
	PacketType type;		//тип пакета
	int protocolVersion;	//версия протокола
	int apiVersion;			//версия этой библиотеки
} PacketHeader;

//нативная структура пакета
//(используется на верхнем уровне при работе с сервером, ниже идут protobuff-пакеты, ещё ниже - скомпонованные двоичные данные).
typedef struct
{
	PacketHeader header;
	union
	{
		GuestAuthPacket guestAuthPacket;	//type 1
		LoginAuthPacket loginAuthPacket; 	//type 2
		AuthRespPacket authRespPacket;		//type 3
		Error errorPacket;					//type 4
	};
} Packet;

//сетевая структура пакета. Самый низкй уровень - в неё компонуется protobuff-пакет. Используется только sпри отправке-получении данных.
typedef struct
{
	ssize_t len;	//длина двоичных данных
	char *body;		//двоичные данные
} NetPacket;

//Кодирует тело пакета согласно типу.
ProtobufCBinaryData encodePacketBody(Packet *, PacketType);

//Декодирует тело пакета согласно типу.
short decodePacketBody(Header *, Packet *);

//Упаковывает пакет в структуру {длина, бинарные данные}
NetPacket *composePacket(Header *);

//Переводит long-значение в 4-е байта
void longToByte(char *, long);

//Переводит 4-е байта в long-значение
long byteToLong(char *);

//Проверяет endianness. 0 - little, 1 - big
short isBigEndian();

#endif /* PACKET_H_ */
