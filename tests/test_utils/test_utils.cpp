#include <QtTest/QtTest>
#include "utils/Utils.h"

class TestUtils : public QObject {
    Q_OBJECT

private slots:
    // --- Тест для isValidDateFormat ---
    void testValidDateFormat() {
        QVERIFY(Utils::isValidDateFormat("2023.05.15"));
        QVERIFY(Utils::isValidDateFormat("0001.01.01"));
        QVERIFY(Utils::isValidDateFormat("9999.12.31"));
        QVERIFY(Utils::isValidDateFormat("2023.5.15"));    // месяц без ведущего нуля
    }

    void testInvalidDateFormat() {
        QVERIFY(!Utils::isValidDateFormat("2023-05-15"));  // неверный разделитель
        QVERIFY(!Utils::isValidDateFormat("15.05.2023"));  // неверный порядок
        QVERIFY(!Utils::isValidDateFormat("2023.05"));     // недостаточно частей
        QVERIFY(!Utils::isValidDateFormat("abc.def.ghi")); // не цифры
    }

    // --- Тест для isValidDateValues ---
    void testValidDateValues() {
        QVERIFY(Utils::isValidDateValues(2020, 2, 29));  // високосный год
        QVERIFY(Utils::isValidDateValues(2023, 4, 30));   // 30 дней в апреле
        QVERIFY(Utils::isValidDateValues(2023, 1, 1));
    }

    void testInvalidDateValues() {
        QVERIFY(!Utils::isValidDateValues(0, 1, 1));      // нулевой год
        QVERIFY(!Utils::isValidDateValues(2023, 0, 1));   // нулевой месяц
        QVERIFY(!Utils::isValidDateValues(2023, 13, 1));  // месяц > 12
        QVERIFY(!Utils::isValidDateValues(2023, 2, 30));  // февраль
        QVERIFY(!Utils::isValidDateValues(2023, 4, 31));  // апрель
        QVERIFY(!Utils::isValidDateValues(2023, 6, 0));   // день = 0
    }

    // --- Тест для isValidValue ---
    void testValidValueFormat() {
        QVERIFY(Utils::isValidValue("123"));
        QVERIFY(Utils::isValidValue("123.45"));
        QVERIFY(Utils::isValidValue("+123.45"));
        QVERIFY(Utils::isValidValue("-123"));
        QVERIFY(Utils::isValidValue("123,45"));
        QVERIFY(Utils::isValidValue("0.00"));
    }

    void testInvalidValueFormat() {
        QVERIFY(!Utils::isValidValue("abc"));
        QVERIFY(!Utils::isValidValue("123.45.67"));  // несколько точек
        QVERIFY(!Utils::isValidValue(""));            // пустая строка
    }

    // --- Тест для normalizationString ---
    void testNormalizationString() {
        QCOMPARE(Utils::normalizationString("Hello"), std::string("hello"));
        QCOMPARE(Utils::normalizationString("WATER"), std::string("water"));
        QCOMPARE(Utils::normalizationString("фывапролджэЙЦУКЕНГШЩЗХЪasdfghjklZXCVBNM"), std::string("фывапролджэйцукенгшщзхъasdfghjklzxcvbnm"));
        QCOMPARE(Utils::normalizationString("MixedCASE"), std::string("mixedcase"));
        QCOMPARE(Utils::normalizationString("123ABC"), std::string("123abc"));
    }

    // --- Тест регулярных выражений ---
    void testDateRegex() {
        const std::regex& dateRx = Utils::dateRegex();
        QVERIFY(std::regex_match("2023.05.15", dateRx));
        QVERIFY(std::regex_match("0001.01.01", dateRx));
        QVERIFY(std::regex_match("9999.12.31", dateRx));
        QVERIFY(!std::regex_match("2023-05-15", dateRx));
        QVERIFY(!std::regex_match("15.05.2023", dateRx));
    }

    void testValueRegex() {
        const std::regex& valueRx = Utils::valueRegex();
        QVERIFY(std::regex_match("123", valueRx));
        QVERIFY(std::regex_match("123.45", valueRx));
        QVERIFY(std::regex_match("+123.45", valueRx));
        QVERIFY(std::regex_match("-123", valueRx));
        QVERIFY(!std::regex_match("abc", valueRx));
        QVERIFY(!std::regex_match("123.45.67", valueRx));
    }
};

QTEST_APPLESS_MAIN(TestUtils)
#include "test_utils.moc"