#pragma once
#include <memory>
#include "controller/MeterController.h"
#include "view/ui/MeterListView.h"

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