#include <stdio.h>
#include <string.h>
#include "config.h"


void getConfig(appConfig *config){

    memcpy(config->serverName, "thomas@geenbs.nl", 17);
}
