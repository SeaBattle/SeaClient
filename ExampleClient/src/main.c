#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int main()
{
	char *listenAdress = "127.0.0.1";
	int listenPort = 4232;

	Client *client = malloc(sizeof(Client));
	if(!client) {
		printf("Error creating client!\n");
		return 0;
	}

	client->socket = create_client_sock(listenAdress, listenPort);
	if (client->socket < 0)
	{
		printf("Err! Can't connect to server. Check your internet connection.\n");
		return 0;
	}
	printf("Connected to %s : %d\n", listenAdress, listenPort);

	if(!connectAndAuthorize(client))
	{
		printf("Authorization error!\n");
		//TODO handle auth fail here!
	}

	if(client->authorised)
		printf("Authorized.\n");
	else
		printf("Not authorized!\n");

	close(client->socket);
	free(client);
	return 0;
}
