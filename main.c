#include <stdio.h>
#include "config.h"

int main(void){
    
    appConfig config;
    if(!getConfig(&config))
        printf("Error in config, not loading changes.\n"); //log to logger, but contine

    printf("\ntesting getconfig\nservername: %s\n", config.serverName);
    printf("serverport: %i\n", config.serverPort);
    printf("sendIntervalSecs: %d\n", config.sendIntervalSecs);
    printf("gpsDeviceName: %s\n", config.gpsDeviceName);
    printf("gpsDeviceNmeaProtocol: %s\n", config.gpsDeviceNmeaProtocol);
    printf("adminEmail: %s\n", config.adminEmail);
    return 0;
}
