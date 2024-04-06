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

    void editBedForm(Bed *bed);

signals:
    void addBed(Bed* bed);
    void editBed(Bed* bed);
    void closeWidget(bool isOpen);

private slots:
    void onExitButtonClicked();
    void onOkButtonClicked();

private:
    Ui::NewBedWidget *ui;
    bool _editMode;
    Bed* _editBed;

    void setPosition(QWidget* parent);
    void setConnections();
    void clearData();
};

#endif //OLDDESIGN_NEWBEDWIDGET_H
