module;


#include "../../includes/IMGUI/imgui.h"
#include "../../includes/IMGUI/imgui_impl_glfw.h"
#include "../../includes/IMGUI/imgui_impl_opengl3.h"
#include <stdio.h>
#include <string>
#include <vector>
#define GL_SILENCE_DEPRECATION
//#if defined(IMGUI_IMPL_OPENGL_ES2)
//#include <GLES2/gl2.h>
//#endif
//#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <GLFW/glfw3.h>

export module gui;

export class Gui{
    public:
        Gui(){};
        ~Gui(){};
        void renderScreen(std::string &browserData){
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
                char userInputBuffer[]="";
                std::string testData=browserData;
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Button("back", ImVec2{100,20});
                ImGui::SameLine();
                ImGui::Button("forward", ImVec2{100,20});
                ImGui::SameLine();
                ImGui::PushItemWidth(ImGui::GetWindowWidth() - 340);
                ImGui::InputText("##",userInputBuffer,sizeof(userInputBuffer));
                ImGui::SameLine();
                ImGui::Button("refresh", ImVec2{100,20});
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::TextUnformatted(testData.c_str(),NULL);
                
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

};