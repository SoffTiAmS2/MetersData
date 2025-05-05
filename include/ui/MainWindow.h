#pragma once
#include <QMainWindow>
#include "controllers/MeterController.h"
#include "views/MeterListView.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_addBtn_clicked();
    void on_loadBtn_clicked();
    void on_saveBtn_clicked();

private:
    Ui::MainWindow* ui;
    MeterListView* meterView;
    MeterController controller;
};