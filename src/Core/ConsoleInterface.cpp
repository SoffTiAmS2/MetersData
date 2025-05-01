#include <iostream>
#include <string>
#include "Data/Meter.h"
#include "Core/ConsoleInterface.h"
#include "Parsers/StringMeterParser.h"

void ConsoleInterface::printInstructions() const {
    std::cout << "Введите данные в формате: 'Тип Дата Значение'\n";
    std::cout << "Пример: \"Вода 4 этаж\" 2023.10.05 150.75\n";
    std::cout << "Для выхода введите 'exit' или 'выход'.\n";
}

void ConsoleInterface::run() {
    printInstructions();
    parser = std::make_unique<StringMeterParser>();
    std::string input;
    while (true) {
        std::cout << "\nВведите данные: ";
        std::getline(std::cin, input);

        if (input == "exit" or input == "выход") {
            std::cout << "Выход из программы.\n";
            break;
        }

        try {
            Meter meter = parser->parse(input);
            std::cout << "Данные успешно распарсены:\n";
            std::cout << "Тип: " << meter.getType() << "\n";
            std::cout << "Дата: " << meter.getDate().toString() << "\n";
            std::cout << "Значение: " << meter.getValue() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    }
}