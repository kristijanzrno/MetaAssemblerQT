/********************************************************************************
** Form generated from reading UI file 'Options.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Options
{
public:
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *Options)
    {
        if (Options->objectName().isEmpty())
            Options->setObjectName(QStringLiteral("Options"));
        Options->resize(500, 325);
        horizontalLayout = new QHBoxLayout(Options);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableView = new QTableView(Options);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        addButton = new QPushButton(Options);
        addButton->setObjectName(QStringLiteral("addButton"));

        verticalLayout->addWidget(addButton);

        editButton = new QPushButton(Options);
        editButton->setObjectName(QStringLiteral("editButton"));

        verticalLayout->addWidget(editButton);

        removeButton = new QPushButton(Options);
        removeButton->setObjectName(QStringLiteral("removeButton"));

        verticalLayout->addWidget(removeButton);

        okButton = new QPushButton(Options);
        okButton->setObjectName(QStringLiteral("okButton"));

        verticalLayout->addWidget(okButton);

        cancelButton = new QPushButton(Options);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        verticalLayout->addWidget(cancelButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(Options);

        QMetaObject::connectSlotsByName(Options);
    } // setupUi

    void retranslateUi(QWidget *Options)
    {
        Options->setWindowTitle(QApplication::translate("Options", "Options", nullptr));
        addButton->setText(QApplication::translate("Options", "Add", nullptr));
        editButton->setText(QApplication::translate("Options", "Edit", nullptr));
        removeButton->setText(QApplication::translate("Options", "Remove", nullptr));
        okButton->setText(QApplication::translate("Options", "Save", nullptr));
        cancelButton->setText(QApplication::translate("Options", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Options: public Ui_Options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
