#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>
#include <windows.h>
#include "udpserverclient.h"

#include <sys/types.h>

#define SERVER_CONFIG_FILE "ServerConfig.txt"

int main(void)
{
	WSADATA  wsa_data;
	SOCKET   UDPListen, UDPClient;
	struct sockaddr_in local, client;
	int       ipAddrSize, recvStatus, iterationStep;
	char      recvBuffer[BUFFER_SIZE];
	double    time_old, time_new, time_interval;
	char str_message;

	char *clientIpAddress = malloc(16);
	int portNumber = -1;

	printf("******** UDP Server ********\n\n");

	captureConfig(SERVER_CONFIG_FILE, &clientIpAddress, &portNumber);
	printf("Extracted config settings from file - Client IP: '%s', Port: '%d'\n\n", clientIpAddress, portNumber);

	if(WSAStartup(MAKEWORD(2,2), &wsa_data) != 0)
	{
        puts("WSAStartup failed!");
		exit(1);
	}
	
	UDPListen = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(UDPListen == SOCKET_ERROR)
	{
		printf("Failed to create socket(): %d\n", WSAGetLastError());
		exit(1);
	}
	
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(clientIpAddress);
	local.sin_port = htons(portNumber);

	if(bind(UDPListen, (struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR)
	{
		printf("Failed to bind(): %d\n", WSAGetLastError());
		exit(1);
	}
	
	printf("--- Listenting for transmissions from client ---\n\n");
    listen(UDPListen, 8);
	
	ipAddrSize = sizeof(client);
	iterationStep = 1;
	time_old = -1;
	for (;;)
	{
		recvStatus = recvfrom(UDPListen, &recvBuffer, BUFFER_SIZE, 0, (struct sockaddr*)&client, &ipAddrSize);
		if (recvStatus > 0) {
			if (recvStatus == SOCKET_ERROR) {
				printf("Failed in recvfrom(): %d\n", WSAGetLastError());
				break;
			}

			else
			{
				if (recvBuffer[0] = 'r')
				{
					printf("\n========= The client has received %ccommand from server =======/n", recvBuffer[0]);
					printf("\n Sending ack to server \n");
					printf("\ Sending time of clinet and random number to the server\n");


				}
			}

			
			// Eliminating possiblility of index out of range and related compiler warnings
			int endOfStr = recvStatus <= 127 ? recvStatus : 127;
			recvBuffer[endOfStr] = 0x00;
			if (strcmp(recvBuffer, "EXIT") == 0)
			{
				break;
			}

			time_new = getTime();
			time_interval = time_old == -1 ? 0 : time_new - time_old;
			time_old = time_new;

			printf("Step = %5d;     Time Interval = %8.6f;     Received String: %s\n", iterationStep, time_interval, recvBuffer);

			iterationStep++;
		}
	}

	for (i = 0; i < MAXCOUNT; i++)
	{
		printf("enter e to quit:");
		getchar();
		while (message != 'e')
		{
			scanf_s("%c" & message);
			printf("the input added is invalid");
			grtchar();

		}
		closesocket(UDPListen);
		return 0;

	printf("--- Transmission complete, closing socket ---\n");
	closesocket(UDPListen);
	
	free(clientIpAddress);
	
    WSACleanup();

	return 0;
}