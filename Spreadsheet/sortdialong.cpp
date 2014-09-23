#include "sortdialong.h"
//#include "ui_sortdialong.h"

SortDialong::SortDialong(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    //**************************************
    secondaryGroupBox->hide();
    tertiaryGroupBox->hide();
    layout()->setSizeConstraint(QLayout::SetFixedSize);//大小不能修改
    setColumnRange('A','Z');//初始化选择的列组合框内容
}

SortDialong::~SortDialong()
{
}
//****************************************
void SortDialong::setColumnRange(QChar first, QChar last)
{
    primaryColumnCombo->clear();
    secondaryColumnCombo->clear();
    tertiaryColumnCombo->clear();

    secondaryColumnCombo->addItem(tr("None"));
    tertiaryColumnCombo->addItem(tr("None"));
    primaryColumnCombo->setMinimumSize(
    secondaryColumnCombo->sizeHint());
    //将主键组合框的大小设置成为第二键组合框的理想大小

    QChar ch = first;
    while(ch <= last)
    {
        primaryColumnCombo->addItem(QString(ch));
        secondaryColumnCombo->addItem(QString(ch));
        tertiaryColumnCombo->addItem(QString(ch));
        ch = ch.unicode() + 1;
    }
}









