#include "user_actions.h"

short connectAndAuthorize(Client *client)
{
	if(client->authorised)
		return 1;
	return guestAuthorize(client->socket);
}
