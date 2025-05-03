#include "models/Date.h"
#include <string>



class StringDateParser {
public:
    Date parse(const std::string& input) const;
};