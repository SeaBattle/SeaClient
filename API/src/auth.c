/*
 * auth.c
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */

#include "auth.h"

/**
 * Авторизовывает клиента на удалённом сервере - гостевой вход.
 * @param client
 * @return -1 - ошибка, 0 - не авторизован, 1 - авторизован
 */
short guestAuthorize(int socket)
{
	Packet request;
	request.header.type = guestAuth;
	strcpy(request.guestAuthPacket.uid, "vasyaUid");
	return processAuth(&request, socket);
}

/**
 * Авторизовывает клиента на удалённом сервере - парольный вход.
 * @param client
 * @return -1 - ошибка, 0 - не авторизован, 1 - авторизован
 */
short loginAuthorize(int socket, char *login, char *password)
{
	Packet request;
	request.header.type = loginAuth;
	strcpy(request.loginAuthPacket.login, login);
	strcpy(request.loginAuthPacket.password, password);
	return processAuth(&request, socket);
}

/**
 * Выполняет авторизацию по заранее заполненному пакету
 * @param request -1 - ошибка, 0 - не авторизован, 1 - авторизован
 */
short processAuth(Packet *request, int socket)
{
	if (!sendPacket(request, socket))
	{
		printf("Sending packet error!\n");
		return -1;
	}

	Packet response;
	if (!recvPacket(&response, socket))
	{
		printf("Receiving packet error!\n");
		return -1;
	}

	if (response.header.type == playerPacket)
	{ //got player packet (authorization success)
		printf("Got player packet: %s, level %d, ban %d\n"
				, response.playersPacket.name, response.playersPacket.level, response.playersPacket.banType);
		return 1;
	}
	else
	{ //got error packet (probably)
		if (response.header.type == error)
		{
			printf("Got error when authorizing: [%d] : %s\n", response.errorPacket.code, response.errorPacket.message);
		}
		else
		{
			printf("Unknown packet type %d!\n", response.header.type);
		}
		return -1;
	}
	return -1;
}
