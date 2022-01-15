// DO NOT LINK
// Works only for linux that runs xorg
#define TASKBAR 70
#include <string>
#include <fstream>
#include <X11/Xlib.h>
#include <iostream>

int main()
{
    Display *d = XOpenDisplay(NULL);
    Screen *s = DefaultScreenOfDisplay(d);
    std::ofstream dimensions("./lib/dimensions.h",std::ofstream::trunc);
    //dimensions.open("gg.txt");
    //dimensions.open("../lib/dimensions.h");
    dimensions << "#define MAX_H " + std::to_string(s->height-TASKBAR) << "\n#define MAX_W " + std::to_string(s->width) <<std::endl;
    dimensions.close();
}