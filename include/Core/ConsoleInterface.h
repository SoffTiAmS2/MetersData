#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "interfaces/IMeterParser.h"
#include "Data/Meter.h"

class ConsoleInterface {
private:
    std::unique_ptr<IMeterParser> parser;

    // Вывод инструкций
    void printInstructions() const;

public:
    // Реализация метода интерфейса
    void run();
};