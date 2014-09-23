#ifndef SORTDIALONG_H
#define SORTDIALONG_H

#include <QDialog>
#include "ui_sortdialong.h"

/*namespace Ui {
class SortDialong;
}*/

class SortDialong : public QDialog , public Ui_SortDialong
{
    Q_OBJECT

public:
    explicit SortDialong(QWidget *parent = 0);
    ~SortDialong();

    //***************************************
    void setColumnRange(QChar first,QChar last);

private:
    //Ui::SortDialong *ui;
};

#endif // SORTDIALONG_H
