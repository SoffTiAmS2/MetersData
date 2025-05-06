#include "view/console/ConsoleInterface.h"
#include <iostream>
#include <string>

void ConsoleInterface::printMenu() const {
    std::cout << "\n=== Консольный интерфейс ===\n";
    std::cout << "1. Загрузить из файла\n";
    std::cout << "2. Сохранить в файл\n";
    std::cout << "3. Показать все счетчики\n";
    std::cout << "4. Выход\n";
    std::cout << "Выберите действие: ";
}

void ConsoleInterface::displayMeters(const MeterList& meters) const {
    std::cout << "\n=== Счетчики ===\n";
    for (const auto& meter : meters.getMeters()) {
        std::cout << meter->toString() << "\n";
    }
}

ConsoleInterface::ConsoleInterface() {}

void ConsoleInterface::run() {
    int choice = 0;
    while (true) {
        printMenu();
        std::cin >> choice;
        std::cin.ignore(); // Очистка буфера после cin

        if (choice == 4) break;

        switch (choice) {
            case 1: {
                std::string path;
                std::cout << "Введите путь к файлу: ";
                std::getline(std::cin, path);
                try {
                    controller.loadFromFile(QString::fromStdString(path));
                    std::cout << "✅ Данные успешно загружены.\n";
                } catch (const std::exception& e) {
                    std::cerr << "❌ Ошибка загрузки: " << e.what() << "\n";
                }
                break;
            }

            case 2: {
                std::string path;
                std::cout << "Введите путь для сохранения: ";
                std::getline(std::cin, path);
                try {
                    controller.saveToFile(QString::fromStdString(path));
                    std::cout << "✅ Данные успешно сохранены.\n";
                } catch (const std::exception& e) {
                    std::cerr << "❌ Ошибка сохранения: " << e.what() << "\n";
                }
                break;
            }

            case 3: {
                const MeterList& meters = controller.getMeters();
                if (meters.empty()) {
                    std::cout << "Список пуст.\n";
                } else {
                    displayMeters(meters);
                }
                break;
            }

            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}