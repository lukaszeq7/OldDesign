#include "Application.h"

Application::Application(int &argc, char **argv)
        : QApplication(argc, argv)
{
    onInit();
}

Application::~Application()
{
    qDeleteAll(_beds);
}

void Application::onInit()
{
    getBedsFromDatabase();
}

void Application::getBedsFromDatabase()
{
    _database = new Database(this);

    connect(_database, &Database::bedsFetched, this, &Application::onBedsFetched);
    connect(_database, &Database::errorOccurred, this, &Application::onErrorOccurred);

    _database->fetchBeds();
}

void Application::onBedsFetched(QList<Bed*> beds)
{
    _beds = beds;

    for(Bed* bed : _beds)
    {
        qDebug() << bed->id() << bed->name() << bed->width() << bed->length() << bed->height() << bed->fabric();
    }
}

void Application::onErrorOccurred(QString errorMessage)
{
    qDebug() << "Błąd: " << errorMessage;
}

QList<Bed *> Application::beds()
{
    return _beds;
}
