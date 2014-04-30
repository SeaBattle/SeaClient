#include "user_actions.h"

short connectAndAuthorize(Client *client)
{
	if(client->state == authorized)
		return 1;
	//int res = loginAuthorize(client->socket, "vasya", "somepass");
	int res = guestAuthorize(client->socket);
	return res;
}
