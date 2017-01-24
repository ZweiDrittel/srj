#include "test.h"
#include "datainput.h"

test::test(QWidget *parent) : QWidget(parent)
{

}

test::test(DataInput *Data)
{
    myData = Data;
}

test::~test()
{
}

void test::dasnTest()
{
    myData->ui->Result->setText("klappt!");
}
