#include "gotocell.h"
#include "ui_gotocell.h"

GoToCell::GoToCell(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    QRegExp regExp("[A-Za-z][0-9]{0,2}");
    lineEdit->setValidator(new QRegExpValidator(regExp,this));

    connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));

}

GoToCell::~GoToCell()
{
}
//******************************************
void GoToCell::on_lineEdit_textChanged()
{
    okButton->setEnabled(lineEdit->hasAcceptableInput());
}

