#ifndef OLDDESIGN_MAINWINDOW_H
#define OLDDESIGN_MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include "BedsWidget.h"

class MainWindow : public QWidget
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QVBoxLayout* _mainLayout;
    BedsWidget* _bedsWidget;
};

#endif //OLDDESIGN_MAINWINDOW_H
