#ifndef OLDDESIGN_BEDSWIDGET_H
#define OLDDESIGN_BEDSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include "BedModel.h"

class BedsWidget : public QWidget
{
Q_OBJECT

public:
    explicit BedsWidget(QWidget *parent = nullptr);
    ~BedsWidget() override;

private:
    QVBoxLayout* _mainLayout;
    QTableView* _tableView;
    BedModel* _bedModel;

    void setupUi();
};

#endif //OLDDESIGN_BEDSWIDGET_H
