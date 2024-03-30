#ifndef OLDDESIGN_APPLICATION_H
#define OLDDESIGN_APPLICATION_H

#include <QApplication>
#include "Database.h"

class Application : public QApplication
{
Q_OBJECT

public:
    explicit Application(int &argc, char **argv);
    ~Application() override;

public slots:
    QList<Bed *> beds();

private:
    Database* _database;
    QList<Bed *> _beds;

    void onInit();

    void getBedsFromDatabase();
    void onBedsFetched(QList<Bed *> beds);
    void onErrorOccurred(QString errorMessage);
};

#endif //OLDDESIGN_APPLICATION_H
