#ifndef GOTOCELL_H
#define GOTOCELL_H

#include <QDialog>
#include "ui_gotocell.h"

class GoToCell : public QDialog , public Ui::GoToCell
{
    Q_OBJECT

public:
    explicit GoToCell(QWidget *parent = 0);
    ~GoToCell();

private:
private slots:
    void on_lineEdit_textChanged();
};

#endif // GOTOCELL_H
