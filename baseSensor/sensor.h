#pragma once
#include <cstdlib>
#include <utility>
#include <string>
#include <iostream>
#include "rand.h"
#include "../config.h"
using string = std::string;
using namespace std;
enum CSensorType
{
    NonExistant_e,
    Temperature_e,
    Humidity_e,
    Wind_e,
    Pressure_e,
    Insolation_e
};
class iCsensor;

template <class T>
class CSensor
{

private:
    T lowLimit;
    T highLimit;
    T makeMeasurement() const { 
        return getRandomNumber(lowLimit,highLimit);
        }

public:
    int id = 0;
    //static CSensor *Make(CSensorType type, float min, float max);
    friend ostream& operator <<(ostream& os,const CSensor<T>& obj)
    {
        os <<"\n" << obj.getName() << "\t" << obj.makeMeasurement() << "  " << obj.getUnit() << "\n";
        return os;
    }
    CSensor(T lowLimit, T highLimit) : lowLimit(lowLimit),
                                               highLimit(highLimit)
    {
        this->id = ID;
        ID++;
    }
    CSensor() {}
    T getMeasurement() const
    {
        return makeMeasurement();
    }
    virtual ~CSensor(){}
    virtual string getName() const = 0;
    virtual string getUnit() const = 0;
};
template <class T>
class CTemperatureSensor : public CSensor<T>
{
public:
    CTemperatureSensor(T lowLimit, T highLimit) : CSensor<T>(lowLimit, highLimit) {}
    string getName() const
    {
        return "Temperature sensor  "+to_string(this->id);
    }
    string getUnit() const
    {
        return "\t st. Celshusza\n";
    }
};
template <class T>
class CHumiditySensor : public CSensor<T>
{
public:
    CHumiditySensor(T lowLimit, T highLimit) : CSensor<T>(lowLimit, highLimit) {}
    string getName() const
    {
        return "Humidity sensor  "+to_string(this->id);
    }
    string getUnit() const
    {
        return "\t%\n";
    }
};
template <class T>
class CWindSensor : public CSensor<T>
{
public:
    CWindSensor(T lowLimit, T highLimit) : CSensor<T>(lowLimit, highLimit) {}
    string getName() const
    {
        return "Wind sensor  "+to_string(this->id);
    }
    string getUnit() const
    {
        return "\tm/s\n";
    }
};
template <class T>
class CPressureSensor : public CSensor<T>
{
public:
    CPressureSensor(T lowLimit, T highLimit) : CSensor<T>(lowLimit, highLimit) {}
    string getName() const
    {
        return "Pressure sensor  "+to_string(this->id);
    }
    string getUnit() const
    {
        return "\tHpa\n";
    }
};
template <class T>
class CInsolationSensor : public CSensor<T>
{
public:
    CInsolationSensor(T lowLimit, T highLimit) : CSensor<T>(lowLimit, highLimit) {}
    string getName() const
    {
        return "Insolation sensor  "+to_string(this->id);
    }
    string getUnit() const
    {
        return "\tW/m^2\n";
    }
};

/*inline CSensor* CSensor::Make(CSensorType type, float min, float max)
{
    switch (type)
    {
    case Temperature_e:
        return new CTemperatureSensor(min, max);
        break;
    case Humidity_e:
        return new CHumiditySensor(min, max);
        break;
    case Wind_e:
        return new CWindSensor(min, max);
        break;
    case Pressure_e:
        return new CPressureSensor(min, max);
        break;
    case Insolation_e:
        return new CInsolationSensor(min, max);
        break;
    default:
        return nullptr;
    }
}
class iCSensor
{
public:
    iCSensor(CSensorType type, float min, float max)
    {
        this->ptr = CSensor::Make(type, min, max);
    }
    ~iCSensor()
    {
        delete this->ptr;
    }
    CSensor *get()
    {
        CSensor* tmp = this->ptr;
        this->ptr = nullptr;
        return tmp;
    }

private:
    CSensor *ptr;
};*/