#include "Application.h"
#include <QDebug>

Application::Application(int &argc, char **argv)
        : QApplication(argc, argv)
{
    qDebug() << "...:::Old Design::..";
}

Application::~Application()
{

}