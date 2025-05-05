#pragma once
#include <memory>
#include "controllers/MeterController.h"
#include "views/MeterListView.h"

class ConsoleInterface {
private:
    MeterController controller;
    MeterListView listView;

    void printMenu() const;
    void displayMeters(const MeterList& meters) const;

public:
    ConsoleInterface();
    void run();
};