#ifndef config_H_
#define config_H_

typedef struct applicationConfguration{
    char serverName[200];
    int serverPort;
    size_t intervalSecs;
    char gpsDevice[100];
    char gpsNmeaProtocol[100];
    char adminEmail[50];
}appConfig;

void getConfig(appConfig *config);

#endif
