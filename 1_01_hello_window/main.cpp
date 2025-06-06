#include <gl_util.h>
#include <iostream>

std::string proj_name = "1_01_hello_window";

int main(int argc, char* argv[])
{
    gl_util::Window window(800, 600, "Window");

    // --------------- Prase inputs ---------------
    std::cout << proj_name << ":\n" <<
              "\tYou can input 3 or 4 integer (range in[0,255]) "
              "to specify the background color of the window.\n" 
              "\t- 3 integer for RGB\n" 
              "\t- 4 integer for RGBA\n"
              "Press 'Esc' to exit.\n";

    if(argc >= 4){
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

        window.clear();
        
        window.refresh();
    }

    return 0;
}