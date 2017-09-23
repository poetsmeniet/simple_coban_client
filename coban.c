#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "config.h"
#include "gpsTools.h"
#include <arpa/inet.h>

static void createCobanString(char *buffer, gpsPos *myPos, appConfig *config){
    //Start appending data to report string
    strcpy(buffer,"imei:");
  
    //Imei
    char imeiString[16];
    snprintf(imeiString, 16, "%lli", config->imei);
    strcat(buffer, imeiString);
  
    //Add some (unused) parameters
    strcat(buffer, ",tracker,161208171150,,F,161148.000,A,");
    
    //Latitude
    char latString[12];
    snprintf(latString, 12, "%.4f", myPos->lat);
    strcat(buffer, latString);
    
    //Lat hemisphere
    char latHem[4];
    snprintf(latHem, 4, ",%c,", myPos->latHemisphere);
    strncat(buffer, latHem, 4);
    
    //Latitude
    char lonString[12];
    snprintf(lonString, 12, "%.5f", myPos->lon);
    strcat(buffer, lonString);
    
    //Lat hemisphere
    char lonHem[11];
    snprintf(lonHem, 11, ",%c,1.01,0;", myPos->lonHemisphere);
    strncat(buffer, lonHem, 11);
}

// A quick client for a one-off connection
extern int deliverPositionReport(gpsPos *myPos, appConfig *config){
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
  
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(config->serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(config->serverName);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
    addr_size = sizeof serverAddr;
   
    if(connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size)){
      return 1;
    }
  
    //Send COBAN auth
    strcpy(buffer,"##,imei:369546025829301,A;");
    if(send(clientSocket,buffer,strlen(buffer),MSG_NOSIGNAL) <= 0)
        return 1;
    recv(clientSocket, buffer, 1024, 0);
  
    //Create COBAN string to pass to tracking server
    createCobanString(buffer, myPos, config);
    
    //Send msg through socket
    if(send(clientSocket,buffer,strlen(buffer),MSG_NOSIGNAL) <= 0)
        return 1;
  
    //Exit tracker connection
    strcpy(buffer,"exit");
    if(send(clientSocket,buffer,strlen(buffer),MSG_NOSIGNAL) <= 0)
        return 1;

    return 0;
}
