/* udpserverclient.h
   header file for UdpServer.c and UdpClient.c

      initially programmed by Glen Tian
              on 23 February 2018
              in Brisbane
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <windows.h>  /* for timing control */

#define BUFFER_SIZE 128

/* get time. Demonstration only */
/* Note: better error checking and handling required in this function. */
double getTime(void)
{
	LARGE_INTEGER ticksPerSecond;
    LARGE_INTEGER tick;           /* time instant */
    LARGE_INTEGER startTicks;

    /* get the accuracy */
    if (!QueryPerformanceFrequency(&ticksPerSecond))
		printf("\tQueryPerformance not present.");

    /* check tick counter */
    if (!QueryPerformanceCounter(&tick)) 
		printf("\tTimer tick counter not installed."); 

    QueryPerformanceCounter(&startTicks); 
     
	return  (double)startTicks.QuadPart/(double)ticksPerSecond.QuadPart;
}

int captureConfig(char *configFile, char **ip, int *port) {
	// Capture the client IP address and port from the configFile specified
	FILE* cfg;
	char line[BUFFER_SIZE];
	cfg = fopen(configFile, "r");
	if (cfg) {
		while (fgets(&line, BUFFER_SIZE, cfg) != NULL) {
			if (line[0] == '\n' || line[0] == ' ' || line[0] == '#') {
				// ignore empty and comment lines
				continue;
			}
			// Removing trailing newline character
			char* token = strtok(line, "\n");
			// Ensure we are extracting the correct values
			if (strstr(line, "IP_ADDRESS") != NULL) {
				token = strtok(token, "=");
				token = strtok(NULL, " ");
				strcpy(*ip, token);
			}
			else if (strstr(line, "PORT") != NULL) {
				token = strtok(token, "=");
				token = strtok(NULL, " ");
				*port = atoi(token);
			}
		}
		fclose(cfg);
	}
	else {
		printf("No '%s' file found in execution directory\n\n", configFile);
		exit(1);
	}
}