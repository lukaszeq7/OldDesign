#include "BedsWidget.h"

BedsWidget::BedsWidget(QWidget *parent)
    : QWidget(parent)
    , _mainLayout(new QVBoxLayout(this))
    , _tableView(new QTableView(this))
    , _bedModel(new BedModel(this))
{
    setupUi();
}

BedsWidget::~BedsWidget()
{
}

void BedsWidget::setupUi()
{
    _mainLayout->addWidget(_tableView);
    _tableView->setModel(_bedModel);
}
