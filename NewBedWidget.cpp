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
    _editBed->setName(ui->nameEdit->text());
    _editBed->setWidth(ui->widthEdit->text().toInt());
    _editBed->setLength(ui->lengthEdit->text().toInt());
    _editBed->setHeight(ui->heightEdit->text().toInt());
    _editBed->setFabric(ui->fabricEdit->text());

    if(_editMode)
    {
        emit editBed(_editBed);
    }
    else
    {
        emit addBed(_editBed);

        ui->confirmationLabel->setText(_editBed->name() + " added");
        clearData();
        _editBed = nullptr;
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
    _editMode = true;

    ui->nameEdit->setText(_editBed->name());
    ui->widthEdit->setText(QString::number(_editBed->width()));
    ui->lengthEdit->setText(QString::number(_editBed->length()));
    ui->heightEdit->setText(QString::number(_editBed->height()));
    ui->fabricEdit->setText(_editBed->fabric());

    ui->confirmationLabel->setText(QString::number(_editBed->id()));
}
