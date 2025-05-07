#include "view/ui/AddMeterDialog.h"
#include "core/factory/MeterFactory.h"
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
#include <string>

AddMeterDialog::AddMeterDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddMeterDialog) {
    ui->setupUi(this);

    // Инициализация выпадающего списка типов
    ui->typeComboBox->addItems({"water", "electricity", "gas"});

    connect(ui->typeComboBox, 
        &QComboBox::currentTextChanged, 
        this, 
        &AddMeterDialog::onTypeChanged
    );

    // Устанавливаем текущую дату по умолчанию
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setDisplayFormat("yyyy.MM.dd");  // Точный формат даты

    // Валидатор для значения
    ui->valueEdit->setValidator(
        new QDoubleValidator(0.0, 999999.99, 2, this)
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

    ui->typeComboBox->setCurrentIndex(0);

    hideAllExtraFields();
    ui->hotCheckBox->show();
    ui->hotCheckBoxLabel->show();
}

AddMeterDialog::~AddMeterDialog() {
    delete ui;
}

std::unique_ptr<AbstractMeter> AddMeterDialog::getMeter() const {
    try {
        std::string type = ui->typeComboBox->currentText().toUtf8().toStdString();
        Date date = DateParser().parse(
            ui->dateEdit->date().toString("yyyy.MM.dd").toUtf8().toStdString()
        );

        float value = ValueParser().parse(
            ui->valueEdit->text().toUtf8().toStdString()
        );

        std::string paramStr;
        if (type == "water") {
            bool isHot = ui->hotCheckBox->isChecked();

            paramStr = isHot ? "Hot" : "Cold";
        } else if (type == "electricity") {
            paramStr = ui->voltageEdit->text().toUtf8().toStdString();
        }
        else if (type == "gas") {
            paramStr = ui->serialEdit->text().toUtf8().toStdString();
        }
        else {
            throw std::invalid_argument(
                "Неизвестный тип счётчика: " + type
            );
        }

        return MeterFactory().createMeter(type, date, value, paramStr);
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
    if (type == "water") {
        ui->hotCheckBox->show();
        ui->hotCheckBoxLabel->show();
    } 
    else if (type == "electricity") {
        ui->voltageLabel->show();
        ui->voltageEdit->show();
    } 
    else if (type == "gas") {
        ui->serialLabel->show();
        ui->serialEdit->show();
    }
}