#pragma once
#include <cstdlib>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstdlib>
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
    T makeMeasurement() const
    {
        return getRandomNumber(lowLimit, highLimit);
    }

protected:
    mutable std::string MeasurmentsCsv;

public:
    int id = 0;
    //static CSensor *Make(CSensorType type, float min, float max);
    friend ostream &operator<<(ostream &os, const CSensor<T> &obj)
    {
        os << "\n"
           << obj.getName() << "\t" << obj.makeMeasurement() << "  " << obj.getUnit() << "\n";
        return os;
    }
    CSensor(T lowLimit, T highLimit) : lowLimit(lowLimit),
                                       highLimit(highLimit)
    {
        this->id = ID;
        ID++;
    }
    CSensor() {}
    T  virtual getMeasurement() const
    {
        T val = makeMeasurement();
        { // write value to file
            std::ofstream file;
            file.open(this->MeasurmentsCsv,std::fstream::app);
            file << (to_string(val)+",");
            file.close();
        }
        return val;
    }
    virtual ~CSensor() {}
    virtual void touch() const = 0;
    virtual string getName() const = 0;
    virtual string getUnit() const = 0;
};
template <class T>
class CTemperatureSensor : public CSensor<T>
{
public:
    CTemperatureSensor(T lowLimit, T highLimit) : CSensor<T>(lowLimit, highLimit) { this->touch(); }
    void touch() const
    {
        std::string filename = "readings/temperatureSensor_" + to_string(this->id);
        this->MeasurmentsCsv = filename;
        system(("touch " + filename).c_str());
    }
    string getName() const
    {
        return "Temperature sensor  " + to_string(this->id);
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
    CHumiditySensor(T lowLimit, T highLimit) : CSensor<T>(lowLimit, highLimit) { this->touch(); }
    void touch() const
    {
        std::string filename = "readings/himiditySensor_" + to_string(this->id);
        this->MeasurmentsCsv = filename;
        system(("touch " + filename).c_str());
    }
    string getName() const
    {
        return "Humidity sensor  " + to_string(this->id);
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
    CWindSensor(T lowLimit, T highLimit) : CSensor<T>(lowLimit, highLimit) { this->touch(); }
    void touch() const
    {
        std::string filename = "readings/windSensor_" + to_string(this->id);
        this->MeasurmentsCsv = filename;
        system(("touch " + filename).c_str());
    }
    string getName() const
    {
        return "Wind sensor  " + to_string(this->id);
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
    CPressureSensor(T lowLimit, T highLimit) : CSensor<T>(lowLimit, highLimit) { this->touch(); }
    void touch() const
    {
        std::string filename = "readings/pressureSensor_" + to_string(this->id);
        this->MeasurmentsCsv = filename;
        system(("touch " + filename).c_str());
    }
    string getName() const
    {
        return "Pressure sensor  " + to_string(this->id);
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
    CInsolationSensor(T lowLimit, T highLimit) : CSensor<T>(lowLimit, highLimit) { this->touch(); }
    void touch() const
    {
        std::string filename = "readings/insolationSensor_" + to_string(this->id);
        this->MeasurmentsCsv = filename;
        system(("touch " + filename).c_str());
    }
    string getName() const
    {
        return "Insolation sensor  " + to_string(this->id);
    }
    string getUnit() const
    {
        return "\tW/m^2\n";
    }
};
template <class T>
class CNonexistantSensor : public CSensor<T>
{
public:
    CNonexistantSensor(T lowLimit, T highLimit) : CSensor<T>(lowLimit, highLimit) { this->touch(); }
    void touch() const
    {
        // supposed to do nothing. This class is just a placeholder
    }
    string getName() const
    {
        return "No sensor there";
    }
    string getUnit() const
    {
        return "j";
    }
};
template <class T>
class CTimeSensor : public CSensor<T>
{
    public:
    CTimeSensor(){}
    void getMeasurement()
    {
        auto time = std::chrono::system_clock::now();
        std::time_t ftime =std::chrono::system_clock::to_time_t(time);
        std::ofstream file;
        file.open(this->MeasurmentsCsv,std::fstream::app);
        file << std::ctime(&ftime)<<",";
        file.close();
    }
    void touch() const
    {
        std::string filename = "readings/time_" + to_string(this->id);
        this->MeasurmentsCsv = filename;
        system(("touch " + filename).c_str());
    }
    string getName() const
    {
        return "";
    }
    string getUnit() const
    {
        return "";
    }
};
/*class iCSensor
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