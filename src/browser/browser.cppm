module;

#include "../../includes/IMGUI/imgui.h"
#include "../../includes/IMGUI/imgui_impl_glfw.h"
#include "../../includes/IMGUI/imgui_impl_opengl3.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>

#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>




export module browser;

import urlparser;
import websocket;
import webparser;
import gui;

// MainBrowser - MainBrowser is a Class used as the main browser interface. 

export class MainBrowser
{
public:
    int m_currentPosition=0;
    std::string m_web;
    std::string m_data;
    std::string m_formattedData;
    std::vector<std::string> m_sessionHistory;
    UrlParser m_parser;
    WebSocket m_socket;
    WebParser m_htmlparse;

    MainBrowser(){};
    ~MainBrowser(){};

    int getWeb(){
        std::map<std::string,std::string> webMap;
        if(m_parser.parse_url(webMap,m_web) != 0){
            return -1;
        }
 
        if(webMap["Path"] == " " || webMap["Path"] == ""){
            webMap["Path"]="/";
        }
        if(webMap["Scheme"][4] == 's'){
            std::cout << "using https" << "\n";
            if(m_socket.getHttps(webMap,m_data) !=0){
            return -1;
        }

        }else{
            std::cout << "using http" << "\n";
            if(m_socket.getHttp(webMap,m_data) !=0){
            return -1;
            }
        }
    
        return 0;
};

std::string getText(){
    
    int styleFind=m_htmlparse.wordFind("</style>",m_data); // locates and indexes closing style tag
    std::string resultHtml;
    if(styleFind == -1){
        resultHtml=m_htmlparse.parseWeb(m_data); // closing tag not found parse raw
    }else{
        std::string extractedHtml=m_htmlparse.extractStyle(styleFind,m_data); // remove style tag and contents from data
        resultHtml=m_htmlparse.parseWeb(extractedHtml); // parse text inside body tag
    }
    return resultHtml;
};

void renderText(){
    glfwInit();
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 1024, " C O R V U S", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //ImGuiIO &io = ImGui::GetIO(); 
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    std::string screenData="CORVUS WEB BROWSER";

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);



        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos); 
        ImGui::SetNextWindowSize(viewport->Size);
            

        // render your GUI
        ImGui::Begin("demo",NULL,ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
        char userInputBuffer[128]="";
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        if(ImGui::Button("back", ImVec2{100,20})){
            if(m_currentPosition != 0){
                m_currentPosition=m_currentPosition - 1;
                std::string backUrl=m_sessionHistory[m_currentPosition];
                m_web=backUrl;
                this->getWeb();
                std::string backData=this->getText();
                m_formattedData=backData;
                screenData=m_formattedData;
            }
           
        }

        ImGui::SameLine();

        if(ImGui::Button("forward", ImVec2{100,20})){
            if(m_currentPosition != static_cast<int>(m_sessionHistory.size())){
                m_currentPosition=m_currentPosition + 1;
                std::string forwardUrl=m_sessionHistory[m_currentPosition];
                m_web=forwardUrl;
                this->getWeb();
                std::string forwardData=this->getText();
                m_formattedData=forwardData;
                screenData=m_formattedData;
            }
        }

        ImGui::SameLine();
        ImGui::PushItemWidth(ImGui::GetWindowWidth() - 340);
        ImGui::InputText("##",userInputBuffer,sizeof(userInputBuffer),ImGuiInputTextFlags_EnterReturnsTrue);
        ImGui::SameLine();

        if(ImGui::Button("refresh", ImVec2{100,20})){
            this->getWeb();
            std::string mainData=this->getText();
            m_formattedData=mainData;
            screenData=m_formattedData;
        }

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::TextUnformatted(screenData.c_str(),NULL);

        
        if(ImGui::IsKeyPressed(ImGuiKey_Enter)){
            if(userInputBuffer[0] != '\0'){
                m_web=userInputBuffer;
                this->getWeb();
                m_sessionHistory.push_back(m_web);
                m_currentPosition=m_sessionHistory.size() - 1;
                std::string mainData=this->getText();
                m_formattedData=mainData;
                screenData=m_formattedData;
                userInputBuffer[0]='\0';

            }
        }
                
        ImGui::End();
        
        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glfwSwapBuffers(window);
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return;
};

void run(){
    this->renderText();
    return;
};

};

