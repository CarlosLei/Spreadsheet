/********************************************************************************
** Form generated from reading UI file 'gotocell.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOTOCELL_H
#define UI_GOTOCELL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GoToCell
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *GoToCell)
    {
        if (GoToCell->objectName().isEmpty())
            GoToCell->setObjectName(QStringLiteral("GoToCell"));
        GoToCell->resize(243, 71);
        verticalLayout = new QVBoxLayout(GoToCell);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(GoToCell);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(GoToCell);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        okButton = new QPushButton(GoToCell);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setEnabled(false);
        okButton->setDefault(true);

        horizontalLayout_2->addWidget(okButton);

        cancelButton = new QPushButton(GoToCell);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_2->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout_2);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(lineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(GoToCell);

        QMetaObject::connectSlotsByName(GoToCell);
    } // setupUi

    void retranslateUi(QDialog *GoToCell)
    {
        GoToCell->setWindowTitle(QApplication::translate("GoToCell", "Go To Cell", 0));
        label->setText(QApplication::translate("GoToCell", "&Cell Location:", 0));
        okButton->setText(QApplication::translate("GoToCell", "OK", 0));
        cancelButton->setText(QApplication::translate("GoToCell", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class GoToCell: public Ui_GoToCell {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOTOCELL_H
