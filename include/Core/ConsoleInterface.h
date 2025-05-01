#pragma once

#include <memory>
#include "interfaces/IMeterParser.h"

class ConsoleInterface {
private:
    // Указатель на парсер
    std::unique_ptr<IMeterParser> parser;

    // Вывод инструкций
    void printInstructions() const;

public:
    // Реализация метода интерфейса
    void run();
};