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
    connect(newBedWidget, &NewBedWidget:: closeWidget, this, &BedsWidget::disableButtons);

    disableButtons(true);
}

void BedsWidget::onDeleteButtonClicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty())
        return;

    int bedId = selectedIndexes.first().data(Qt::DisplayRole).toInt();
    _bedModel->deleteBed(bedId);
}

void BedsWidget::onEditButtonClicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty())
        return;

    NewBedWidget* newBedWidget = new NewBedWidget(this);
    newBedWidget->setAutoFillBackground(true);
    newBedWidget->show();

    int bedId = selectedIndexes.first().data(Qt::DisplayRole).toInt();
    Bed* bed = _bedModel->getBed(bedId);
    newBedWidget->editBedForm(bed);

    connect(newBedWidget, &NewBedWidget::editBed, this, &BedsWidget::editBed);
    connect(newBedWidget, &NewBedWidget:: closeWidget, this, &BedsWidget::disableButtons);

    disableButtons(true);
}

void BedsWidget::addBed(Bed *bed)
{
    _bedModel->addBed(bed);
}

void BedsWidget::editBed(Bed *bed)
{
    _bedModel->editBed(bed);
}

void BedsWidget::disableButtons(bool disable)
{
    ui->addButton->setDisabled(disable);
    ui->editButton->setDisabled(disable);
    ui->deleteButton->setDisabled(disable);
}
