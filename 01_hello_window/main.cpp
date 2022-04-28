#include "../gl_util/gl_window.h"
#include <iostream>

std::string proj_name = "01_hello_window";

int main(int argc, char* argv[])
{
    gl_util::Window window(800, 600);

    // --------------- Prase inputs ---------------
    if (argc <= 1){
        std::cout << proj_name << ":\n\tYou can input 3 or 4 integer to specify the background color of the window.\n" << "\t# 3 integer for RGB\n" << "\t# 4 integer for RGBA\n";
    }
    else if(argc >= 4){
        unsigned char R = std::stoi(argv[1]);
        unsigned char G = std::stoi(argv[2]);
        unsigned char B = std::stoi(argv[3]);
        unsigned char A = 255;
        if(argc == 5) A = std::stoi(argv[4]);

        window.setBackgroundColor(R,G,B,A);
    }
    // ---------------------------------------------


    // Window show
    while(!window.shouldClose()){
        window.activate();
        window.refresh();
    }
    window.release();

    return 0;
}