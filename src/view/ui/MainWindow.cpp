#include "view/ui/MainWindow.h"
#include "controller/MeterController.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QDebug>
#include <QShortcut>
#include <QContextMenuEvent>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), isModified(false) {

    setupUi();
    connectSignalsAndSlots();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupUi() {
    ui->setupUi(this);

    meterView = std::make_unique<MeterListView>(ui->meterTableView->parentWidget());
    meterView->setSelectionMode(QAbstractItemView::SingleSelection);
    meterView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->meterTableView->setWidget(meterView.get());

    // Настраиваем содержимое QScrollArea
    ui->meterTableView->setWidgetResizable(true);

    // Установим заголовок по умолчанию
    updateWindowTitle();
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

void MainWindow::loadFromFile(const QString& path) {
    controller.loadFromFile(path);
    meterView->updateView(controller.getMeters());
}

void MainWindow::loadFileActions() {
    // Получаем текущий каталог (предположим, что это корень проекта)
    QString projectRoot = QCoreApplication::applicationDirPath();

    // Открываем диалог выбора файла
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Открыть файл"),
        projectRoot                 // Начальный каталог — корень проекта
    );

    if (filePath.isEmpty()) {
        return; // Пользователь отменил выбор файла
    }

    try{
        loadFromFile(filePath);
        currentFilePath = filePath;
        isModified = false;
        updateWindowTitle();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(
            this,
            tr("Ошибка загрузки"),
            tr("Не удалось загрузить файл: ") + QString::fromStdString(e.what())
        );
    } catch (...) {
        QMessageBox::critical(
            this,
            tr("Неизвестная ошибка"),
            tr("Произошла неожиданная ошибка при загрузке файла.")
        );
    }
}
void MainWindow::saveToFile(const QString& path) {
    QString selectedPath = path;
    if (selectedPath.isEmpty()) {
        selectedPath = QFileDialog::getSaveFileName(
            this,
            tr("Сохранить файл"),
            "",
            "Текстовые файлы (*.txt);;CSV-файлы (*.csv)"
        );
    }

    if (!selectedPath.isEmpty()) {
        controller.saveToFile(selectedPath);
        currentFilePath = selectedPath;
        isModified = false;
        updateWindowTitle();
    }
}

void MainWindow::onDeleteSelectedRow() {
    int index = meterView->selectedRow();
    if (index >= 0 && static_cast<size_t>(index) < controller.getMeters().size()) {
        controller.removeMeter(index);
        meterView->updateView(controller.getMeters());
        isModified = true;
        updateWindowTitle();
    }
}

// void MainWindow::showContextMenu(const QPoint& pos) {
//     QMenu contextMenu(tr("Контекстное меню"), this);
//     QAction* deleteAction = contextMenu.addAction("Удалить");

//     QAction* action = contextMenu.exec(mapToGlobal(pos));

//     if (action == deleteAction) {
//         onDeleteSelectedRow();
//     }
// }

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
        } else if (btn == QMessageBox::No) {
            event->accept();
        } else {
            event->ignore();
        }
    } else {
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
        if (!filePath.isEmpty()) {
            try {
                loadFromFile(filePath);
                currentFilePath = filePath;
                isModified = false;
                updateWindowTitle();
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Ошибка", QString("Не удалось загрузить файл: ") + QString::fromStdString(e.what()));
            }
        }
    }
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