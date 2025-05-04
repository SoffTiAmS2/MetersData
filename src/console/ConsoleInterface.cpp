#include <iostream>
#include <string>
#include <memory>
#include "console/ConsoleInterface.h"
#include "meters/AbstractMeter.h"
#include "parsers/StringMeterParser.h"

void ConsoleInterface::printInstructions() const {
    std::cout << "=== Инструкция ===\n";
    std::cout << "Введите данные в формате:\n";
    std::cout << "  <Тип> <Дата> <Значение> <Параметр>\n";
    std::cout << "Примеры:\n";
    std::cout << "  вода 2023.10.05 150.75 горячая\n";
    std::cout << "  вода 2023.10.05 150.75 холодная\n";
    std::cout << "  газ  2024.01.01 78.6 SN-12345\n";
    std::cout << "  электричество 2024.05.15 321.0 220\n";
    std::cout << "Для выхода введите 'exit' или 'выход'.\n";
}

void ConsoleInterface::run() {
    printInstructions();

    parser = std::make_unique<StringMeterParser>();
    std::string input;

    while (true) {
        std::cout << "\nВведите данные: ";
        std::getline(std::cin, input);

        // Удаление ведущих/замыкающих пробелов (опционально)
        if (input.empty()) continue;

        if (input == "exit" || input == "выход") {
            std::cout << "Выход из программы.\n";
            break;
        }

        try {
            std::unique_ptr<AbstractMeter> meter = parser->parse(input);
            std::cout << "\n✅ Данные успешно распознаны:\n";
            std::cout << meter->toString() << '\n';
        } catch (const std::exception& e) {
            std::cerr << "❌ Ошибка: " << e.what() << "\n";
        }
    }
}
