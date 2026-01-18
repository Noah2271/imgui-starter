#pragma once
#include <iostream>
#include "imgui/imgui.h"
#include <cstring>
#include <stdio.h>

class Logger
{
    public:

    bool scrollDown = true;

    //
    // singleton accessor
    //
    static Logger& GetInstance(){ static Logger instance; return instance;} 
    
    //
    // push log function
    // takes a log level and message pair and pushes it to log vector for display
    //
    void PushLog(int level, const char* message) { Items.push_back({level, Strdup(message)}); scrollDown = true;
    }

    //
    // set filter function
    // sets current filter to specified log level LogLevel type
    //
    void setFilter(int filter){ currentFilter = filter;
    }

    //
    // clear function
    // clears all logs from the vector along with memory
    //
    void Clear(){
        for(int i = 0; i < Items.Size; i++) ImGui::MemFree(Items[i].second);
        Items.clear(); 
        PushLog(1, "CONSOLE CLEARED");
    }

    //
    // print to file function
    // prints all current visible logs to logs.txt, specified in Application.cpp
    //
    void PrintToFile(const char* filename){ 
        FILE* file = nullptr;
        fopen_s(&file, filename, "w");
        if(file){
            for(int i = 0; i < Items.Size; i++){
                if(Items[i].first > currentFilter) continue;
                const char* levelStr = "";
                if(Items[i].first == 0){ levelStr = "[USER]"; }
                if(Items[i].first == 1){ levelStr = "[INFO]"; } 
                if(Items[i].first == 2){ levelStr = "[WARNING]"; }
                if(Items[i].first == 3){ levelStr = "[ERROR]"; }
                fprintf(file, "%s %s\n", levelStr, Items[i].second);
            }
            PushLog(1, "LOGS PRINTED TO: logs.txt");
            fclose(file);
        } else {
            std::cerr << "FAILED TO OPEN LOG FILE: " << filename << std::endl;
        }
    }

    //
    // draw function
    // draws the log window and skips logs that do not match the current LogLevel filter
    //
    void Draw()
    {
        for (int i = 0; i < Items.Size; i++){
            if (Items[i].first > currentFilter)continue;

            const char* levelStr = "";
            ImVec4 color = ImVec4(1, 1, 1, 1);

            switch (Items[i].first){
            case 0:
                levelStr = "[USER]";
                color = ImVec4(0.5f, 0.5f, 1.0f, 1.0f);
                break;
            case 1:
                levelStr = "[INFO]";
                color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
                break;
            case 2:
                levelStr = "[WARNING]";
                color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
                break;
            case 3:
                levelStr = "[ERROR]";
                color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
                break;
            }

            ImGui::TextColored(color, "%s", levelStr);
            ImGui::SameLine();
            ImGui::TextUnformatted(Items[i].second);
        }
        if(scrollDown)
            {
                ImGui::SetScrollHereY(1.0f);
                scrollDown = false;
            }
    }

    //
    // command line execute function
    // uses the demo Stricmp function to compare input to implemented commands and executes them
    //
    void Execute(const char* command){
        if(Stricmp(command, "clear") == 0){ Clear(); }
        else if(Stricmp(command, "filter1") == 0){ currentFilter = 1; PushLog(1, "FILTER SET TO INFO+"); }
        else if(Stricmp(command, "filter2") == 0){ currentFilter = 2; PushLog(2, "FILTER SET TO WARNING+"); }
        else if(Stricmp(command, "filter3") == 0){ currentFilter = 3; PushLog(3, "FILTER SET TO ERROR+"); }
        else if (Stricmp(command, "print") == 0) { PrintToFile("logs.txt"); }
        else if (Stricmp(command, "help") == 0) { PushLog(1, "AVAILABLE COMMANDS: clear, filter1, filter2, filter3, print, help"); }
        else{ PushLog(1, "UNKNOWN COMMAND"); }
    }

    private:
    //
    // constructor and destructor
    //
    Logger() = default;
    ~Logger() { Clear(); }

    //
    // vector of log level and message pair
    //
    ImVector<std::pair<int, char*>> Items;

    //
    // String helper functions from imgui_demo.cpp
    //
    int currentFilter = 3;
    static char* Strdup(const char* s) { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = ImGui::MemAlloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
    static int   Stricmp(const char* s1, const char* s2) { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }

};