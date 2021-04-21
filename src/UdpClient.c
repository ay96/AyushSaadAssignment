#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>     
#include <time.h>
#include "udpserverclient.h"

#define PERIOD 3
#define NUMBER_RANGE 100
/* maximum number of iterations of sending data */
#define MAXCOUNT 5

#define CLIENT_CONFIG_FILE "ClientConfig.txt"

int main(void)
{
    WSADATA       wsa_data;
    SOCKET        UDPClient;
    struct sockaddr_in UDPServer;
    struct hostent     *host = NULL;
    int ipAddrSize;

	char sendMessageStr[8];
	int sendStatus; int randomNumber;
	double time_old, time_new, time_interval = 0;
	int i;

    char *serverIpAddress = malloc(16);
    int portNumber = -1;

	printf("======== UDP Client ========\n\n");

    captureConfig(CLIENT_CONFIG_FILE, &serverIpAddress, &portNumber);
    printf("Extracted config settings from file - Server IP: '%s', Port: '%d'\n\n", serverIpAddress, portNumber);

    if (WSAStartup(MAKEWORD(2,2), &wsa_data) != 0)
    {
        puts("WSAStartup failed!\n");
        exit(1);
    }

    UDPClient = socket(AF_INET, SOCK_DGRAM, 0);
    if (UDPClient == INVALID_SOCKET)
    {
        printf("Failed to create socket(): %d\n", WSAGetLastError());
        exit(1);
    }

    UDPServer.sin_family = AF_INET;
    UDPServer.sin_addr.s_addr = inet_addr(serverIpAddress);
    UDPServer.sin_port = htons(portNumber);
    
    ipAddrSize = sizeof(UDPServer);
	time_old = getTime();
	srand(time(NULL));
	for(i = 0; i < MAXCOUNT; i++)
    {
		time_interval = 0;
		while (time_interval < PERIOD)
		{
			time_new = getTime();
			time_interval = time_new - time_old;
		}
		time_old = time_new;
	    
		itoa(rand()%(NUMBER_RANGE+1),sendMessageStr,10);
        
        sendStatus = sendto(UDPClient, sendMessageStr, strlen(sendMessageStr), 0, (struct sockaddr*)&UDPServer, &ipAddrSize);

        if (sendStatus == 0)
            break;
        else if (sendStatus == SOCKET_ERROR)
        {
            printf("Failed to send(): %d\n", WSAGetLastError());
            break;
        }
        printf("Step=%4d; Time Interval=%8.6fs; Sent Msg = %4s; Sent %3d byte/s\n", i+1,time_interval,sendMessageStr,sendStatus);
    }

    srand(time(NULL));
    itoa(rand() % (NUMBER_RANGE + 1), randomNumber, 10);
    time_t time1 = time(NULL);
    char* time_str = ctime(&time1);

    time_str[strlen(time_str) - 1] = '/0';
    strcat(sendMessageStr, time_str);
    strcat(sendMessageStr, randomNumber);
    sendStatus = send(UDPClient, sendMessageStr, strlen(sendMessageStr), 0);

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


    
    
    
    )
    

	sendto(UDPClient, "EXIT", strlen("EXIT"), 0, (struct sockaddr*)&UDPServer, &ipAddrSize);
    
    printf("--- Transmission complete, closing socket ---\n");
	closesocket(UDPClient);

    free(serverIpAddress);

    WSACleanup();
	
    return 0;
}