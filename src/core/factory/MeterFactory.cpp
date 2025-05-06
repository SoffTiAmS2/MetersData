#include "core/factory/MeterFactory.h"
#include "core/model/AbstractMeter.h"
#include "core/model/ElectricityMeter.h"
#include "core/model/WaterMeter.h"
#include "core/model/GasMeter.h"
#include "core/parsUtils/ValueParser.h"


std::unique_ptr<AbstractMeter> MeterFactory::createMeter(
    const std::string& type,
    const Date& date,
    float value,
    const std::string& param) {
        if (type == "electricity" or type == "электричество") {

            ValueParser valueParser;
            float voltage = valueParser.parse(param);
            return std::make_unique<ElectricityMeter>(date, value, voltage);
        }
        else if (type == "water" or type == "вода") {
            if ((param != "hot" && param != "cold") && 
                (param != "горячая" && param != "холодная")) {
                throw std::invalid_argument("Счетчик воды: ожидается 'горячая' или 'холодная'.");
            }

            bool isHot = (param == "hot");

            return std::make_unique<WaterMeter>(date, value, isHot);
        }
        else if (type == "gas" or type == "газ") {
            if (param.empty()) {
                throw std::invalid_argument("Счетчик газа: требуется непустой серийный номер.");
            }

            return std::make_unique<GasMeter>(date, value, param);
        }
        else {
            throw std::invalid_argument("Неизвестный тип счётчика: " + type);
        }

}