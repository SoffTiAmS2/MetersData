// include/controllers/MeterController.h
#pragma once
#include "core/file/FileHandler.h"
#include "core/model/MeterList.h"
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