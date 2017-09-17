#include <stdio.h>
#include "config.h"

int main(void){
    
    appConfig config;
    getConfig(&config);

    printf("testing getconfig, servername: %s\n", config.serverName);
    return 0;
}
