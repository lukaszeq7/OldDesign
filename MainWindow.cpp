#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent)
        , _mainLayout(new QVBoxLayout(this))
        , _bedsWidget(new BedsWidget(this))
{
    setFixedSize(800, 600);

    _mainLayout->addWidget(_bedsWidget);
}

MainWindow::~MainWindow()
{
}