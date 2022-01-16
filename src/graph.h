#pragma once
#include "cpoint.h"
#include <list>
#include <utility>
#include <string>
/*
    I guess CSensor should consist of makeMeasurement(actual sensor) , Window with graph(sdl addition). 
    CSensor would be responsible for returning any form of data we want
*/
struct SensorGraph{
    std::list<std::pair<float,std::string>> points; // value_timestamp
    CPoint ZeroZero;
    void Move(int x, int y)
    { // change it's position

    }
    void Render()
    {  // print lines out of points

    }
    std::string produceOutput(std::string sensorId)
    { // make csv string
        std::string& result = sensorId;
        for (auto value:points)
        {
            result+= to_string(value.first);
            result+=",";
        }
        return result;
    }
};