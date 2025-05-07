#include "controller/MeterController.h"
#include <QDebug>

MeterController::MeterController() {}

void MeterController::loadFromFile(const QString& path) {
    try {
        fileHandler.load(path, meters);
    } catch (const std::exception& e) {
        throw;
    }
}

void MeterController::saveToFile(const QString& path) const {
    try {
        fileHandler.save(path, meters);
    } catch (const std::exception& e) {
        throw;
    }
}

void MeterController::addMeter(std::unique_ptr<AbstractMeter> meter) {
    if (!meter) return;
    meters.addMeter(std::move(meter));
}

void MeterController::removeMeter(size_t index) {
    if (index >= meters.size()) return;
    meters.removeMeter(index);
}

bool MeterController::empty() const {
    return meters.empty();
}

const MeterList& MeterController::getMeters() const {
    return meters;
}