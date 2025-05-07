// src/meters/MeterList.cpp
#include "core/model/MeterList.h"

void MeterList::addMeter(std::unique_ptr<AbstractMeter> meter) {
    meters.push_back(std::move(meter));
}

void MeterList::removeMeter(size_t index) {
    if (index < meters.size()) {
        
        meters.erase(meters.begin() + index);
    }
}

void MeterList::clear() {
    meters.clear();
}

const std::vector<std::unique_ptr<AbstractMeter>>& MeterList::getMeters() const {
    return meters;
}

int MeterList::size() const {
    return meters.size();
}

bool MeterList::empty() const {
    return meters.empty();
}