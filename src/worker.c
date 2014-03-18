/*
 * worker.c
 *
 *  Created on: 01 нояб. 2013 г.
 *      Author: tihon
 */

#include "worker.h"

void processEvent(void *client)
{
	printf("Process event\n");
	char *data = getPacket(client);
	if (data)
	{
		printf("got %s\n", data);

		free(data);
	}

}

void processNewConnection(int *listenSocket, int *epollSD,
        struct epoll_event *event)
{
	ClientStruct *client = createClient(listenSocket, epollSD, event);
	if (client)
	{
		if (addClientToEpoll(epollSD, event, client))
		{
			printf("Client connected\n");
			client->settings.on_url = on_url;
			client->settings.on_header_field = on_header_field;

			client->parser = malloc(sizeof(http_parser));
			http_parser_init(client->parser, HTTP_REQUEST);
			client->parser->data = &client->socket;
		}
	}
}

void processDisconnect(void *client, int socket)
{
	printf("Client disconnected\n");
	if (client)
	{
		killClient(client);
	}
	close(socket);
}

void dump_url(const char *url, const struct http_parser_url *u)
{
	unsigned int i;

	printf("\tfield_set: 0x%x, port: %u\n", u->field_set, u->port);
	for (i = 0; i < UF_MAX; i++)
	{
		if ((u->field_set & (1 << i)) == 0)
		{
			printf("\tfield_data[%u]: unset\n", i);
			continue;
		}

		printf("\tfield_data[%u]: off: %u len: %u part: \"%.*s\n", i,
		        u->field_data[i].off, u->field_data[i].len,
		        u->field_data[i].len, url + u->field_data[i].off);
	}
}

int on_url(http_parser* _, const char* at, size_t length)
{
	(void) _;
	printf("Url: %.*s\n", (int) length, at);
	struct http_parser_url res;
	int result = http_parser_parse_url(at, length, 0, &res);	//TODO сделать
	if (!result)
	{
		printf("Parse ok, result : \n");
		dump_url(at, &res);
	}

	return 0;
}

int on_header_field(http_parser* _, const char* at, size_t length)
{
	(void) _;
	printf("Header field: %.*s\n", (int) length, at);
	return 0;
}
