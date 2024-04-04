#include "BedsWidget.h"
#include "ui_BedsWidget.h"
#include "NewBedWidget.h"

BedsWidget::BedsWidget(QWidget *parent) :
        QWidget(parent)
        , ui(new Ui::BedsWidget)
        , _bedModel(new BedModel(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(_bedModel);
    setConnections();
}

BedsWidget::~BedsWidget()
{
    delete ui;
}

void BedsWidget::setConnections()
{
    connect(ui->addButton, &QPushButton::clicked, this, &BedsWidget::onAddButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &BedsWidget::onDeleteButtonClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &BedsWidget::onEditButtonClicked);
}

void BedsWidget::onAddButtonClicked()
{
    NewBedWidget* newBedWidget = new NewBedWidget(this);
    newBedWidget->setAutoFillBackground(true);
    newBedWidget->show();

    connect(newBedWidget, &NewBedWidget::addBed, this, &BedsWidget::addBed);
}

void BedsWidget::onDeleteButtonClicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty())
        return;

    _bedModel->removeSelectedRows(selectedIndexes);
}

void BedsWidget::onEditButtonClicked()
{

}

void BedsWidget::addBed(Bed *bed)
{
    _bedModel->addBed(bed);
}