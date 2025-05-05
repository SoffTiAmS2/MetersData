#include "ui/MainWindow.h"
#include "ui_mainwindow.h"
#include "views/MeterListView.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), meterView(new MeterListView()) {
    ui->setupUi(this);  // ← Автоматическая настройка UI


    
    connect(ui->addBtn, &QPushButton::clicked, this, &MainWindow::on_addBtn_clicked);
    connect(ui->loadBtn, &QPushButton::clicked, this, &MainWindow::on_loadBtn_clicked);
    connect(ui->saveBtn, &QPushButton::clicked, this, &MainWindow::on_saveBtn_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
    delete meterView;
}

void MainWindow::on_addBtn_clicked() {
    QMessageBox::information(this, "Информация", "Функция 'Добавить' пока не реализована.");
}

void MainWindow::on_loadBtn_clicked() {
    QString path = QFileDialog::getOpenFileName(
        this,
        "Открыть файл",
        "",
        "Текстовые файлы (*.txt *.csv)"
    );

    if (!path.isEmpty()) {
        try {
            controller.loadFromFile(path);
            meterView->updateView(controller.getMeters());
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Ошибка", QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::on_saveBtn_clicked() {
    QString path = QFileDialog::getSaveFileName(
        this,
        "Сохранить файл",
        "",
        "Текстовые файлы (*.txt *.csv)"
    );

    if (!path.isEmpty()) {
        try {
            controller.saveToFile(path);
            QMessageBox::information(this, "Успех", "Данные успешно сохранены.");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Ошибка", QString::fromStdString(e.what()));
        }
    }
}