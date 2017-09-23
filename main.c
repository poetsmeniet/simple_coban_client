#include <stdio.h>
#include <unistd.h>
#include "config.h"
#include "gpsTools.h"
#include "coban.h"
#include "logger.h"
#define LOGFILE "simple_coban.log"

int main(void){
    //Initialize logger
    initLogr(LOGFILE);
    logr(1, "System startup");

    //Define configuration struct 
    appConfig config;

    //Populate configuration
    if(!getConfig(&config)) //log to logger, but contine
        printf("Error in config, not loading changes.\n"); 

    //Define position data structure
    gpsPos myPos;

    while(1){
        //Glean GPS position data
        unsigned int gpsFormat = 2; //decDeg
        returnGPSPos(&myPos, config.gpsDeviceName, gpsFormat);

        //Send in data using COBAN to tracker
        if(deliverPositionReport(&myPos, &config) == 0)
            logr(1, "Position report delivered");
        else
            logr(2, "Position report delivered failed");

        sleep(config.sendIntervalSecs);
    }

    return 0;
}
