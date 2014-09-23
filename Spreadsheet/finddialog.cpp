#include "finddialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>


FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    //**************************************
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);//伙伴关系

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));
    findButton = new QPushButton(tr("&Find"));
    findButton->setDefault(true);
    findButton->setEnabled(false);//禁用按钮

    closeButton = new QPushButton(tr("Close"));

    connect(lineEdit,SIGNAL(textChanged(const QString &)),this
            ,SLOT(enableFindButton(const QString &)));
    connect(findButton,SIGNAL(clicked()),this,SLOT(findClicked()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));

    QHBoxLayout *topleftLayout = new QHBoxLayout;
    topleftLayout->addWidget(label);
    topleftLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topleftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);//
    setWindowTitle(tr("Find"));
    setFixedHeight(sizeHint().height());//这个可以返回一个窗口部件所“理想”的尺寸大小
}

FindDialog::~FindDialog()
{

}
void FindDialog::findClicked()
{
    QString text = lineEdit->text();
    //Qt::CaseSensitive cs = caseCheckBox->isChecked()?Qt::CaseSensitive:Qt::CaseInsensitive;
    bool cs = caseCheckBox->isChecked()?Qt::CaseSensitive:Qt::CaseInsensitive;
    if(backwardCheckBox->isChecked())
    {
        emit findPrevious(text,cs);
    }
    else
    {
        emit findNext(text,cs);
    }
}
void FindDialog::enableFindButton(const QString &text)
{
    findButton->setEnabled(!text.isEmpty());
}

