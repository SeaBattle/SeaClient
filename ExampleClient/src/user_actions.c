#include "user_actions.h"

short connectAndAuthorize(Client *client)
{
	if (client->state == authorized)
	{
		printf("Already authorized!\n");
		return 1;
	}

	char uid[UIDSIZE];
	getUid(uid);
	int res = guestAuthorize(client->socket, uid, &client->player);
	//int res = loginAuthorize(client->socket, "vasya", "somepass", &client->player);
	printf("Got player packet: %s, level %d, ban %d\n", client->player.name, client->player.level,
	        client->player.banType);
	return res;
}

short registerOnServer(Client *client)
{
	if (client->state == authorized)
	{
		printf("Can't register when authorized!\n");
		return 0;
	}
	char uid[UIDSIZE];
	getUid(uid);
	int res = registerPlayer(client->socket, "Vasya@mail.ru", "Password", uid, "Vasya", "Vasya is the best!", "default",
	        &client->player);
	return res;
}

void getUid(char *uid)
{
	FILE *uidStorage = fopen("uidStorage", "a+");
	if (!uidStorage)
	{
		perror("Error accessing uidStorage file!\n");
		return;
	}
	fseek(uidStorage, 0, SEEK_END);
	long fileSize = ftell(uidStorage);
	rewind(uidStorage);

	if (fileSize < UIDSIZE)
	{
		generateUID(uid);
		fwrite(uid, 1, UIDSIZE, uidStorage);
	}
	else
		fread(uid, 1, UIDSIZE, uidStorage);

	fclose(uidStorage);
}
