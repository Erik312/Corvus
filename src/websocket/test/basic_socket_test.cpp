//
// basic_socket_test.cpp
// version 1.0
// Written by Erik Ramos(erikram312@gmail.com)
// 
//

#include <iostream>
#include <map>
#include <string>
#include <cassert>

import websocket;


int main(int argc, char const *argv[])
{
    WebSocket mySocket;
    string myBuffer;
    assert(typeid(mySocket)==typeid(WebSocket));
    std::map<std::string,std::string> myMap{{"Scheme","http://"},{"Hostname","www.example.com"},{"Path","/"}};
    assert(myMap["Path"]=="/");
    assert(myMap["Hostname"]=="www.example.com");
    assert(myMap["Scheme"]=="http://");
    int socketTest=mySocket.getData(myMap,myBuffer);
    assert(socketTest == 0);
    return 0;
}
