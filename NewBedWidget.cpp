#include "NewBedWidget.h"
#include "ui_NewBedWidget.h"

NewBedWidget::NewBedWidget(QWidget *parent) 
        : QWidget(parent)
        , ui(new Ui::NewBedWidget)
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
    connect(ui->addButton, &QPushButton::clicked, this, &NewBedWidget::onAddButtonClicked);
}

void NewBedWidget::onExitButtonClicked()
{
    close();
}

void NewBedWidget::onAddButtonClicked()
{
    Bed* bed = new Bed(this);
    bed->setName(ui->nameEdit->text());
    bed->setWidth(ui->widthEdit->text().toInt());
    bed->setLength(ui->lengthEdit->text().toInt());
    bed->setHeight(ui->heightEdit->text().toInt());
    bed->setFabric(ui->fabricEdit->text());
    emit addBed(bed);

    ui->confirmationLabel->setText(bed->name() + " added");

    clearData();
}

void NewBedWidget::clearData()
{
    ui->nameEdit->setText("");
    ui->widthEdit->setText("");
    ui->lengthEdit->setText("");
    ui->heightEdit->setText("");
    ui->fabricEdit->setText("");
}
