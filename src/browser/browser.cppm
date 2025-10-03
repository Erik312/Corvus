module;

#include <iostream>
#include <string>
#include <map>



export module browser;

import urlparser;
import websocket;
import webparser;
import spartan_gui;

// MainBrowser - MainBrowser is a Class used as the main browser interface. 

export class MainBrowser
{
public:
    std::string m_web;
    std::string m_data;
    UrlParser m_parser;
    WebSocket m_socket;
    WebParser m_htmlparse;
    MainBrowser(std::string webSite){
        m_web=webSite;

    };
    ~MainBrowser(){};

    int getWeb(){
    std::map<std::string,std::string> webMap;
    if(m_parser.parse_url(webMap,m_web) != 0){
        return -1;
    }
    if(webMap["Scheme"][4] == 's'){
        std::cout << "using https" << "\n";
        if(m_socket.getHttps(webMap,m_data) !=0){
        return -1;
    }

    }else{
        std::cout << "using http" << "\n";
        std::cout << webMap["Scheme"] << "\n";
        if(m_socket.getHttp(webMap,m_data) !=0){
        return -1;
        }
    }
    
    return 0;
};

std::string getText(){
    
    int styleFind=m_htmlparse.wordFind("</style>",m_data); // locates and indexes closing style tag
    std::string resultHtml="";
    if(styleFind == -1){
        resultHtml=m_htmlparse.parseWeb(m_data); // closing tag not found parse raw
    }else{
        std::string extractedHtml=m_htmlparse.extractStyle(styleFind,m_data); // remove style tag and contents from data
        resultHtml=m_htmlparse.parseWeb(extractedHtml); // parse text inside body tag
    }
    return resultHtml;
};

void renderText(std::string renderData){
    std::cout << "------------------------------" << " Spartan " << "------------------------------" << "\n";
    std::cout << renderData;
    SpartanGui browserGui;
    browserGui.renderScreen(renderData);
    return;
};

void run(){
    std::cout << "This browser is now running" << "\n";
    this->getWeb();
    std::string mainData=this->getText();
    this->renderText(mainData);
    return;
};

};




