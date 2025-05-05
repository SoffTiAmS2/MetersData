#include "views/MeterListView.h"
#include "meters/AbstractMeter.h"
#include "meters/ElectricityMeter.h"
#include "meters/GasMeter.h"
#include "meters/WaterMeter.h"
#include <QTableWidgetItem>

MeterListView::MeterListView(QWidget* parent)
    : QTableWidget(parent) {
    setColumnCount(4);
    setHorizontalHeaderLabels(QStringList() << "Тип" << "Дата" << "Значение" << "Параметр");
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MeterListView::updateView(const MeterList& meters) {
    clearContents();
    setRowCount(0);

    for (const auto& meter : meters.getMeters()) {
        int row = rowCount();
        insertRow(row);

        QTableWidgetItem* typeItem = new QTableWidgetItem();
        QTableWidgetItem* dateItem = new QTableWidgetItem();
        QTableWidgetItem* valueItem = new QTableWidgetItem();
        QTableWidgetItem* paramItem = new QTableWidgetItem();

        typeItem->setText(QString::fromStdString(meter->toString().substr(0, 15)));
        dateItem->setText(QString::fromStdString(meter->getDate().toString()));
        valueItem->setText(QString::number(meter->getValue(), 'f', 2));
        const auto* waterMeter = dynamic_cast<const WaterMeter*>(meter.get());
        const auto* gasMeter = dynamic_cast<const GasMeter*>(meter.get());
        
        if (waterMeter) {
            paramItem->setText(waterMeter->isHotWater() ? QStringLiteral("Горячая") : QStringLiteral("Холодная"));
        } 
        else if (gasMeter) {
            paramItem->setText(QString::fromStdString(gasMeter->getSerialNumber()));
        } 
        else if (auto* electricityMeter = dynamic_cast<const ElectricityMeter*>(meter.get())) {
            Q_UNUSED(electricityMeter); // Если не используешь переменную дальше
            paramItem->setText(QStringLiteral("Напряжение"));
        }

        setItem(row, 0, typeItem);
        setItem(row, 1, dateItem);
        setItem(row, 2, valueItem);
        setItem(row, 3, paramItem);
    }

    resizeColumnsToContents();
}