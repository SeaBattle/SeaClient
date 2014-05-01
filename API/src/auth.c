/*
 * auth.c
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */

#include "auth.h"

/**
 * Авторизовывает клиента на удалённом сервере - гостевой вход.
 * @param socket
 * @param uid - 30-и символьный идентификатор пользователя
 * @param player - структура игрока, в которую будет записан результат, полученный с сервера.
 * @return -1 - ошибка, 0 - не авторизован, 1 - авторизован
 */
short guestAuthorize(int socket, char *uid, Player *player)
{
	Packet request;
	request.header.type = guestAuth;
	strcpy(request.guestAuthPacket.uid, uid);
	return processAuth(&request, socket, player);
}

/**
 * Авторизовывает клиента на удалённом сервере - парольный вход.
 * @param socket
 * @param login
 * @param password
 * @param player - структура игрока, в которую будет записан результат, полученный с сервера.
 * @return -1 - ошибка, 0 - не авторизован, 1 - авторизован
 */
short loginAuthorize(int socket, char *login, char *password, Player *player)
{
	Packet request;
	request.header.type = loginAuth;
	strcpy(request.loginAuthPacket.login, login);
	strcpy(request.loginAuthPacket.password, password);
	return processAuth(&request, socket, player);
}

/**
 * Проводит регистрацию на сервере
 * @param socket
 * @param login - логин обязателен
 * @param password - пароль обязателен
 * @param uid - идентификатор устройства пользователя, обязателен
 * @param name - имя игрока не обязательно. Если имя не будет задано - будет выбрано стандартное.
 * @param motto - девиз игрока, не обязателен.
 * @param icon - ссылка на аватарку игрока, не обязательна.
 * @param player - структура игрока, в которую будет записан результат, полученный с сервера.
 */
short registerPlayer(int socket, char *login, char *password, char *uid, char *name, char *motto, char *icon, Player *player)
{
	if (!login || !password)
	{
		perror("Login and password required!\n");
		return 0;
	}

	Packet *request = calloc(1, sizeof(Packet));
	request->header.type = registerP;
	strcpy(request->registerPacket.loginData.login, login);
	strcpy(request->registerPacket.loginData.password, password);
	strcpy(request->registerPacket.uid, uid);
	if (name) strcpy(request->registerPacket.name, name);
	if (motto) strcpy(request->registerPacket.motto, motto);
	if (icon) strcpy(request->registerPacket.icon, icon);

	if (!sendPacket(request, socket))
	{
		printf("Sending packet error!\n");
		free(request);
		return -1;
	}
	free(request);

	Packet response;
	if (!recvPacket(&response, socket))
	{
		printf("Receiving packet error!\n");
		return -1;
	}

	if (response.header.type == playerPacket)
	{ //got player packet (registration success)
		memcpy(player, &response.playersPacket, sizeof(Player));
		return 1;
	}
	else
	{ //got error packet (probably)
		if (response.header.type == error)
		{
			printf("Registration error: [%d] : %s\n", response.errorPacket.code, response.errorPacket.message);
		}
		else
		{
			printf("Unknown packet type %d!\n", response.header.type);
		}
		return -1;
	}

	return -1;
}

/**
 * Выполняет авторизацию по заранее заполненному пакету
 * @param request -1 - ошибка, 0 - не авторизован, 1 - авторизован
 * @param socket
 * @param player - полученная от сервера структура пользователя
 */
short processAuth(Packet *request, int socket, Player *player)
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
		memcpy(player, &response.playersPacket, sizeof(Player));
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

/**
 * Генерирует случайный 30-и символьный uid,
 * состоящий из арабских цифр и латинского алфавита обоих регистров.
 * @param uid - место в памяти для записи 30-и символов
 */
void generateUID(char *uid)
{
	srand(time(NULL));
	char charset[] = "0123456789"
			"abcdefghijklmnopqrstuvwxyz"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int i = 0; i < 30; i++)
	{
		size_t index = rand() % (int) (sizeof charset - 1);
		*uid++ = charset[index];
	}
	*uid = '\0';
}
