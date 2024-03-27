#include <QDebug>
#include <QSqlQuery>
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

    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName("baza.db");

    if (!_db.open())
    {
        qDebug() << "Nie udało się połączyć z bazą danych!";
        return;
    }

    QSqlQuery query("SELECT * FROM Bed;");
    if (!query.exec())
    {
        qDebug() << "Błąd podczas wykonywania zapytania SQL:";
        return;
    }

    while (query.next())
    {
        Bed *bed = new Bed(this);

        bed->setId(query.value(0).toInt());
        bed->setName(query.value(1).toString());
        bed->setWidth(query.value(2).toInt());
        bed->setLength(query.value(3).toInt());
        bed->setHeight(query.value(4).toInt());
        bed->setFabric(query.value(5).toString());

        _beds.append(bed);
    }

    for(Bed* bed : _beds)
    {
        qDebug() << bed->id() << bed->name() << bed->width() << bed->length() << bed->height() << bed->fabric();
    }
}

MainWindow::~MainWindow()
{
    _db.close();
    qDeleteAll(_beds);
}
