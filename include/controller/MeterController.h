#pragma once

#include "core/model/MeterList.h"
#include "core/file/FileHandler.h"
#include <QString>


class MeterController {
public:
    MeterController();

    void loadFromFile(const QString& path);
    void saveToFile(const QString& path) const;
    void addMeter(std::unique_ptr<AbstractMeter> meter);
    void removeMeter(size_t index);
    const MeterList& getMeters() const;
    bool empty() const;

private:
    MeterList meters;
    FileHandler fileHandler;
};