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

public slots:
    void fetchBeds();
    void onErrorOccurred(QString errorMessage);

signals:
    void bedsFetched(const QList<Bed*>& beds);
    void errorOccurred(const QString errorMessage);

private:
    QSqlDatabase _db;
};

#endif //OLDDESIGN_DATABASE_H
