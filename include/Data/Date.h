#pragma once
#include <string>


class Date{
private:
    // поля год месяц день
    int year;
    int month;
    int day;
public:
    //Конструктор
    Date(int year, int month, int day);
    
    // Геттеры
    const int getYear() const;
    const int getMonth() const;
    const int getDay() const ;

    // Метод для строкового представления
    const std::string toString() const; 
};