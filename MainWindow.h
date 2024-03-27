#ifndef OLDDESIGN_MAINWINDOW_H
#define OLDDESIGN_MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QSqlDatabase>
#include "Bed.h"
#include "BedModel.h"

class MainWindow : public QWidget
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    QVBoxLayout* _mainLayout;
    QTableView* _tableView;
    BedModel* _bedModel;
    QSqlDatabase _db;

    QList<Bed*> _beds;
};

#endif //OLDDESIGN_MAINWINDOW_H
