#include "user_actions.h"

short connectAndAuthorize(Client *client)
{
	if(client->authorised)
		return 1;
	//loginAuthorize(client->socket, "vasya", "somepass");
	//guestAuthorize(client->socket);
	return loginAuthorize(client->socket, "vasya", "somepass");
}
