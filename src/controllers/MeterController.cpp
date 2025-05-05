// src/controllers/MeterController.cpp
#include "controllers/MeterController.h"
#include "file/FileHandler.h"
#include "meters/MeterList.h"
#include <QDebug>

MeterController::MeterController() {}

void MeterController::loadFromFile(const QString& path) {
    try {
        meters = fileHandler.loadFromFile(path);
    } catch (const std::exception& e) {
        throw;
    }
}

void MeterController::saveToFile(const QString& path) {
    try {
        fileHandler.saveToFile(path, meters);
    } catch (const std::exception& e) {
        throw;
    }
}

const MeterList& MeterController::getMeters() const {
    return meters;
}