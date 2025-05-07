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
            paramItem->setText(waterMeter->isHotWater() ? QStringLiteral("Горячая") : QStringLiteral("Холодная"));
        } 
        else if (gasMeter) {
            paramItem->setText(QString::fromStdString(gasMeter->getSerialNumber()));
        } 
        else if (auto* electricityMeter = dynamic_cast<const ElectricityMeter*>(meter.get())) {
            Q_UNUSED(electricityMeter);
            paramItem->setText(QStringLiteral("Напряжение"));
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

    // Отключаем обычное выделение (по ЛКМ)
    setSelectionMode(QAbstractItemView::NoSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setAlternatingRowColors(true);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setStretchLastSection(true);
    // setContextMenuPolicy(Qt::CustomContextMenu); // Включаем поддержку контекстного меню
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
                clearSelection(); // Снимаем выделение при повторном нажатии
            } else {
                selectRow(index.row()); // Выделяем новую строку
            }
        } else {
            clearSelection(); // Если клик вне таблицы — убираем всё выделение
        }
    }

    QTableWidget::mousePressEvent(event); // Передаём событие дальше
}

void MeterListView::contextMenuEvent(QContextMenuEvent* event) {
    // Получаем индекс под курсором
    QModelIndex index = indexAt(event->pos());

    // Если индекс невалиден — выходим
    if (!index.isValid()) return;

    // Программно выделяем строку
    selectRow(index.row());

    // Создаём контекстное меню
    QMenu contextMenu(tr("Контекстное меню"), this);
    QAction* deleteAction = contextMenu.addAction("Удалить");

    // Отображаем меню в точке клика
    QAction* selectedAction = contextMenu.exec(mapToGlobal(event->pos()));

    if (selectedAction == deleteAction) {
        emit rowDeleted(selectedRow());
    }
}
