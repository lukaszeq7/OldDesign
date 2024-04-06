#include "BedsWidget.h"
#include "ui_BedsWidget.h"

BedsWidget::BedsWidget(QWidget *parent) :
        QWidget(parent)
        , ui(new Ui::BedsWidget)
        , _bedModel(new BedModel(this))
{
    ui->setupUi(this);
    _newBedWidget = new NewBedWidget(this);
    _newBedWidget->hide();

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

    connect(_newBedWidget, &NewBedWidget::addBed, this, &BedsWidget::addBed);
    connect(_newBedWidget, &NewBedWidget::editBed, this, &BedsWidget::editBed);
    connect(_newBedWidget, &NewBedWidget::closeWidget, this, &BedsWidget::disableButtons);
    connect(_newBedWidget, &NewBedWidget::getLastBedId, this, &BedsWidget::lastBedId);
}

void BedsWidget::onAddButtonClicked()
{
    _newBedWidget->setEditMode(false);
    _newBedWidget->show();

    disableButtons(true);
}

void BedsWidget::onDeleteButtonClicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty())
        return;

    if(!_bedModel->rowCount())
        return;

    int bedId = selectedIndexes.first().data(Qt::DisplayRole).toInt();
    _bedModel->deleteBed(bedId);
}

void BedsWidget::onEditButtonClicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty())
        return;

    if(!_bedModel->rowCount())
        return;

    int bedId = selectedIndexes.first().data(Qt::DisplayRole).toInt();
    Bed* bed = _bedModel->getBed(bedId);
    _newBedWidget->editBedForm(bed);
    _newBedWidget->setEditMode(true);
    _newBedWidget->show();

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

void BedsWidget::lastBedId()
{
    _newBedWidget->setLastBedId(_bedModel->lastBedId());
}
