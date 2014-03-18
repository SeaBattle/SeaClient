#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int main()
{
	char *listenAdress = "127.0.0.1";
	int listenPort = 4232;

	int connectSocket = create_client_sock(listenAdress, listenPort);
	if (connectSocket < 0)
	{
		printf(
		        "Err! Can't connect to server. Check your internet connection.\n");
		return 0;
	}
	printf("Server started on %s : %d\n", listenAdress, listenPort);

	//создаём главный дескриптор epoll
	int mainEpollSD;
	struct epoll_event mainEvent;
	if (!epollInit(&connectSocket, &mainEpollSD, &mainEvent))
	{
		printf("Err! Can't initialize Main epoll descriptor!\n");
		close(connectSocket);
		abort();
	}

	//выделяем память под события клиентов (до MAXEVENTS одновременных событий)
	struct epoll_event *mainEvents = calloc(MAXEVENTS, sizeof mainEvent);

	//основной серверный цикл
	while (1)
	{
		//ждём наступления события (событие - подключение нового клиента)
		waitForNewEvents(&connectSocket, &mainEpollSD, mainEvents, &mainEvent);
	}
	return 0;
}
