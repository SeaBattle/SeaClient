/*
 * auth.h
 *
 *  Created on: 19 марта 2014 г.
 *      Author: tihon
 */

#ifndef AUTH_H_
#define AUTH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "client.h"

/**
 * Авторизовывает клиента на удалённом сервере - гостевой вход.
 * @param socket
 * @param uid - 30-и символьный идентификатор пользователя
 * @param player - структура игрока, в которую будет записан результат, полученный с сервера.
 * @return -1 - ошибка, 0 - не авторизован, 1 - авторизован
 */
short guestAuthorize(int, char *, Player *);

/**
 * Авторизовывает клиента на удалённом сервере - парольный вход.
 * @param socket
 * @param login
 * @param password
 * @param player - структура игрока, в которую будет записан результат, полученный с сервера.
 * @return -1 - ошибка, 0 - не авторизован, 1 - авторизован
 */
short loginAuthorize(int, char *, char *, Player *);

/**
 * Проводит регистрацию на сервере
 * @param socket
 * @param login логин обязателен
 * @param password пароль обязателен
 * @param uid - идентификатор устройства пользователя, обязателен
 * @param name имя игрока не обязательно. Если имя не будет задано - будет выбрано стандартное.
 * @param motto девиз игрока, не обязателен.
 * @param icon ссылка на аватарку игрока, не обязательна.
 * @param player - структура игрока, в которую будет записан результат, полученный с сервера.
 */
short registerPlayer(int, char *, char *, char *, char *, char *, char *, Player *);

/**
 * Выполняет авторизацию по заранее заполненному пакету
 * @param request -1 - ошибка, 0 - не авторизован, 1 - авторизован
 * @param socket
 * @param player - полученная от сервера структура пользователя
 */
short processAuth(Packet *, int, Player *);

/**
 * Генерирует случайный 30-и символьный uid,
 * состоящий из арабских цифр и латинского алфавита обоих регистров.
 * @param uid - место в памяти для записи 30-и символов
 */
void generateUID(char *);

#endif /* AUTH_H_ */
