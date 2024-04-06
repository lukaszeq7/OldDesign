#ifndef OLDDESIGN_BEDSWIDGET_H
#define OLDDESIGN_BEDSWIDGET_H

#include <QWidget>
#include "BedModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BedsWidget; }
QT_END_NAMESPACE

class BedsWidget : public QWidget
{
Q_OBJECT

public:
    explicit BedsWidget(QWidget *parent = nullptr);
    ~BedsWidget() override;

private slots:
    void onAddButtonClicked();
    void onDeleteButtonClicked();
    void onEditButtonClicked();

    void addBed(Bed* bed);
    void editBed(Bed* bed);

    void disableButtons(bool disable);

private:
    Ui::BedsWidget *ui;
    BedModel* _bedModel;

    void setConnections();
};

#endif //OLDDESIGN_BEDSWIDGET_H
