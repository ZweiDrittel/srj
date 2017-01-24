#include "datainput.h"
#include "ui_datainput.h"
#include "test.h"

DataInput::DataInput(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataInput)
{
    ui->setupUi(this);

    test *kleinerTest = new test(this);

    connect(ui->Button, SIGNAL(clicked()), this, SLOT(dasnTest()));
}

DataInput::~DataInput()
{
    delete ui;
}


