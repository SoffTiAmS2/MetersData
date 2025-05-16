#include <QtTest/QtTest>
#include "core/spliter/StringSplitter.h"

class TestStringSplitter : public QObject {
    Q_OBJECT
private slots:
    void testSplitting() {
        StringSplitter splitter;
        auto tokens = splitter.split("Water 2023.05.15 123.45 Hot");
        QCOMPARE(tokens.size(), 4);
        QCOMPARE(tokens[0], "Water");
        QCOMPARE(tokens[1], "2023.05.15");
        QCOMPARE(tokens[2], "123.45");
        QCOMPARE(tokens[3], "Hot");
    }

    void testMultipleSpaces() {
        StringSplitter splitter;
        auto tokens = splitter.split("Gas   2023.06.01   9.87   ABC123");
        QCOMPARE(tokens.size(), 4);
        QCOMPARE(tokens[0], "Gas");
        QCOMPARE(tokens[1], "2023.06.01");
        QCOMPARE(tokens[2], "9.87");
        QCOMPARE(tokens[3], "ABC123");
    }
};

QTEST_APPLESS_MAIN(TestStringSplitter)
#include "test_stringsplitter.moc"