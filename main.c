#include <stdio.h>
#include "config.h"
#include "gpsTools.h"

int main(void){
    
    appConfig config;
    if(!getConfig(&config))
        printf("Error in config, not loading changes.\n"); //log to logger, but contine

    //printf("\ntesting getconfig\nservername: %s\n", config.serverName);
    //printf("serverport: %i\n", config.serverPort);
    //printf("sendIntervalSecs: %d\n", config.sendIntervalSecs);
    //printf("gpsDeviceName: %s\n", config.gpsDeviceName);
    //printf("gpsDeviceNmeaProtocol: %s\n", config.gpsDeviceNmeaProtocol);
    //printf("adminEmail: %s\n", config.adminEmail);

    gpsPos myPos;
    
    returnGPSPos(&myPos, config.gpsDeviceName);
    printf("lat: %f\n", myPos.lat);
    printf("lon: %f\n", myPos.lon);
    return 0;
}
