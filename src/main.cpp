#include <QApplication>
#include "ui/MainWindow.h"
#include "console/ConsoleInterface.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Если нужно запустить GUI
    // MainWindow window;
    // window.show();

    // Если нужно запустить консольный режим
    ConsoleInterface console;
    console.run();

    return app.exec();
}