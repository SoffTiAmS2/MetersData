#include <QtTest/QtTest>
#include "core/model/MeterList.h"
#include "core/model/Meters.h"
#include "core/model/Date.h"

class TestMeterList : public QObject {
    Q_OBJECT

private slots:
    void testEmptyInitially();
    void testAddMeter();
    void testRemoveMeter();
    void testClear();
    void testSize();
    void testGetMeters();
};

void TestMeterList::testEmptyInitially() {
    MeterList list;
    QVERIFY(list.empty());
    QCOMPARE(list.size(), 0);
}

void TestMeterList::testAddMeter() {
    MeterList list;
    Date date(2023, 5, 15);

    auto water = std::make_unique<WaterMeter>(date, 123.45f, true);
    auto gas = std::make_unique<GasMeter>(date, 98.76f, "SN123456");
    auto electricity = std::make_unique<ElectricityMeter>(date, 50.0f, 220.0f);

    list.addMeter(std::move(water));
    list.addMeter(std::move(gas));
    list.addMeter(std::move(electricity));

    QCOMPARE(list.size(), 3);
    QVERIFY(!list.empty());

    const auto& meters = list.getMeters();
    QCOMPARE(meters[0]->getType(), std::string("Water"));
    QCOMPARE(meters[1]->getType(), std::string("Gas"));
    QCOMPARE(meters[2]->getType(), std::string("Electricity"));
}

void TestMeterList::testRemoveMeter() {
    MeterList list;
    Date date(2023, 5, 15);

    list.addMeter(std::make_unique<WaterMeter>(date, 123.45f, true));
    list.addMeter(std::make_unique<GasMeter>(date, 98.76f, "SN123456"));

    list.removeMeter(0); // Удаляем первый элемент
    QCOMPARE(list.size(), 1);
    QCOMPARE(list.getMeters()[0]->getType(), std::string("Gas"));

    list.removeMeter(0); // Удаляем последний
    QVERIFY(list.empty());
}

void TestMeterList::testClear() {
    MeterList list;
    Date date(2023, 5, 15);

    list.addMeter(std::make_unique<WaterMeter>(date, 123.45f, true));
    list.addMeter(std::make_unique<GasMeter>(date, 98.76f, "SN123456"));
    list.addMeter(std::make_unique<ElectricityMeter>(date, 50.0f, 220.0f));

    list.clear();

    QVERIFY(list.empty());
    QCOMPARE(list.size(), 0);
}

void TestMeterList::testSize() {
    MeterList list;
    Date date(2023, 5, 15);

    QCOMPARE(list.size(), 0);

    list.addMeter(std::make_unique<WaterMeter>(date, 123.45f, true));
    QCOMPARE(list.size(), 1);

    list.addMeter(std::make_unique<GasMeter>(date, 98.76f, "SN123456"));
    QCOMPARE(list.size(), 2);

    list.removeMeter(0);
    QCOMPARE(list.size(), 1);

    list.clear();
    QCOMPARE(list.size(), 0);
}

void TestMeterList::testGetMeters() {
    MeterList list;
    Date date(2023, 5, 15);

    list.addMeter(std::make_unique<WaterMeter>(date, 123.45f, true));
    list.addMeter(std::make_unique<GasMeter>(date, 98.76f, "SN123456"));

    const auto& meters = list.getMeters();
    QVERIFY(meters.size() == 2);
    QCOMPARE(meters[0]->getType(), std::string("Water"));
    QCOMPARE(meters[1]->getType(), std::string("Gas"));
}

QTEST_APPLESS_MAIN(TestMeterList)
#include "test_meterlist.moc"