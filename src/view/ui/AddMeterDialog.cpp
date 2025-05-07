#include "view/ui/AddMeterDialog.h"
#include "ui_addmeterdialog.h"

#include "core/model/AbstractMeter.h"
#include "core/model/WaterMeter.h"
#include "core/model/ElectricityMeter.h"
#include "core/model/GasMeter.h"
#include "core/parser/DateParser.h"
#include "core/parsUtils/ValueParser.h"
#include <QMessageBox>
#include <QDoubleValidator>
#include <stdexcept>

AddMeterDialog::AddMeterDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddMeterDialog) {
    ui->setupUi(this);

    // Инициализация выпадающего списка типов
    ui->typeComboBox->addItems({"Вода", "Электричество", "Газ"});
    connect(ui->typeComboBox, 
        &QComboBox::currentTextChanged, 
        this, 
        &AddMeterDialog::onTypeChanged
    );

    // Устанавливаем текущую дату по умолчанию
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setDisplayFormat("yyyy.MM.dd");  // Точный формат даты

    // Валидатор для значения (только float)
    ui->valueEdit->setValidator(
        new QDoubleValidator(
        0.0, 
        999999.99, 
        2, 
        this
        )
    );

    // Валидатор для напряжения
    ui->voltageEdit->setValidator(
        new QDoubleValidator(
            0.0, 
            999999.99, 
            2, 
            this
        )
    );

}

AddMeterDialog::~AddMeterDialog() {
    delete ui;
}

std::unique_ptr<AbstractMeter> AddMeterDialog::getMeter() const {
    if (!validateInput()) {
        return nullptr;
    }

    try {
        QString type = ui->typeComboBox->currentText();
        Date date = DateParser().parse(
            ui->dateEdit->date().toString("yyyy.MM.dd").toStdString()
        );
        float value = ValueParser().parse(
            ui->valueEdit->text().toUtf8().toStdString()
        );
        if (type == "Вода") {
            bool isHot = ui->hotCheckBox->isChecked();
            return std::make_unique<WaterMeter>(date, value, isHot);
        } else if (type == "Электричество") {
            float voltage = ValueParser().parse(
                ui->voltageEdit->text().toUtf8().toStdString()
            );
            return std::make_unique<ElectricityMeter>(date, value, voltage);
        } else if (type == "Газ") {
            std::string serial = ui->serialEdit->text().toStdString();
            return std::make_unique<GasMeter>(date, value, serial);
        } else {
            throw std::invalid_argument(
                "Неизвестный тип счётчика: " + type.toStdString()
            );
        }

    } catch (const std::exception& e) {
        QMessageBox::critical(
            nullptr, 
            tr("Ошибка"), 
            QString::fromStdString(e.what())
        );
        return nullptr;
    }
}

void AddMeterDialog::hideAllExtraFields() {
    // Скрываем всё
    ui->hotCheckBox->hide();
    ui->hotCheckBoxLabel->hide();

    ui->voltageLabel->hide();
    ui->voltageEdit->hide();

    ui->serialLabel->hide();
    ui->serialEdit->hide();
}

void AddMeterDialog::onTypeChanged(const QString& type) {
    hideAllExtraFields();

    // Показываем нужные поля
    if (type == "Вода") {
        ui->hotCheckBox->show();
        ui->hotCheckBoxLabel->show();
    } else if (type == "Электричество") {
        ui->voltageLabel->show();
        ui->voltageEdit->show();
    } else if (type == "Газ") {
        ui->serialLabel->show();
        ui->serialEdit->show();
    }

    // Очистка полей при смене типа
    ui->valueEdit->clear();
    ui->voltageEdit->clear();
    ui->serialEdit->clear();
}

bool AddMeterDialog::validateInput() const {
    // Проверяем значение
    bool ok;
    float value = ValueParser().parse(
        ui->valueEdit->text().toUtf8().toStdString()
    );
    if (value < 0) {
        QMessageBox::warning(
            nullptr, 
            tr("Ошибка"), 
            tr("Значение должно быть положительным числом")
        );
        return false;
    }

    QString type = ui->typeComboBox->currentText();

    // Проверяем напряжение, если выбрано электричество
    if (type == "Электричество") {
        float voltage = ValueParser().parse(
            ui->voltageEdit->text().toUtf8().toStdString()
        );
        if (voltage < 0) {
            QMessageBox::warning(
                nullptr, 
                tr("Ошибка"), 
                tr("Напряжение должно быть положительным числом")
            );
            return false;
        }
    }

    // Проверяем серийный номер, если выбран газ
    if (type == "Газ" && ui->serialEdit->text().isEmpty()) {
        QMessageBox::warning(
            nullptr, 
            tr("Ошибка"), 
            tr("Введите серийный номер")
        );
        return false;
    }

    return true;
}