/*
 * packet.c
 *
 *  Created on: 22 марта 2014 г.
 *      Author: tihon
 */

#include "packet.h"

/**
 * Заполняет заголовок пакета. Вставляет константы и тип, переданный параметром
 * @param header - Заголовок, который необходимо заполнить
 * @param type - тип пакета - enum
 */
void fillHeader(PacketHeader *header, PacketType type)
{
	header->apiVersion = API_VERSION;
	header->protocolVersion = PROTOCOL_VERSION;
	header->type = type;
}

void *fillPacket(void *rawData, PacketType type)
{
	switch (type)
	{
		case AuthResp:
			AuthResp *authRespPacket = malloc(sizeof(AuthResp));
			memcpy(authRespPacket, rawData, sizeof(AuthResp));
			if(authRespPacket->header.type == type)
			{
				free(rawData);
				return authRespPacket;
			}else
			{
				ErrorPacket *packet = rawData;
			}
	}

}
