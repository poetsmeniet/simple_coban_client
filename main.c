#include <stdio.h>
#include "config.h"
#include "gpsTools.h"
#include "coban.h"

int main(void){
    
    //Define configuration struct 
    appConfig config;

    //Populate configuration
    if(!getConfig(&config)) //log to logger, but contine
        printf("Error in config, not loading changes.\n"); 

    //Define position data structure
    gpsPos myPos;
    
    //Glean GPS position data
    unsigned int gpsFormat = 2; //decDeg
    returnGPSPos(&myPos, config.gpsDeviceName, gpsFormat);

    //Send in data using COBAN to tracker
    deliverPositionReport(&myPos, &config);
    return 0;
}
