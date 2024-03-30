#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent)
        , _mainLayout(new QVBoxLayout(this))
        , _tableView(new QTableView(this))
{
    setFixedSize(800, 600);

    _mainLayout->addWidget(_tableView);
}

MainWindow::~MainWindow()
{
}