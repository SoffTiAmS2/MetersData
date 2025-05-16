#include <QtTest/QtTest>
#include "core/model/Meters.h"
#include "core/model/Date.h"

class TestMeters : public QObject {
    Q_OBJECT
private slots:
    void testWaterMeterCreation();
    void testGasMeterCreation();
    void testElectricityMeterCreation();

    void testInvalidDateInMeter();
    void testNegativeValue();
};

void TestMeters::testWaterMeterCreation() {
    Date date(2023, 5, 15);
    WaterMeter hotWater(date, 123.45f, true);
    QCOMPARE(hotWater.isHotWater(), true);
    QCOMPARE(hotWater.getType(), std::string("Water"));
    QCOMPARE(hotWater.toString(), std::string("Water 2023.05.15 123.45 Hot"));

    WaterMeter coldWater(date, 98.76f, false);
    QCOMPARE(coldWater.isHotWater(), false);
    QCOMPARE(coldWater.getType(), std::string("Water"));
    QCOMPARE(coldWater.toString(), std::string("Water 2023.05.15 98.76 Cold"));
}

void TestMeters::testGasMeterCreation() {
    Date date(2022, 12, 31);
    GasMeter gas(date, 100.0f, "SN123456");
    QCOMPARE(gas.getSerialNumber(), std::string("SN123456"));
    QCOMPARE(gas.getType(), std::string("Gas"));
    QCOMPARE(gas.toString(), std::string("Gas 2022.12.31 100.00 SN123456"));
}

void TestMeters::testElectricityMeterCreation() {
    Date date(2024, 1, 1);
    ElectricityMeter meter(date, 200.0f, 220.0f);
    QCOMPARE(meter.getVoltage(), 220.0f);
    QCOMPARE(meter.getType(), std::string("Electricity"));
    QCOMPARE(meter.toString(), std::string("Electricity 2024.01.01 200.00 220.00"));
}

void TestMeters::testInvalidDateInMeter() {
    bool exceptionThrown = false;
    try {
        Date invalidDate(2023, 2, 30); // Некорректная дата
        WaterMeter meter(invalidDate, 100.0f, false);
    } catch (const std::invalid_argument&) {
        exceptionThrown = true;
    }
    QVERIFY(exceptionThrown);
}

void TestMeters::testNegativeValue() {
    Date date(2023, 5, 15);
    bool exceptionThrown = false;
    try {
        WaterMeter meter(date, -100.0f, false); // Отрицательное значение
    } catch (const std::invalid_argument&) {
        exceptionThrown = true;
    }
    QVERIFY(exceptionThrown);
}

QTEST_APPLESS_MAIN(TestMeters)
#include "test_meter.moc"