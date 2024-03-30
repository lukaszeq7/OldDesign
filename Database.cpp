#include "Database.h"

Database::Database(QObject *parent)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName("baza.db");
    if (!_db.open()) {
        emit errorOccurred("Nie udało się połączyć z bazą danych: " + _db.lastError().text());
    }

    connect(this, &Database::errorOccurred, this, &Database::onErrorOccurred);
}

Database::~Database()
{
    _db.close();
}

void Database::fetchBeds()
{
    QList<Bed*> beds;

    QSqlQuery query = QSqlQuery(_db);
    query.prepare("SELECT * FROM Bed;");
    if (!query.exec()) {
        emit errorOccurred("Błąd podczas wykonywania zapytania SQL: " + query.lastError().text());
        return;
    }

    while (query.next())
    {
        Bed *bed = new Bed();

        bed->setId(query.value(0).toInt());
        bed->setName(query.value(1).toString());
        bed->setWidth(query.value(2).toInt());
        bed->setLength(query.value(3).toInt());
        bed->setHeight(query.value(4).toInt());
        bed->setFabric(query.value(5).toString());

        beds.append(bed);
    }

    emit bedsFetched(beds);
}

void Database::onErrorOccurred(QString errorMessage)
{
    qDebug() << "Błąd: " << errorMessage;
}
