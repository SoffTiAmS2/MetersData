#include "view/ui/AddMeterDialog.h"
#include "ui_addmeterdialog.h"

#include "core/model/AbstractMeter.h"
#include "core/model/WaterMeter.h"
#include "core/model/ElectricityMeter.h"
#include "core/model/GasMeter.h"
#include "core/parser/DateParser.h"
#include "utils/Utils.h"

#include <QMessageBox>
#include <stdexcept>

AddMeterDialog::AddMeterDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddMeterDialog) {
    ui->setupUi(this);

    // Заполняем типы
    ui->typeComboBox->addItems({"Вода", "Электричество", "Газ"});

    connect(
        ui->typeComboBox, 
        &QComboBox::currentTextChanged, 
        this, 
        &AddMeterDialog::onTypeChanged
    );

    // Устанавливаем текущую дату по умолчанию
    ui->dateEdit->setDate(QDate::currentDate());
    ui->typeComboBox->setCurrentIndex(0);
    // Скрываем лишние поля
    hideAllExtraFields();
    ui->hotCheckBox->show();
    ui->hotCheckBoxLabel->show();
}

AddMeterDialog::~AddMeterDialog() {
    delete ui;
}

void AddMeterDialog::hideAllExtraFields() {
    ui->hotCheckBox->hide();
    ui->hotCheckBoxLabel->hide();
    ui->voltageLabel->hide();
    ui->voltageEdit->hide();
    ui->serialLabel->hide();
    ui->serialEdit->hide();
}

void AddMeterDialog::onTypeChanged(const QString& type) {
    hideAllExtraFields();

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
}

std::unique_ptr<AbstractMeter> AddMeterDialog::getMeter() const {
    try {
        QString type = ui->typeComboBox->currentText();
        Date date = DateParser().parse(
            ui->dateEdit->date().toString("yyyy.MM.dd").toUtf8().toStdString()
        );
        float value = static_cast<float>(ui->valueEdit->text().toFloat());

        if (type == "Вода") {
            bool isHot = ui->hotCheckBox->isChecked();
            return std::make_unique<WaterMeter>(date, value, isHot);
        } else if (type == "Электричество") {
            float voltage = static_cast<float>(ui->voltageEdit->text().toFloat());

            return std::make_unique<ElectricityMeter>(date, value, voltage);
        } else if (type == "Газ") {
            std::string serial = ui->serialEdit->text().toUtf8().toStdString();
            return std::make_unique<GasMeter>(date, value, serial);
        } else {
            throw std::invalid_argument(
                "Неизвестный тип счётчика: " + type.toUtf8().toStdString()
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