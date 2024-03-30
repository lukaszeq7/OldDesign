#include <QApplication>
#include "MainWindow.h"
#include "Application.h"

int main(int argc, char *argv[])
{
    Application a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
