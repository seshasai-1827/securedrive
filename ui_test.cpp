#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include "authorization.h"
#include<fstream>
using namespace ftxui;


void debug_log(const std::string& msg) {
    std::ofstream log("debug.log", std::ios::app);
    log << msg << std::endl;
}

int main() {
    std::string password;
    bool reply;

    auto textbox = Input(&password, "Enter password");

    auto component = CatchEvent(textbox, [&](Event event) {
    if (event == Event::Return) {
        //store_password(password.c_str());
        reply = verify_password(password.c_str());
        //debug_log(password);
        password.clear();
        return true;
    }
    return false;
    });
    
    auto renderer = Renderer(component, [&] {
        if(!reply){
        return vbox(
            
            
            text("Password") | bold,
            separator(),
            textbox->Render()
        );
    }
    else{
        return vbox(
            text("welcome to Journable")|bold,
            separator(),
            text("gay")
        
        );
    }
    }
    ) | border;

     

    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);
}