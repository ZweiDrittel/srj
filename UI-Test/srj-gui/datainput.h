#ifndef DATAINPUT_H
#define DATAINPUT_H

#include <QMainWindow>

namespace Ui {
class DataInput;
}

class DataInput : public QMainWindow
{
    Q_OBJECT

public:
    explicit DataInput(QWidget *parent = 0);
    ~DataInput();
    Ui::DataInput *ui;

private slots:

private:

};

#endif // DATAINPUT_H
