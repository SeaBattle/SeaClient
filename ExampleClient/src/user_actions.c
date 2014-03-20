#include "user_actions.h"

short connectAndAuthorize(Client *client)
{
	if (!authorize(client))
	{
		return 0;
	}

	return 1;
}
