#include <QApplication>
#include "view/ui/MainWindow.h"
#include "view/console/ConsoleInterface.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Если нужно запустить GUI
    MainWindow window;
    window.show();

    // Если нужно запустить консольный режим
    // ConsoleInterface console;
    // console.run();

    return app.exec();
} 
