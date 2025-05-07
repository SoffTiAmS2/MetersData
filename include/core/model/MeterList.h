#pragma once

#include <vector>
#include <memory>
#include "core/model/Meters.h"


class MeterList {
public:
    void addMeter(std::unique_ptr<AbstractMeter> meter);
    void removeMeter(size_t index);
    void clear();

    const std::vector<std::unique_ptr<AbstractMeter>>& getMeters() const;
    int size() const;
    bool empty() const;

private:
    std::vector<std::unique_ptr<AbstractMeter>> meters;
};