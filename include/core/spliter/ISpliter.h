#pragma once

#include <string>
#include <vector>

class ISpliter{
public:
    virtual std::vector<std::string> split(const std::string& input) const = 0;
    virtual ~ISpliter() = default;
};