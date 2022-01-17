#pragma once
#include "../lib/primlib.h"
#include "cpoint.h"
#include "winsys.h"
#include <list>
#include <utility>
#include <string>
/*
    I guess CSensor should consist of makeMeasurement(actual sensor) , Window with graph(sdl addition). 
    CSensor would be responsible for returning any form of data we want
*/
class CSensorGraph : public CFramedWindow{
    public:
    CSensorGraph(CRect r, color wc = DWC, color fc = DFC) : CFramedWindow(r, wc, fc) {}
    std::list<std::pair<int,float>> values;
    void paint()
    {
        CFramedWindow::paint();
        auto a = values.begin();
        auto b = values.begin()++;
        while(b!=values.end())
        {
            gfx_line(a->first,a->second,b->first,b->second,wc);
            a++;
            b++;
        }
    }
};