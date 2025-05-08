#include "core/factory/MeterFactory.h"
#include "core/model/AbstractMeter.h"
#include "core/model/ElectricityMeter.h"
#include "core/model/WaterMeter.h"
#include "core/model/GasMeter.h"
#include "core/parser/ValueParser.h"
#include "utils/Utils.h"


std::unique_ptr<AbstractMeter> MeterFactory::createMeter (
    const std::string& type,
    const Date& date,
    float value,
    const std::string& param
) const {
    if (type == "electricity" or type == "электричество") {

        ValueParser valueParser;
        float voltage = valueParser.parse(param);

        return std::make_unique<ElectricityMeter>(date, value, voltage);
    }

    else if (type == "water" or type == "вода") {

        std::string normalesParam = Utils::normalizationString(param);

        if (normalesParam != "hot" && normalesParam != "cold") {
            throw std::invalid_argument(
                "Счетчик воды: ожидается 'hot' или 'cold'."
            );
        }

        bool isHot = (normalesParam == "hot");

        return std::make_unique<WaterMeter>(date, value, isHot);
    }

    else if (type == "gas" or type == "газ") {

        if (param.empty()) {

            throw std::invalid_argument(
                "Счетчик газа: требуется непустой серийный номер."
            );
        }

        return std::make_unique<GasMeter>(date, value, param);
    }

    else {
        
        throw std::invalid_argument("Неизвестный тип счётчика: " + type);
    }
}