#ifndef OLDDESIGN_APPLICATION_H
#define OLDDESIGN_APPLICATION_H

#include <QApplication>

class Application : public QApplication
{
Q_OBJECT

public:
    explicit Application(int &argc, char **argv);
    ~Application() override;
};

#endif //OLDDESIGN_APPLICATION_H
