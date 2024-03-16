#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent)
        , _mainLayout(new QVBoxLayout(this))
        , _tableView(new QTableView(this))
        , _bedModel(new BedModel(this))
{
    setFixedSize(800, 600);

    _mainLayout->addWidget(_tableView);
    _tableView->setModel(_bedModel);



}

MainWindow::~MainWindow()
{
}
