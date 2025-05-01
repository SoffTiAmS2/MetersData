#pragma once
#include <string>


class Date{
private:
    int year;
    int month;
    int day;
public:
    Date(int year, int month, int day);
    const int getYear() const;
    const int getDay() const ;
    const int getMonth() const;
    const std::string toString() const; 
};