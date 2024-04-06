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
    void setLastBedId(int lastBedId);
    void setEditMode(bool editMode);

signals:
    void addBed(Bed* bed);
    void editBed(Bed* bed);
    void closeWidget(bool isOpen);
    void getLastBedId();

private slots:
    void onExitButtonClicked();
    void onOkButtonClicked();

private:
    Ui::NewBedWidget *ui;
    bool _editMode;
    Bed* _editBed;
    int _lastBedId;

    void setPosition(QWidget* parent);
    void setConnections();
    void clearData();
};

#endif //OLDDESIGN_NEWBEDWIDGET_H
