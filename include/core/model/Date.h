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
    int getYear() const;
    int getMonth() const;
    int getDay() const ;

    // Метод для строкового представления
    std::string toString() const; 
};