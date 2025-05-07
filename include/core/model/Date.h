#pragma once

#include <string>




class Date{
public:
    Date(int year, int month, int day);

    int getYear() const;
    int getMonth() const;
    int getDay() const ;

    std::string toString() const; 

private:
    int year;
    int month;
    int day;
};