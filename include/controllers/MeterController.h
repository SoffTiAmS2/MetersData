// include/controllers/MeterController.h
#pragma once
#include "meters/MeterList.h"
#include "file/FileHandler.h"
#include <QString>

class MeterController {
public:
    MeterController();
    void loadFromFile(const QString& path);
    void saveToFile(const QString& path);
    const MeterList& getMeters() const;
    
private:
    MeterList meters;
    FileHandler fileHandler;
};