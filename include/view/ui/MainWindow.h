#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QFileDialog>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QCloseEvent>
#include <QMessageBox>

#include "controller/MeterController.h"
#include "view/ui/MeterListView.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void addObjectActions();
    
    void onDeleteSelectedRow();

    void loadFileActions();
    void saveFileActions();
    void saveCurrentFileActions();
    
    

private:
    Ui::MainWindow* ui;
    MeterController controller;
    std::unique_ptr<MeterListView> meterView;

    QString currentFilePath;
    bool isModified;

    void setupUi();
    void connectSignalsAndSlots();
    void updateWindowTitle();

    void loadFromFile(const QString& path);
    void saveToFile(const QString& path = "");

    void closeEvent(QCloseEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
};