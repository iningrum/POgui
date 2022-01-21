#pragma once
#include "../lib/primlib.h"
#include "../config.h"
#include "cpoint.h"
#include "winsys.h"
#include <list>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <iostream>
/*
    I guess CSensor should consist of makeMeasurement(actual sensor) , Window with graph(sdl addition). 
    CSensor would be responsible for returning any form of data we want
*/
class CSensorGraph : public CFramedWindow
{
public:
    float minV;
    float maxV;
    std::vector<TYPE> Y;
    std::vector<float> X;
    std::pair<float,float> real_topleft;
    std::pair<float, float> multipliers;
    std::pair<float, float> specialPoint;
    std::pair<float, float> shift;
    void flush()
    {
        for(auto &v:Y)
        {
            v=0;
        }
        this->str = "Loading...";
    }
    CSensorGraph(CRect r,float x,float y,float min, float max, color wc = DWC, color fc = DFC) : CFramedWindow(r, wc, fc)
    {
        minV = min;
        maxV = max;
        this -> str = "Loading...";
        for (int i=0; i<8; i++)
            Y.push_back(0);
        real_topleft = std::make_pair(x,y);
        this->scaleGraph();
        //this->scaleY();
    }
    void push_back(TYPE val)
    {
        Y.erase(Y.begin());
        Y.push_back(val*multipliers.second);
        //float& v = *Y.end();
        
    }
    void scaleY()
    {
        for (auto &v : Y)
            v *= multipliers.second;
    }
    void scaleGraph()
    {
        float rltlX = real_topleft.first;//geom.size.x;
        float rltlY = real_topleft.second;//geom.size.y; 
        { // establish mutipliers
            float ymult = abs(minV - maxV) / abs(geom.size.y);
            float xmult = abs(geom.size.x) / 7;
            multipliers = std::make_pair(xmult, ymult);
            this->newX();
        }
        { // establish special point
            float yval = rltlY+geom.size.y/2 ;//* 1.02 + (geom.size.y) / 2;
            float xval = rltlX;
            specialPoint = std::make_pair(xval, yval);
        }
        { // establish shift
            //float min = *std::min_element(Y.begin(), Y.end());
            //float max = *std::max_element(Y.begin(), Y.end());
            float yval = specialPoint.second;
            float xval = (X[0] - specialPoint.first);
            shift = std::make_pair(xval, yval);
        }
    }
    void newX()
    {
        X.clear();
        float val = real_topleft.first;
        for (auto const &i : Y)
        {
            X.push_back(val);
            val += multipliers.first;
        }
    }
    std::pair<std::vector<float>, std::vector<TYPE>> Transp()
    {
        auto ys = Y;
        auto xs = X;
        {
            for (auto &v : ys)
            {
                v += specialPoint.second;
                v -= 2*(v-specialPoint.second);
            }
            //Y[0] +=specialPoint.second;//real_topleft.second;
            for (auto &v : xs)
            {
                v += shift.first;
            }
        }
        return std::make_pair(xs,ys);
    }
    void transpose()
    {
        {
            for (auto &v : Y)
            {
                v += specialPoint.second;
                v -= 2*(v-specialPoint.second);
            }
            //Y[0] +=specialPoint.second;//real_topleft.second;
            for (auto &v : X)
            {
                v += shift.first;
            }
        }
    }
    void paint()
    {
        CFramedWindow::paint();
        gfx_textout(real_topleft.first*1.01,real_topleft.second+geom.size.y*0.01,this->str.c_str(),GREEN);
        //float &ymul = multipliers.second;
        auto data = this->Transp();
        auto xx = data.first;
        auto yy = data.second;
        auto xs = xx.begin();
        auto ys = yy.begin();
        while (ys != yy.end()-1 )
        {
            float Xa = *xs;
            float Xb = *(xs + 1);
            TYPE Ya = *ys;
            TYPE Yb = *(ys + 1);
            gfx_wline(Xa, Ya, Xb, Yb, GREEN, 5);
            xs++;
            ys++;
        }
        gfx_wline(specialPoint.first, specialPoint.second, specialPoint.first+geom.size.x, specialPoint.second, WHITE, 2);
    }
    void Move(int x, int y)
    {
        geom.Move(x,y);
        real_topleft.first+=x;
        real_topleft.second+=y;
    }
};