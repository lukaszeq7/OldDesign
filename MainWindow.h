#ifndef OLDDESIGN_MAINWINDOW_H
#define OLDDESIGN_MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include "Bed.h"
#include "BedModel.h"
#include "Database.h"

class MainWindow : public QWidget
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

public slots:
    void onBedsFetched(QList<Bed*> beds);
    void onErrorOccurred(QString errorMessage);

private:
    QVBoxLayout* _mainLayout;
    QTableView* _tableView;

    QList<Bed*> _beds;
    BedModel* _bedModel;

    Database* _db;
};

#endif //OLDDESIGN_MAINWINDOW_H
