#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#define CONFIGFILE "config.txt"
#define MAXLEN 50 

//A quick write for a simple configuration file
extern int getConfig(appConfig *config){
    size_t lineNr = 0;
    FILE *fp;
    fp = fopen(CONFIGFILE, "r");

    if(fp != NULL){
        while(!feof(fp)){
            lineNr++;
            char sKey[MAXLEN];
            char sVal[MAXLEN];

            fscanf(fp, "%s %s\n", &sKey[0], sVal);

            size_t keyLen = strlen(sKey) + 1;
            size_t valLen = strlen(sVal) + 1;
            if(keyLen > MAXLEN || valLen > MAXLEN){
               //please integrate logger function here
               printf("Configuration option larger than allowed max of %d on line number %d\n", MAXLEN, lineNr);
               return 0;
            }
            
            if(bcmp(&sKey[0], &"serverName", 10) == 0){
               memcpy(config->serverName, &sVal, valLen);
            }
            if(bcmp(&sKey[0], &"serverPort", 10) == 0){
               config->serverPort =(int)strtol(sVal, (char **)NULL, 10);
            }
            if(bcmp(&sKey[0], &"sendIntervalSecs", 16) == 0){
               config->sendIntervalSecs =(int)strtol(sVal, (char **)NULL, 10);
            }
            if(bcmp(&sKey[0], &"gpsDeviceName", 13) == 0){
               memcpy(config->gpsDeviceName, &sVal, valLen);
            }
            if(bcmp(&sKey[0], &"gpsDeviceNmeaProtocol", 21) == 0){
               memcpy(config->gpsDeviceNmeaProtocol, &sVal, valLen);
            }
            if(bcmp(&sKey[0], &"adminEmail", 10) == 0){
               memcpy(config->adminEmail, &sVal, valLen);
            }
        }
    }else{
        //Pocess error
        printf("No such file; '%s'\n", CONFIGFILE);
        return 0;
    }
    return 1;
}
