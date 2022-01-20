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
    std::list<int> X;
    std::list<int> Y;
    void paint()
    {
        gfx_wline(0,100,50,140,BLACK,5);
        gfx_wline(50,140,200.5,200,BLACK,5);
        //CFramedWindow::paint();
        auto xs = X.begin();
        auto ys = Y.begin();
        auto next = Y.begin()++;
        for (int i = 0; i<Y.size();i++)
        {
            int Xa = *xs;
            int Ya = *ys;
            xs++;
            ys++;
            int Xb = *xs;
            int Yb = *ys;
            gfx_wline(Xa,Ya,Xb,Yb,BLACK,5);
            xs++;
            ys++;
        }
    }
};