#ifndef TEST_H
#define TEST_H

#include <QWidget>

class DataInput;

class test : public QWidget
{
    Q_OBJECT

DataInput *myData;

public:
    explicit test(QWidget *parent = 0);
    test(DataInput *Data);
    ~test();

signals:

private slots:
    void dasnTest();
};

#endif // TEST_H
