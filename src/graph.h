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
    std::list<float> X;
    std::list<float> Y;
    void paint()
    {
        CFramedWindow::paint();
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
            gfx_wline(Xa,Ya,Xb,Yb,WHITE,5);
            xs++;
            ys++;
        }
    }
};