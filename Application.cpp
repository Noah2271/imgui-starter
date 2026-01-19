#include "Application.h"
#include "imgui/imgui.h"
#include "Logger.h"

namespace ClassGame {
        //
        // game starting point
        // this is called by the main render loop in main.cpp
        //
        void GameStartUp() 
        {
            // Initialize logging system
            Logger& logger = Logger::GetInstance();
            logger.PushLog(1, "WELCOME. USE COMMAND help FOR A LIST OF AVAILABLE COMMANDS");
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {
        /*/
            ImGui::DockSpaceOverViewport();
            ImGui::ShowDemoWindow();

            ImGui::Begin("ImGui Log Demo");
            ImGui::LogButtons();

            if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
            {
                ImGui::LogToClipboard();
                ImGui::LogText("Hello, world!");
                ImGui::LogFinish();
            }
            ImGui::End();
        /*/
            // 
            // main console window
            // this is where all logs will be displayed
            //
            static bool showFilters = false;
            Logger& logger = Logger::GetInstance();

            ImGui::Begin("Game Log Console");
            if(ImGui::Button("Clear")){ logger.Clear();}

            ImGui::SameLine();
            if(ImGui::Button("Test Info")){ logger.PushLog(1, "Player joined the game"); }

            ImGui::SameLine();
            if(ImGui::Button("Test Warning")){ logger.PushLog(2, "Player inventory is full"); }

            ImGui::SameLine(); 
            if(ImGui::Button("Test Error")){ logger.PushLog(3, "Player made illegal move"); }
            
            ImGui::SameLine();
            if(ImGui::Button("Print to File")){ logger.PushLog(1, "Printing logs to file..."); logger.PrintToFile("logs.txt"); }
            
            //
            // filter window
            // this is the button that opens a filter window to filter logs by type
            //
            ImGui::SameLine();
            if(ImGui::Button("Filters")){ showFilters = !showFilters; logger.PushLog(1, "TOGGLING FILTER WINDOW"); }
            
            if(showFilters){
                ImGui::Begin("Filters");
                if(ImGui::Button("Level 1: Info")){ logger.setFilter(1); logger.PushLog(1, "FILTER SET TO INFO ONLY"); }
                
                ImGui::SameLine();
                if(ImGui::Button("Level 2: Warning+")){ logger.setFilter(2); logger.PushLog(2, "FILTER SET TO WARNING+"); }

                ImGui::SameLine();
                if(ImGui::Button("Level 3: Error+")){ logger.setFilter(3); logger.PushLog(3, "FILTER SET TO ERROR+"); }

                ImGui::End();
            }

            ImGui::Separator();
            const float footer_height =
                ImGui::GetStyle().ItemSpacing.y +
                ImGui::GetFrameHeightWithSpacing();

            ImGui::BeginChild(
                "LogArea",
                ImVec2(0, -footer_height),
                false,
                ImGuiWindowFlags_HorizontalScrollbar
            );

            logger.Draw(); 

            ImGui::EndChild();

            ImGui::Separator();

            //
            // command line implementation
            // takes user input and executes commmands based on the input
            //
            static char Input[256] = "";
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;
            
            if(ImGui::InputText("Command Line", Input, IM_ARRAYSIZE(Input), flags)){
                if (Input[0] != '\0'){
                    logger.PushLog(0, Input);
                    logger.Execute(Input);
                    Input[0] = '\0';
                }
            }

            ImGui::End();

        }

        //
        // end turn is called by the game code at the end of each turn
        // this is where we check for a winner
        //
        void EndOfTurn() 
        {
        }
}
