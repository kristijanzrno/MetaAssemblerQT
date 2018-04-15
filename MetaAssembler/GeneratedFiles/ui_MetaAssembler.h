/********************************************************************************
** Form generated from reading UI file 'MetaAssembler.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_METAASSEMBLER_H
#define UI_METAASSEMBLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MetaAssemblerClass
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave_As;
    QAction *actionExit;
    QAction *actionSelection;
    QAction *actionDocument;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionDelete;
    QAction *actionEditor;
    QAction *actionCDM_Table_View;
    QAction *actionCustomise;
    QAction *actionOptions;
    QAction *action68K_General_Help;
    QAction *actionAbout;
    QAction *actionToolbarNew;
    QAction *actionToolbarOpen;
    QAction *actionToolbarSave;
    QAction *actionToolbarReformat;
    QAction *actionToolbarCut;
    QAction *actionToolbarCopy;
    QAction *actionToolbarPaste;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEdit;
    QTableView *tableView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuReformat;
    QMenu *menuView;
    QMenu *menuTools;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MetaAssemblerClass)
    {
        if (MetaAssemblerClass->objectName().isEmpty())
            MetaAssemblerClass->setObjectName(QStringLiteral("MetaAssemblerClass"));
        MetaAssemblerClass->resize(1500, 1000);
        MetaAssemblerClass->setMinimumSize(QSize(1500, 1000));
        actionNew = new QAction(MetaAssemblerClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(MetaAssemblerClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave_As = new QAction(MetaAssemblerClass);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionExit = new QAction(MetaAssemblerClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSelection = new QAction(MetaAssemblerClass);
        actionSelection->setObjectName(QStringLiteral("actionSelection"));
        actionDocument = new QAction(MetaAssemblerClass);
        actionDocument->setObjectName(QStringLiteral("actionDocument"));
        actionCut = new QAction(MetaAssemblerClass);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        actionCopy = new QAction(MetaAssemblerClass);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        actionPaste = new QAction(MetaAssemblerClass);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        actionDelete = new QAction(MetaAssemblerClass);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        actionEditor = new QAction(MetaAssemblerClass);
        actionEditor->setObjectName(QStringLiteral("actionEditor"));
        actionCDM_Table_View = new QAction(MetaAssemblerClass);
        actionCDM_Table_View->setObjectName(QStringLiteral("actionCDM_Table_View"));
        actionCustomise = new QAction(MetaAssemblerClass);
        actionCustomise->setObjectName(QStringLiteral("actionCustomise"));
        actionOptions = new QAction(MetaAssemblerClass);
        actionOptions->setObjectName(QStringLiteral("actionOptions"));
        action68K_General_Help = new QAction(MetaAssemblerClass);
        action68K_General_Help->setObjectName(QStringLiteral("action68K_General_Help"));
        actionAbout = new QAction(MetaAssemblerClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionToolbarNew = new QAction(MetaAssemblerClass);
        actionToolbarNew->setObjectName(QStringLiteral("actionToolbarNew"));
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToolbarNew->setIcon(icon);
        actionToolbarOpen = new QAction(MetaAssemblerClass);
        actionToolbarOpen->setObjectName(QStringLiteral("actionToolbarOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("Resources/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToolbarOpen->setIcon(icon1);
        actionToolbarSave = new QAction(MetaAssemblerClass);
        actionToolbarSave->setObjectName(QStringLiteral("actionToolbarSave"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("Resources/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToolbarSave->setIcon(icon2);
        actionToolbarReformat = new QAction(MetaAssemblerClass);
        actionToolbarReformat->setObjectName(QStringLiteral("actionToolbarReformat"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("Resources/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToolbarReformat->setIcon(icon3);
        actionToolbarCut = new QAction(MetaAssemblerClass);
        actionToolbarCut->setObjectName(QStringLiteral("actionToolbarCut"));
        QIcon icon4;
        icon4.addFile(QStringLiteral("Resources/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToolbarCut->setIcon(icon4);
        actionToolbarCopy = new QAction(MetaAssemblerClass);
        actionToolbarCopy->setObjectName(QStringLiteral("actionToolbarCopy"));
        QIcon icon5;
        icon5.addFile(QStringLiteral("Resources/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToolbarCopy->setIcon(icon5);
        actionToolbarPaste = new QAction(MetaAssemblerClass);
        actionToolbarPaste->setObjectName(QStringLiteral("actionToolbarPaste"));
        QIcon icon6;
        icon6.addFile(QStringLiteral("Resources/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToolbarPaste->setIcon(icon6);
        centralWidget = new QWidget(MetaAssemblerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        horizontalLayout->addWidget(textEdit);

        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        horizontalLayout->addWidget(tableView);


        horizontalLayout_2->addLayout(horizontalLayout);

        MetaAssemblerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MetaAssemblerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1500, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuReformat = new QMenu(menuEdit);
        menuReformat->setObjectName(QStringLiteral("menuReformat"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MetaAssemblerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MetaAssemblerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MetaAssemblerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MetaAssemblerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MetaAssemblerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionExit);
        menuEdit->addAction(menuReformat->menuAction());
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionDelete);
        menuReformat->addAction(actionSelection);
        menuReformat->addAction(actionDocument);
        menuView->addAction(actionEditor);
        menuView->addAction(actionCDM_Table_View);
        menuTools->addAction(actionCustomise);
        menuTools->addAction(actionOptions);
        menuHelp->addAction(action68K_General_Help);
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionToolbarNew);
        mainToolBar->addAction(actionToolbarOpen);
        mainToolBar->addAction(actionToolbarSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionToolbarReformat);
        mainToolBar->addAction(actionToolbarCut);
        mainToolBar->addAction(actionToolbarCopy);
        mainToolBar->addAction(actionToolbarPaste);

        retranslateUi(MetaAssemblerClass);

        QMetaObject::connectSlotsByName(MetaAssemblerClass);
    } // setupUi

    void retranslateUi(QMainWindow *MetaAssemblerClass)
    {
        MetaAssemblerClass->setWindowTitle(QApplication::translate("MetaAssemblerClass", "MetaAssembler", nullptr));
        actionNew->setText(QApplication::translate("MetaAssemblerClass", "New", nullptr));
        actionOpen->setText(QApplication::translate("MetaAssemblerClass", "Open", nullptr));
        actionSave_As->setText(QApplication::translate("MetaAssemblerClass", "Save As...", nullptr));
        actionExit->setText(QApplication::translate("MetaAssemblerClass", "Exit", nullptr));
        actionSelection->setText(QApplication::translate("MetaAssemblerClass", "Selection", nullptr));
        actionDocument->setText(QApplication::translate("MetaAssemblerClass", "Document", nullptr));
        actionCut->setText(QApplication::translate("MetaAssemblerClass", "Cut", nullptr));
        actionCopy->setText(QApplication::translate("MetaAssemblerClass", "Copy", nullptr));
        actionPaste->setText(QApplication::translate("MetaAssemblerClass", "Paste", nullptr));
        actionDelete->setText(QApplication::translate("MetaAssemblerClass", "Delete", nullptr));
        actionEditor->setText(QApplication::translate("MetaAssemblerClass", "Editor", nullptr));
        actionCDM_Table_View->setText(QApplication::translate("MetaAssemblerClass", "CDM Table View", nullptr));
        actionCustomise->setText(QApplication::translate("MetaAssemblerClass", "Customise", nullptr));
        actionOptions->setText(QApplication::translate("MetaAssemblerClass", "Options", nullptr));
        action68K_General_Help->setText(QApplication::translate("MetaAssemblerClass", "68K General Help", nullptr));
        actionAbout->setText(QApplication::translate("MetaAssemblerClass", "About", nullptr));
        actionToolbarNew->setText(QApplication::translate("MetaAssemblerClass", "New", nullptr));
        actionToolbarOpen->setText(QApplication::translate("MetaAssemblerClass", "Open", nullptr));
        actionToolbarSave->setText(QApplication::translate("MetaAssemblerClass", "Save", nullptr));
        actionToolbarReformat->setText(QApplication::translate("MetaAssemblerClass", "Reformat", nullptr));
        actionToolbarCut->setText(QApplication::translate("MetaAssemblerClass", "Cut", nullptr));
        actionToolbarCopy->setText(QApplication::translate("MetaAssemblerClass", "Copy", nullptr));
        actionToolbarPaste->setText(QApplication::translate("MetaAssemblerClass", "Paste", nullptr));
        menuFile->setTitle(QApplication::translate("MetaAssemblerClass", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("MetaAssemblerClass", "Edit", nullptr));
        menuReformat->setTitle(QApplication::translate("MetaAssemblerClass", "Reformat", nullptr));
        menuView->setTitle(QApplication::translate("MetaAssemblerClass", "View", nullptr));
        menuTools->setTitle(QApplication::translate("MetaAssemblerClass", "Tools", nullptr));
        menuHelp->setTitle(QApplication::translate("MetaAssemblerClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MetaAssemblerClass: public Ui_MetaAssemblerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_METAASSEMBLER_H
