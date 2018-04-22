/********************************************************************************
** Form generated from reading UI file 'InstructionEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTRUCTIONEDITOR_H
#define UI_INSTRUCTIONEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InstructionEditor
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *instructionText;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *definitionText;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *opSize;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *cancelButton;
    QPushButton *okButton;

    void setupUi(QWidget *InstructionEditor)
    {
        if (InstructionEditor->objectName().isEmpty())
            InstructionEditor->setObjectName(QStringLiteral("InstructionEditor"));
        InstructionEditor->resize(359, 141);
        verticalLayout_2 = new QVBoxLayout(InstructionEditor);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(InstructionEditor);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        instructionText = new QLineEdit(InstructionEditor);
        instructionText->setObjectName(QStringLiteral("instructionText"));

        horizontalLayout->addWidget(instructionText);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(InstructionEditor);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        definitionText = new QLineEdit(InstructionEditor);
        definitionText->setObjectName(QStringLiteral("definitionText"));

        horizontalLayout_2->addWidget(definitionText);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(InstructionEditor);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        opSize = new QComboBox(InstructionEditor);
        opSize->addItem(QString());
        opSize->addItem(QString());
        opSize->addItem(QString());
        opSize->addItem(QString());
        opSize->setObjectName(QStringLiteral("opSize"));

        horizontalLayout_4->addWidget(opSize);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        cancelButton = new QPushButton(InstructionEditor);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_5->addWidget(cancelButton);

        okButton = new QPushButton(InstructionEditor);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout_5->addWidget(okButton);


        verticalLayout_2->addLayout(horizontalLayout_5);


        retranslateUi(InstructionEditor);

        QMetaObject::connectSlotsByName(InstructionEditor);
    } // setupUi

    void retranslateUi(QWidget *InstructionEditor)
    {
        InstructionEditor->setWindowTitle(QApplication::translate("InstructionEditor", "InstructionEditor", nullptr));
        label->setText(QApplication::translate("InstructionEditor", "Instruction", nullptr));
        label_2->setText(QApplication::translate("InstructionEditor", "Definition  ", nullptr));
        label_3->setText(QApplication::translate("InstructionEditor", "Operand Size (characters)", nullptr));
        opSize->setItemText(0, QApplication::translate("InstructionEditor", "0", nullptr));
        opSize->setItemText(1, QApplication::translate("InstructionEditor", "1", nullptr));
        opSize->setItemText(2, QApplication::translate("InstructionEditor", "2", nullptr));
        opSize->setItemText(3, QApplication::translate("InstructionEditor", "3", nullptr));

        cancelButton->setText(QApplication::translate("InstructionEditor", "Cancel", nullptr));
        okButton->setText(QApplication::translate("InstructionEditor", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InstructionEditor: public Ui_InstructionEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTRUCTIONEDITOR_H
