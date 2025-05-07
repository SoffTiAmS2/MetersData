#pragma once

#include "core/model/MeterList.h"
#include <QTableWidget>

class MeterListView : public QTableWidget {
    Q_OBJECT

public:
    explicit MeterListView(QWidget* parent = nullptr);

    void updateView(const MeterList& meters);
    int selectedRow() const;

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    void setupStyle();

signals:
    void rowDeleted(int row); // ← Здесь объявляем сигнал
};