#pragma once

#include <QtWidgets/QMainWindow>
#include <string>
#include "ui_MetaAssembler.h"
#include "FileHandler.h"
#include "qstandarditemmodel.h"
#include "Assembler.h"
#include "StatusOutput.h"

class MetaAssembler : public QMainWindow
{
	Q_OBJECT

public:
	MetaAssembler(QWidget *parent = Q_NULLPTR);

	//Functions to handle UI triggers
	private slots:
	void openHandler();
	void saveHandler();
	void exitHandler();
	void clearStatusHandler();
	void cutHandler();
	void copyHandler();
	void pasteHandler();
	void editorViewHandler();
	void tableViewHandler();
	void customiseHandler();
	void optionsHandler();
	void helpHandler();
	void aboutHandler();
	void documentNHandler();
	void assemble();
	void statusToggle();


private:
	void changeEvent(QEvent * event);
	void clearTable();

	FileHandler* fileHandler;
	Assembler* assembler;
	StatusOutput* statusOutput;

	Ui::MetaAssemblerClass ui;
	QStandardItemModel* cedarTableModel;

};
