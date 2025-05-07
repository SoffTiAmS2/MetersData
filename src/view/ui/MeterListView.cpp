// src/view/ui/MeterListView.cpp
#include "view/ui/MeterListView.h"
#include <QTableWidgetItem>
#include <QContextMenuEvent>
#include <QHeaderView>
#include <QMenu>

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

        typeItem->setText(QString::fromStdString(meter->getType()));
        dateItem->setText(QString::fromStdString(meter->getDate().toString()));
        valueItem->setText(QString::number(meter->getValue(), 'f', 2));

        const auto* waterMeter = dynamic_cast<const WaterMeter*>(meter.get());
        const auto* gasMeter = dynamic_cast<const GasMeter*>(meter.get());

        if (waterMeter) {
            paramItem->setText(
                waterMeter->isHotWater() ? 
                QStringLiteral("Горячая") : 
                QStringLiteral("Холодная")
            );
        } 
        else if (gasMeter) {
            paramItem->setText(
                QString::fromStdString(gasMeter->getSerialNumber())
            );
        } 
        else if (auto* electricityMeter = dynamic_cast<const ElectricityMeter*>(meter.get())) {
            Q_UNUSED(electricityMeter);
            paramItem->setText(QString::number(meter->getValue(), 'f', 2));
        }

        setItem(row, 0, typeItem);
        setItem(row, 1, dateItem);
        setItem(row, 2, valueItem);
        setItem(row, 3, paramItem);
    }

    resizeColumnsToContents();
}

MeterListView::MeterListView(QWidget* parent)
    : QTableWidget(parent) {

    setColumnCount(4);
    
    QStringList headers;
    headers << "Тип" << "Дата" << "Значение" << "Параметр";
    
    setHorizontalHeaderLabels(headers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setAlternatingRowColors(true);
    horizontalHeader()->setStretchLastSection(true);
}

int MeterListView::selectedRow() const {
    QModelIndexList selected = selectedIndexes();

    return selected.isEmpty() ? -1 : selected.first().row();
}

void MeterListView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        QModelIndex index = indexAt(event->pos());

        if (index.isValid()) {
            int currentRow = selectedRow();

            if (currentRow == index.row()) {
                clearSelection();
            } else {
                selectRow(index.row());
            }
        } else {
            clearSelection();
        }
    }

    QTableWidget::mousePressEvent(event);
}

void MeterListView::contextMenuEvent(QContextMenuEvent* event) {
    QModelIndex index = indexAt(event->pos());

    if (!index.isValid()) return;

    selectRow(index.row());

    QMenu contextMenu(tr("Контекстное меню"), this);
    QAction* deleteAction = contextMenu.addAction("Удалить");

    QAction* selectedAction = contextMenu.exec(mapToGlobal(event->pos()));

    if (selectedAction == deleteAction) {
        emit rowDeleted(selectedRow());
    }
}
