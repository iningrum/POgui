#pragma once
#define TYPE float
#include "sensor.h"
#include "base.h"
#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <string>
const CSensor<TYPE>* MakeSensor(std::string line)
{
    std::array<std::string,3> params;
    { // preparse
        std::string temp;
        unsigned int i = 0;
        for( auto c:line)
        {
            if (c==',')
            {
                params.at(i) = temp;
                temp.clear();
                i++;
            }
            else temp+=c;
        }
        if (i==2)
        {
            params.at(i) = temp;
            temp.clear();
            i++;
        }
    }
    { // return
        std::string& type = params[0];
        float min = stof(params[1]);
        float max = stof(params[2]);
        if (type=="temperature")
            return new const CTemperatureSensor<TYPE>(min,max);
        else if(type=="humidity")
            return new const CHumiditySensor<TYPE>(min,max);
        else if(type=="wind")
            return new const CWindSensor<TYPE>(min,max);
        else if(type=="pressure")
            return new const CPressureSensor<TYPE>(min,max);
        else if(type=="insolation")
            return new const CInsolationSensor<TYPE>(min,max);
        else throw 1;
    }
    
}
const CBase<TYPE>* LoadMachineState()
{ // return vector of sensors
    /*std::ifstream file("machineState.csv");
    std::vector<const CSensor<TYPE>*> result;
    std::string line;
    while(std::getline(file,line))
    {
        std::cout <<"aaa   " <<line << std::endl;
        result.push_back(MakeSensor(line));
    }
    std::cout << "\n-->=> " << result.size() << std::endl;*/
    std::vector<const CSensor<TYPE>*> result;
    result.push_back(new CTemperatureSensor<float>(10,40));
    result.push_back(new CTemperatureSensor<float>(-60,40));
    result.push_back(new CTemperatureSensor<float>(100,200));
    result.push_back(new CTemperatureSensor<float>(-600,400));
    result.push_back(new CTemperatureSensor<float>(150,450));
    result.push_back(new CTemperatureSensor<float>(130,400));
    result.push_back(new CTemperatureSensor<float>(10,40));
    result.push_back(new CTemperatureSensor<float>(0,80));
    return new CBase<TYPE>(result);
}