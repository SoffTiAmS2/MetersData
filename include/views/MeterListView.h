#pragma once
#include "meters/MeterList.h"
#include <QTableWidget>

class MeterListView : public QTableWidget {
public:
    MeterListView(QWidget* parent = nullptr);
    void updateView(const MeterList& meters);
};