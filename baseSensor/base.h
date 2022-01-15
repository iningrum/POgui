#pragma once
//#include "stack.h"
#include "sensor.h"
#include "exception.h"
#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#define MAX_NUMBER_OF_SENSORS 5

/*
template <class T>
class CBase;

template <class T>
ostream& operator <<(ostream& os,const CBase<T>& obj);
*/

template <class T>
class CBase
{
public:
    std::vector<const CSensor<T>*> Sensors;
    CBase<T>(std::vector<const CSensor<T>*>::const_iterator begin, std::vector<const CSensor<T>*>::const_iterator end)
    {
        this->Sensors(begin,end);
    }
    CBase<T>(int val){Sensors.reserve(val);}
    friend ostream& operator <<(ostream& os,const CBase<T>& obj)
    {
        for (typename vector<const CSensor<T>*>::const_iterator it = obj.Sensors.begin(); it<obj.Sensors.end();it++)
        //for (auto sensor:Sensors)
            os << "\n" << **it;
        return os;
    }
    CBase<T>& operator +=(const CSensor<T>& obj)
    {
        this->Sensors.push_back(&obj);
        return *this;
    }
    CBase<T> operator -=(const CSensor<T>& obj)
    {
        auto where = find(Sensors.begin(),Sensors.end(),&obj);
        if (where!=Sensors.end())
        {
            Sensors.erase(where);
            return *this;
        }
        else throw CException("element not in the vector");
    }

    void setSensor(T* sensor)
    {
        this->Sensors.push_back(sensor);
    }
    /*~CBase()
    {
        for(auto &item: Sensors)
        {
            delete item;
        }
    }*/
    
};