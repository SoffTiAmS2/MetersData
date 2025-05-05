#pragma once
#include "parsUtils/ISpliter.h"
#include <string>
#include <vector>

class CsvSplitter : public ISpliter{
public:
    std::vector<std::string> split(const std::string& input) const override;
};