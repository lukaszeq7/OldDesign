#ifndef OLDDESIGN_DATABASE_H
#define OLDDESIGN_DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "Bed.h"

class Database : public QObject
{
Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    void connectToDatabase();

public slots:
    void fetchBeds();
    void onBedsFetched();

    void saveBed(Bed* bed);
    void onBedSaved(Bed* bed);

    void deleteBed(int bedId);
    void onBedDeleted(int bedId);

    void updateBed(Bed* bed);
    void onBedUpdated(Bed* bed);

    void onErrorOccurred(QString errorMessage);

signals:
    void bedsFetched(const QList<Bed*>& beds);
    void errorOccurred(const QString errorMessage);
    void bedSaved(Bed* bed);
    void bedDeleted(int bedId);
    void bedUpdated(Bed* bed);

private:
    QSqlDatabase _database;
};

#endif //OLDDESIGN_DATABASE_H
