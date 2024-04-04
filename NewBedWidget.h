#ifndef OLDDESIGN_NEWBEDWIDGET_H
#define OLDDESIGN_NEWBEDWIDGET_H

#include <QWidget>
#include "Bed.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NewBedWidget; }
QT_END_NAMESPACE

class NewBedWidget : public QWidget
{
Q_OBJECT

public:
    explicit NewBedWidget(QWidget *parent = nullptr);
    ~NewBedWidget() override;

signals:
    void addBed(Bed* bed);

private slots:
    void onExitButtonClicked();
    void onAddButtonClicked();

private:
    Ui::NewBedWidget *ui;

    void setPosition(QWidget* parent);
    void setConnections();
    void clearData();
};

#endif //OLDDESIGN_NEWBEDWIDGET_H
