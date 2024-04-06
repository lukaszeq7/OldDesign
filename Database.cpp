#include "Database.h"

Database::Database(QObject *parent)
{
    connect(this, &Database::bedsFetched, this, &Database::onBedsFetched);
    connect(this, &Database::bedSaved, this, &Database::onBedSaved);
    connect(this, &Database::bedDeleted, this, &Database::onBedDeleted);
    connect(this, &Database::bedUpdated, this, &Database::onBedUpdated);
    connect(this, &Database::errorOccurred, this, &Database::onErrorOccurred);
}

Database::~Database()
{
    _database.close();
}

void Database::connectToDatabase()
{
    if(_database.isOpen())
    {
        return;
    }

    _database = QSqlDatabase::addDatabase("QSQLITE");
    _database.setDatabaseName("baza.db");
    if (!_database.open())
    {
        emit errorOccurred("Can't connect to database: " + _database.lastError().text());
    }
}

void Database::fetchBeds()
{
    if ( !_database.isOpen() )
    {
        _database.open();
        if ( !_database.isOpen() )
        {
            emit errorOccurred("Can't connect to database: " + _database.lastError().text());
            return;
        }
    }

    QList<Bed*> beds;

    QSqlQuery query = QSqlQuery(_database);
    query.prepare("SELECT * FROM Bed;");
    if (!query.exec())
    {
        emit errorOccurred("Error executing SQL query: " + query.lastError().text());
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
        beds.append(bed);
    }

    emit bedsFetched(beds);
}

void Database::saveBed(Bed* bed)
{
    if ( !_database.isOpen() )
    {
        _database.open();
        if ( !_database.isOpen() )
        {
            emit errorOccurred("Can't connect to database: " + _database.lastError().text());
            return;
        }
    }

    QSqlQuery query(_database);
    query.prepare("INSERT INTO Bed (id, name, width, length, height, fabric) "
                  "VALUES (:id, :name, :width, :length, :height, :fabric)");
    query.bindValue(":id", bed->id());
    query.bindValue(":name", bed->name());
    query.bindValue(":width", bed->width());
    query.bindValue(":length", bed->length());
    query.bindValue(":height", bed->height());
    query.bindValue(":fabric", bed->fabric());

    if (!query.exec())
    {
        emit errorOccurred("Error while saving the bed to the database: " + query.lastError().text());
        return;
    }

    emit bedSaved(bed);
}

void Database::deleteBed(int bedId)
{
    QSqlQuery query(_database);
    query.prepare("DELETE FROM Bed WHERE id = :id");
    query.bindValue(":id", bedId);

    if (!query.exec())
    {
        emit errorOccurred("Error while deleting the bed from the database: " + query.lastError().text());
        return;
    }

    emit bedDeleted(bedId);
}

void Database::updateBed(Bed* bed)
{
    if (!_database.isOpen())
    {
        _database.open();
        if (!_database.isOpen())
        {
            emit errorOccurred("Can't connect to database: " + _database.lastError().text());
            return;
        }
    }

    QSqlQuery query(_database);
    query.prepare("UPDATE Bed "
                  "SET name = :name, width = :width, length = :length, height = :height, fabric = :fabric "
                  "WHERE id = :id");
    query.bindValue(":id", bed->id());
    query.bindValue(":name", bed->name());
    query.bindValue(":width", bed->width());
    query.bindValue(":length", bed->length());
    query.bindValue(":height", bed->height());
    query.bindValue(":fabric", bed->fabric());

    if (!query.exec())
    {
        emit errorOccurred("Error while updating the bed in the database: " + query.lastError().text());
        return;
    }

    emit bedUpdated(bed);
}


void Database::onErrorOccurred(QString errorMessage)
{
    qDebug() << "Error: " << errorMessage;
}

void Database::onBedSaved(Bed* bed)
{
    qDebug() << "Database ADDED bed:"
        << bed->id()
        << bed->name()
        << "Width:" << bed->width()
        << "Length:" << bed->length()
        << "Height:" << bed->height()
        << "Fabric" << bed->fabric();
}

void Database::onBedDeleted(int bedId)
{
    qDebug() << "Database DELETED bed id:" << bedId;
}

void Database::onBedsFetched()
{
    qDebug() << "Beds FETCHED from database";
}

void Database::onBedUpdated(Bed *bed)
{
    qDebug() << "Database UPDATED bed:"
             << bed->id()
             << bed->name()
             << "Width:" << bed->width()
             << "Length:" << bed->length()
             << "Height:" << bed->height()
             << "Fabric" << bed->fabric();
}
