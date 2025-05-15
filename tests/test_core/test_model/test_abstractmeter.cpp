#include <QtTest/QtTest>
#include "core/model/AbstractMeter.h"
#include "core/model/Meters.h"

class TestAbstractMeter : public QObject {
    Q_OBJECT

private slots:
    void testConstructor();
    void testGetters();
    void testToString();
    void testInvalidDate();
    void testInvalidValue();
};

void TestAbstractMeter::testConstructor() {
    Date date(2024, 5, 1);
    AbstractMeter* meter = new WaterMeter(date, 100.0f, false);

    QVERIFY(meter != nullptr);
}

void TestAbstractMeter::testGetters() {
    Date date(2024, 5, 1);
    WaterMeter meter(date, 100.0f, false);

    QCOMPARE(meter.getDate(), date);
    QCOMPARE(meter.getValue(), 100.0f);
    QCOMPARE(meter.getType(), std::string("Water"));
}

void TestAbstractMeter::testToString() {
    Date date(2024, 5, 1);
    WaterMeter meter(date, 100.0f, false);

    QString expected = "Water 2024.05.01 100.00 Cold";
    QCOMPARE(QString::fromStdString(meter.toString()), expected);
}

void TestAbstractMeter::testInvalidDate() {
    bool exceptionThrown = false;
    try {
        Date invalidDate(2024, 2, 30); // Некорректная дата (Февраль имеет максимум 29 дней)
        WaterMeter meter(invalidDate, 100.0f, false);
    } catch (const std::invalid_argument& e) {
        exceptionThrown = true;
    }

    QVERIFY(exceptionThrown);
}

void TestAbstractMeter::testInvalidValue() {
    Date date(2024, 5, 1);
    bool exceptionThrown = false;

    try {
        WaterMeter meter(date, -100.0f, false); // Отрицательное значение
    } catch (const std::invalid_argument& e) {
        exceptionThrown = true;
    }

    QVERIFY(exceptionThrown);
}

QTEST_APPLESS_MAIN(TestAbstractMeter)
#include "test_abstractmeter.moc"