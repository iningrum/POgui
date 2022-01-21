#pragma once
#define TYPE float
#include "sensor.h"
#include "base.h"
#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <fstream>
#include <string>
const CSensor<TYPE> *MakeSensor(std::string line)
{
    using str = std::string;

    //line = strip(line);
    std::vector<std::string> command = split(line, ',');
    std::map<str, CSensorType> possible_types;
    str &type = command.at(0);
    str &min = command.at(1);
    str &max = command.at(2);
    std::cout << "\ntype\t" << type<<"\n";
    possible_types["temperature"] = Temperature_e;
    possible_types["humidity"] = Humidity_e;
    possible_types["wind"] = Wind_e;
    possible_types["pressure"] = Pressure_e;
    possible_types["insolation"] = Insolation_e;
    CSensorType t;
    { // get type
        auto where = possible_types.find(type);
        t = (where != possible_types.end()) ? where->second : NonExistant_e;
    }
    switch (t)
    {
    case Temperature_e:
        return new CTemperatureSensor<TYPE>(stof(min), stof(max));
    case Humidity_e:
        return new CHumiditySensor<TYPE>(stof(min), stof(max));
    case Wind_e:
        return new CWindSensor<TYPE>(stof(min), stof(max));
    case Pressure_e:
        return new CPressureSensor<TYPE>(stof(min), stof(max));
    case Insolation_e:
        return new CInsolationSensor<TYPE>(stof(min), stof(max));
    case NonExistant_e:
        return nullptr;
    }
    return nullptr;
}
const CBase<TYPE> *LoadMachineState()
{ // return vector of sensors
    std::ifstream file("baseSensor/machineState.csv");
    std::vector<const CSensor<TYPE>*> result;
    std::string line;
    while(std::getline(file,line))
    {
        std::cout <<"aaa   " <<line << std::endl;
        result.push_back(MakeSensor(line));
    }
    for (int i =0; i<(result.size()+8)%8;i++)
        result.push_back(new CNonexistantSensor<TYPE>(0,0));
    return new CBase<TYPE>(result);
}