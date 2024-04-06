#include "NewBedWidget.h"
#include "ui_NewBedWidget.h"

#include <QDebug>

NewBedWidget::NewBedWidget(QWidget *parent) 
        : QWidget(parent)
        , ui(new Ui::NewBedWidget)
        , _editMode(false)
        , _editBed(new Bed(this))
{
    ui->setupUi(this);
    setPosition(parent);
    setAutoFillBackground(true);

    setConnections();
}

NewBedWidget::~NewBedWidget()
{
    delete ui;
}

void NewBedWidget::setPosition(QWidget* parent)
{
    int parentWidth = parent->width();
    int parentHeight = parent->height();
    int widgetWidth = width();
    int widgetHeight = height();

    int x = (parentWidth - widgetWidth) / 2;
    int y = (parentHeight - widgetHeight) / 2;

    move(x, y);
}

void NewBedWidget::setConnections()
{
    connect(ui->exitButton, &QPushButton::clicked, this, &NewBedWidget::onExitButtonClicked);
    connect(ui->okButton, &QPushButton::clicked, this, &NewBedWidget::onOkButtonClicked);
}

void NewBedWidget::onExitButtonClicked()
{
    close();
    emit closeWidget(false);
}

void NewBedWidget::onOkButtonClicked()
{
    if(_editMode)
    {
        _editBed->setName(ui->nameEdit->text());
        _editBed->setWidth(ui->widthEdit->text().toInt());
        _editBed->setLength(ui->lengthEdit->text().toInt());
        _editBed->setHeight(ui->heightEdit->text().toInt());
        _editBed->setFabric(ui->fabricEdit->text());
        emit editBed(_editBed);

        ui->confirmationLabel->setText("Id " + QString::number(_editBed->id()) + " edited");
    }
    else
    {
        Bed* bed = new Bed(this);
        bed->setName(ui->nameEdit->text());
        bed->setWidth(ui->widthEdit->text().toInt());
        bed->setLength(ui->lengthEdit->text().toInt());
        bed->setHeight(ui->heightEdit->text().toInt());
        bed->setFabric(ui->fabricEdit->text());

        emit getLastBedId();
        bed->setId(_lastBedId + 1);//todo przy dodawaniu lozka nie zmienia id

        emit addBed(bed);

        ui->confirmationLabel->setText(bed->name() + " added");
        clearData();
    }
}

void NewBedWidget::clearData()
{
    ui->nameEdit->setText("");
    ui->widthEdit->setText("");
    ui->lengthEdit->setText("");
    ui->heightEdit->setText("");
    ui->fabricEdit->setText("");
}

void NewBedWidget::editBedForm(Bed *bed)
{
    _editBed = bed;

    ui->nameEdit->setText(_editBed->name());
    ui->widthEdit->setText(QString::number(_editBed->width()));
    ui->lengthEdit->setText(QString::number(_editBed->length()));
    ui->heightEdit->setText(QString::number(_editBed->height()));
    ui->fabricEdit->setText(_editBed->fabric());

    ui->confirmationLabel->setText(QString::number(_editBed->id()));
}

void NewBedWidget::setLastBedId(int lastBedId)
{
    _lastBedId = lastBedId;
}

void NewBedWidget::setEditMode(bool editMode)
{
    _editMode = editMode;
    if(!_editMode)
    {
        clearData();
    }
}
