#include "view/ui/MainWindow.h"
#include "controller/MeterController.h"
#include "ui_mainwindow.h"
#include "utils/Logger.h"
#include "view/ui/AddMeterDialog.h"
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QDebug>
#include <QShortcut>
#include <QContextMenuEvent>
#include <string>
#include <QProcess>




MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), isModified(false) {

    setupUi();
    connectSignalsAndSlots();
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::addObjectActions() {
    AddMeterDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        auto meter = dialog.getMeter();
        if (meter) {
            controller.addMeter(std::move(meter));
            meterView->updateView(controller.getMeters());
            isModified = true;
            updateWindowTitle();
        }
    }
}


void MainWindow::onDeleteSelectedRow() {
    int index = meterView->selectedRow();
    if (index >= 0 && index < controller.getMeters().size()) {

        controller.removeMeter(index);
        
        meterView->updateView(controller.getMeters());
        
        isModified = true;
        
        updateWindowTitle();
    }
}


void MainWindow::loadFileActions() {
    QString projectRoot = QCoreApplication::applicationDirPath();

    QString filePath = getOpenFileName();

    loadFromFile(filePath);
}


void MainWindow::saveFileActions() {
    saveToFile();  // Сохранение с выбором пути
}


void MainWindow::saveCurrentFileActions() {
    if (currentFilePath.isEmpty()) {
        saveToFile();
    } else {
        saveToFile(currentFilePath);
    }
}


void MainWindow::setupUi() {
    ui->setupUi(this);

    meterView = std::make_unique<MeterListView>(ui->meterTableView->parentWidget());
    meterView->setSelectionMode(QAbstractItemView::SingleSelection);
    meterView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->meterTableView->setWidget(meterView.get());
    ui->meterTableView->setWidgetResizable(true);

    updateWindowTitle();
}


void MainWindow::updateWindowTitle() {
    QString title = "Приложение для учёта счётчиков";

    if (!currentFilePath.isEmpty()) {
        title += " - " + currentFilePath;
    }
    if (isModified) {
        title += " *";
    }

    setWindowTitle(title);
}


void MainWindow::loadFromFile(const QString& path) {

    if (path.isEmpty()) {
        return;
    }

    try{
        controller.loadFromFile(path);

        currentFilePath = path;
        isModified = false;

        meterView->updateView(controller.getMeters());

        updateWindowTitle();
    }
    catch (const std::exception& e) {
        std::string message = "Не удалось загрузить файл: ";
        QMessageBox::critical(
            this,
            tr("Ошибка загрузки"),
            QString::fromStdString(message + e.what())
        );
        Logger::instance().log(message + e.what());
    } 
    catch (...) {
        std::string message = "Произошла неожиданная ошибка при загрузки файла.";
        QMessageBox::critical(
            this,
            tr("Неизвестная ошибка"),
            QString::fromStdString(message)
        );
        Logger::instance().log(message);
    }
}



void MainWindow::saveToFile(const QString& path) {
    QString selectedPath = path;

    if (selectedPath.isEmpty()) {

        selectedPath = getSaveFileName();
    }

    if (selectedPath.isEmpty()) {
        return;
    }

    try{
        controller.saveToFile(selectedPath);

        currentFilePath = selectedPath;
        isModified = false;

        updateWindowTitle();
    }
    catch (const std::exception& e) {
        std::string message = "Не удалось сохранить файл: ";
        QMessageBox::critical(
            this,
            tr("Ошибка сохранения"),
            QString::fromStdString(message + e.what())
        );
        Logger::instance().log(message + e.what());
    } 
    catch (...) {
        std::string message = "Произошла неожиданная ошибка при сохранение файла.";
        QMessageBox::critical(
            this,
            tr("Неизвестная ошибка"),
            QString::fromStdString(message)
        );
        Logger::instance().log(message);
    }

}


void MainWindow::closeEvent(QCloseEvent* event) {
    if (isModified and !controller.empty()) {
        QMessageBox::StandardButton btn;

        btn = QMessageBox::question(
            this,
            tr("Выйти"),
            tr("Вы хотите сохранить изменения перед выходом?"),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
        );

        if (btn == QMessageBox::Yes) {

            saveToFile();
            
            event->accept();
        } 
        else if (btn == QMessageBox::No) {
            event->accept();
        }
        else {
            event->ignore();
        }
    } 
    else {
        event->accept();
    }
}


void MainWindow::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent* event) {
    const QList<QUrl> urls = event->mimeData()->urls();

    if (!urls.isEmpty()) {
        QString filePath = urls.first().toLocalFile();

        loadFromFile(filePath);
    }
}

QString MainWindow::getOpenFileName() {
    QProcess process;
    process.start("osascript", QStringList()
        << "-e" << "POSIX path of (choose file with prompt \"Выберите файл\")");
    process.waitForFinished();
    QString path = process.readAllStandardOutput().trimmed();
    return path;
}


QString MainWindow::getSaveFileName() {
    QProcess process;
    process.start("osascript", QStringList()
        << "-e" << "POSIX path of (choose file name with prompt \"Сохранить файл как\")");
    process.waitForFinished();
    QString path = process.readAllStandardOutput().trimmed();
    if (!path.endsWith(".txt") && !path.endsWith(".csv")) {
        path += ".txt"; // по умолчанию
    }
    return path;
}


void MainWindow::connectSignalsAndSlots() {
    connect(ui->addBtn, &QPushButton::clicked, this, &MainWindow::addObjectActions);
    connect(ui->loadBtn, &QPushButton::clicked, this, &MainWindow::loadFileActions);

    connect(ui->action, &QAction::triggered, this, &MainWindow::saveFileActions);
    connect(ui->action_2, &QAction::triggered, this, &MainWindow::saveCurrentFileActions);

    // Горячие клавиши
    QShortcut* addShortcut = new QShortcut(QKeySequence(Qt::MetaModifier | Qt::Key_N), this);
    connect(addShortcut, &QShortcut::activated, this, &MainWindow::addObjectActions);

    QShortcut* saveShortcut = new QShortcut(QKeySequence(Qt::MetaModifier | Qt::Key_S), this);
    connect(saveShortcut, &QShortcut::activated, this, &MainWindow::saveCurrentFileActions);

    QShortcut* saveAsShortcut = new QShortcut(QKeySequence(Qt::MetaModifier | Qt::ShiftModifier | Qt::Key_S), this);
    connect(saveAsShortcut, &QShortcut::activated, this, &MainWindow::saveFileActions);

    QShortcut* delShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    connect(delShortcut, &QShortcut::activated, this, &MainWindow::onDeleteSelectedRow);

    QShortcut* quitShortcut = new QShortcut(QKeySequence(Qt::MetaModifier | Qt::Key_Q), this);
    connect(quitShortcut, &QShortcut::activated, this, &MainWindow::close);

    // Подключаем событие контекстного меню
    connect(meterView.get(), &MeterListView::rowDeleted, this, &MainWindow::onDeleteSelectedRow);
}
