#include <QtTest/QtTest>
#include "core/model/Date.h"

class TestDate : public QObject {
    Q_OBJECT

private slots:
    void testValidCreation();
    void testInvalidCreation_year();
    void testInvalidCreation_monthOutOfRange();
    void testInvalidCreation_invalidDay();
    void testGetters();
    void testToString();
};

void TestDate::testValidCreation() {
    Date date(2024, 5, 1);
    QCOMPARE(date.getYear(), 2024);
    QCOMPARE(date.getMonth(), 5);
    QCOMPARE(date.getDay(), 1);
}

void TestDate::testInvalidCreation_year() {
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, Date(0, 5, 1));
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, Date(-1, 5, 1));
}

void TestDate::testInvalidCreation_monthOutOfRange() {
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, Date(2024, 0, 1));
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, Date(2024, 13, 1));
}

void TestDate::testInvalidCreation_invalidDay() {
    // Февраль не может быть 30
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, Date(2024, 2, 30));

    // Апрель не может быть 31
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, Date(2023, 4, 31));

    // День меньше 1
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument, Date(2024, 5, 0));
}

void TestDate::testGetters() {
    Date date(2023, 12, 31);
    QCOMPARE(date.getYear(), 2023);
    QCOMPARE(date.getMonth(), 12);
    QCOMPARE(date.getDay(), 31);
}

void TestDate::testToString() {
    Date date1(2024, 1, 1);
    QCOMPARE(date1.toString(), std::string("2024.01.01"));

    Date date2(2023, 12, 31);
    QCOMPARE(date2.toString(), std::string("2023.12.31"));

    Date date3(2020, 2, 29); // Високосный
    QCOMPARE(date3.toString(), std::string("2020.02.29"));
}

QTEST_APPLESS_MAIN(TestDate)
#include "test_date.moc"