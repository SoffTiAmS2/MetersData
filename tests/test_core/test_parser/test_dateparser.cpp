#include <QtTest/QtTest>
#include "core/parser/DateParser.h"

class TestDateParser : public QObject {
    Q_OBJECT

private slots:
    void testValidDateParsing() {
        DateParser parser;
        Date date = parser.parse("2023.05.15");
        QCOMPARE(date.getYear(), 2023);
        QCOMPARE(date.getMonth(), 5);
        QCOMPARE(date.getDay(), 15);
    }

    void testInvalidDateFormat() {
        DateParser parser;
        QVERIFY_THROWS_EXCEPTION(std::invalid_argument, parser.parse("2023-05-15"));
        QVERIFY_THROWS_EXCEPTION(std::invalid_argument, parser.parse("15.05.2023"));
    }

    void testInvalidDateValues() {
        DateParser parser;
        QVERIFY_THROWS_EXCEPTION(std::invalid_argument, parser.parse("2023.13.01"));
        QVERIFY_THROWS_EXCEPTION(std::invalid_argument, parser.parse("2023.02.30"));
    }
};

QTEST_APPLESS_MAIN(TestDateParser)
