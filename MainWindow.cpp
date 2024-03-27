#include <QDebug>
#include <QSqlQuery>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent)
        , _mainLayout(new QVBoxLayout(this))
        , _tableView(new QTableView(this))
        , _bedModel(new BedModel(this))
        , _db(new Database(this))
{
    setFixedSize(800, 600);

    _mainLayout->addWidget(_tableView);
    _tableView->setModel(_bedModel);

    connect(_db, &Database::bedsFetched, this, &MainWindow::onBedsFetched);
    connect(_db, &Database::errorOccurred, this, &MainWindow::onErrorOccurred);

    _db->fetchBeds();
}

MainWindow::~MainWindow()
{
    qDeleteAll(_beds);
}

void MainWindow::onBedsFetched(QList<Bed*> beds)
{
    _beds = beds;

    for(Bed* bed : _beds)
    {
        qDebug() << bed->id() << bed->name() << bed->width() << bed->length() << bed->height() << bed->fabric();
    }
}

void MainWindow::onErrorOccurred(QString errorMessage)
{
    qDebug() << "Błąd: " << errorMessage;
}
