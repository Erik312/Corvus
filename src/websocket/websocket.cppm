//
// websocket.cppm - A socket wrapper 
// version 1.0
// Written by Erik Ramos(erik.ramos315@gmail.com)
// 
//

module;


#include <iostream>
#include <map>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"


export module websocket;

// WebSocket - A bsd socket class wrapper
export class WebSocket{
public:
    WebSocket(){};
    ~WebSocket(){};
 

    // Gets requested website,connects and communicates.Takes a map of strings as url and a string as a buffer.
    // parameter: std::map<string,string> myMap, string &dataBuffer.
    // returns 0 on success.
    int getHttp(std::map<std::string,std::string> myMap,std::string &dataBuffer){
        std::map<std::string,std::string> tempMap=myMap;
        int sockfd; // main socket object
        char buff[1024];
        std::string recvBuffer;
        struct addrinfo hints, *servinfo, *p;
        std::string tempHost=tempMap["Hostname"];
        std::string tempPath=tempMap["Path"];
        std::string myPort="80";

        memset(&hints,0,sizeof(hints)); // zero hints container
        hints.ai_family=AF_UNSPEC; // IPV4 or IPV6
        hints.ai_socktype=SOCK_STREAM; // TCP socket
        hints.ai_flags=AI_PASSIVE; // additional flags

        //resolve url address
        int resolvedAddr=getaddrinfo(tempHost.c_str(),myPort.c_str(),&hints,&servinfo); 
        if(resolvedAddr!= 0){ 
            std::cout << "Error: error resolving address" << "\n";
            return -1;
        }

        // try all in linked list until connect or failure
        for(p=servinfo; p!=NULL; p=p->ai_next){
            if((sockfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1){
                continue;
            }
            if(connect(sockfd,p->ai_addr,p->ai_addrlen) == -1){
                close(sockfd);
                continue;
            }
            break;

        }

        if(p==NULL){
            std::cout << "failed to connect" << "\n";
            return -1;
        }

        std::cout << "Connecting..." << "\n";

        freeaddrinfo(servinfo); // free memory 

        std::string sendMsg="GET "+tempPath+ " HTTP/1.0\r\nHost: "+tempHost+"\r\n\r\n";

        // send message to server
        if(send(sockfd,sendMsg.c_str(),strlen(sendMsg.c_str()),0)< 0){
            std::cout << "Error: sending request message" << "\n";
            return -1;
        }

        // loop until all data is received
        while(1){
            memset(buff,0,sizeof(buff)); // zero buffer
            int recvData=recv(sockfd,buff,1024-1,0);
            if(recvData == 0){
                break;
            }
            if(recvData == -1){
                std::cout << "An error has occured" << "\n";
                return -1;
            }
            recvBuffer+=buff; // append buff data to recvBuffer string.
            continue;
        }
        dataBuffer=recvBuffer;
        std::cout << "\n";
        close(sockfd);
        return 0;

    };

    //HTTPS Support
    int getHttps(std::map<std::string,std::string> myMap,std::string &dataBuffer){
        std::map<std::string,std::string> tempMap=myMap;
        int sockfd; // main socket object
        SSL *ssl; // main ssl object
        SSL_CTX *ctx=SSL_CTX_new(TLS_client_method()); // set context method for ssl object
        SSL_library_init(); // initialize ssl object.
        OpenSSL_add_all_algorithms(); //load ssl algo
        SSL_load_error_strings();
        ssl=SSL_new(ctx);// set ssl config using (ctx);
        char buff[1024];
        std::string recvBuffer;
        struct addrinfo hints, *servinfo, *p;
        std::string tempHost=tempMap["Hostname"];
        std::string tempPath=tempMap["Path"];
        std::string myPort="443"; // port 443 for secure connection

        memset(&hints,0,sizeof(hints)); // zero hints container
        hints.ai_family=AF_UNSPEC; // IPV4 or IPV6
        hints.ai_socktype=SOCK_STREAM; // TCP socket
        hints.ai_flags=AI_PASSIVE; // additional flags

        int resolvedAddr=getaddrinfo(tempHost.c_str(),myPort.c_str(),&hints,&servinfo);
        //resolve url address 
        if(resolvedAddr!= 0){ 
            std::cout << "Error: error resolving address" << "\n";
            return -1;
        }

        // try all in linked list until connect or failure
        for(p=servinfo; p!=NULL; p=p->ai_next){
            if((sockfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1){
                continue;
            }

            if(connect(sockfd,p->ai_addr,p->ai_addrlen) == -1){ 
                close(sockfd);
                continue;
            }
            break;

        }

        SSL_set_fd(ssl,sockfd); // wrap socket with ssl wrapper
        int safeConnect=SSL_connect(ssl); // establish connection using socket wrapped with ssl
        
        if (safeConnect <=0){ // check for connection errors and return error string
            int myErr=SSL_get_error(ssl,safeConnect);
            if(myErr != SSL_ERROR_NONE){
                std::string errString=ERR_error_string(ERR_get_error(),NULL);
                std::cout << errString << "\n";
            }
        }
        

        if(p==NULL){
            std::cout << "failed to connect" << "\n";
            return -1;
        }

        std::cout << "Connecting..." << "\n";

        freeaddrinfo(servinfo); // free memory 

        std::string sendMsg="GET "+tempPath+ " HTTP/1.0\r\nHost: "+tempHost+"\r\n\r\n";

        // send message to server
        int bytesWrite=SSL_write(ssl,sendMsg.c_str(),strlen(sendMsg.c_str()));

        if(bytesWrite <= 0){
            std::cout << "Error: " <<"\n";
            std::cout << bytesWrite << "\n";
            return -1;
        }

        // loop until all data is received
        while(1){
            memset(buff,0,sizeof(buff)); // zero buffer
            int recvData=SSL_read(ssl,buff,1024-1); // ssl read
            if(recvData == 0){
                break;
            }
            if(recvData == -1){
                std::cout << "An error has occured while receiving data" << "\n";
                return -1;
            }
            recvBuffer+=buff; // append buff data to recvBuffer string.
            continue;
        }
        dataBuffer=recvBuffer;
        std::cout << "\n";
        SSL_shutdown(ssl);
        SSL_CTX_free(ctx);
        SSL_free(ssl);
        close(sockfd);
        return 0;

    };

};