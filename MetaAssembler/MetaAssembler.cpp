#pragma once
#include "MetaAssembler.h"
#include <sstream>
#include "Options.h"
#include "qfontdialog.h"
#include "qdesktopservices.h"
#include "qfiledialog.h"
#include "qmessagebox.h"
using namespace std;

MetaAssembler::MetaAssembler(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(documentNHandler()));
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openHandler()));
	connect(ui.actionSave_As, SIGNAL(triggered()), this, SLOT(saveHandler()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(exitHandler()));
	connect(ui.actionCopy, SIGNAL(triggered()), this, SLOT(copyHandler()));
	connect(ui.actionCut, SIGNAL(triggered()), this, SLOT(cutHandler()));
	connect(ui.actionPaste, SIGNAL(triggered()), this, SLOT(pasteHandler()));
	connect(ui.actionDelete, SIGNAL(triggered()), this, SLOT(deleteHandler()));
	connect(ui.actionEditor, SIGNAL(triggered()), this, SLOT(editorViewHandler()));
	connect(ui.actionCDM_Table_View, SIGNAL(triggered()), this, SLOT(tableViewHandler()));
	connect(ui.actionCustomise, SIGNAL(triggered()), this, SLOT(customiseHandler()));
	connect(ui.actionOptions, SIGNAL(triggered()), this, SLOT(optionsHandler()));
	connect(ui.action68K_General_Help, SIGNAL(triggered()), this, SLOT(helpHandler()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(aboutHandler()));
	connect(ui.actionToolbarNew, SIGNAL(triggered()), this, SLOT(documentNHandler()));
	connect(ui.actionToolbarOpen, SIGNAL(triggered()), this, SLOT(openHandler()));
	connect(ui.actionToolbarSave, SIGNAL(triggered()), this, SLOT(saveHandler()));
	connect(ui.actionToolbarCut, SIGNAL(triggered()), this, SLOT(cutHandler()));
	connect(ui.actionToolbarPaste, SIGNAL(triggered()), this, SLOT(pasteHandler()));
	connect(ui.actionToolbarCopy, SIGNAL(triggered()), this, SLOT(copyHandler()));
	connect(ui.actionAssemble_to_CDM, SIGNAL(triggered()), this, SLOT(assemble()));
	connect(ui.actionConvertToCDM, SIGNAL(triggered()), this, SLOT(assemble()));
	connect(ui.actionStatus_View, SIGNAL(triggered()), this, SLOT(statusToggle()));
 	connect(ui.actionClear_Status_View, SIGNAL(triggered()), this, SLOT(clearStatusHandler()));

	
	//Populating the tableView
	cedarTableModel = new QStandardItemModel(256, 16, this);
	assembler = new Assembler(ui.statusText, cedarTableModel);

	//Columns
	stringstream stringStream;
	for (int i = 0; i < 16; i++) {
		stringStream << uppercase << hex << i;
		string title = stringStream.str();
		cedarTableModel->setHorizontalHeaderItem(i, new QStandardItem(QString::fromStdString(title)));
		stringStream.str("");
	}
	//Rows
	for (int i = 0; i < 256; i++) {
		stringStream << uppercase << "0x" << hex << i << "X";
		string title = stringStream.str();
		cedarTableModel->setVerticalHeaderItem(i, new QStandardItem(QString::fromStdString(title)));
		stringStream.str("");
	}
	ui.tableView->setModel(cedarTableModel);
	fileHandler = FileHandler(parent);
	statusOutput = new StatusOutput(ui.statusText);
	statusOutput->showMessage(0, 10);

}

void MetaAssembler::openHandler()
{
	string content = fileHandler.openFile("");
	if (content != "") {
		ui.textEdit->setText(QString::fromStdString(content));
		statusOutput->showMessage(0, 6);
	}
	else {
		statusOutput->showMessage(0, 5);
	}
}
void MetaAssembler::saveHandler()
{
	clearTable();
	bool saved = false;
	QString filename = QFileDialog::getSaveFileName(this, QFileDialog::tr("Save File"), "", QFileDialog::tr("Cedar Memory file (*.cdm);;MetaAssembler Project (*.MASP);;Text file (*.txt)"));
	if (filename != "") {
		string content = ui.textEdit->toPlainText().toStdString();
		string data = assembler->decode(content);
		if (filename.endsWith("txt") || filename.endsWith("MASP")) {
				saved = fileHandler.saveFile(filename.toUtf8().constData(), content);
		}
		else {
			if (data != "-1") {
				saved = fileHandler.saveFile(filename.toUtf8().constData(), data);
			}
			else {
				saved = false;
			}
		}
	}
	if (!saved) {
		clearTable();
		statusOutput->showMessage(0, 7);
	}
	else {
		statusOutput->showMessage(0, 8);
	}
}

void MetaAssembler::exitHandler()
{
	//check if the user wants to save
	if (QMessageBox::Yes == QMessageBox::question(this, tr("Save"), tr("Do you want to save the project first?"))) {
		saveHandler();
	}
	close();
}

void MetaAssembler::clearStatusHandler()
{
	ui.statusText->clear();
}

void MetaAssembler::cutHandler()
{
	ui.textEdit->cut();

}

void MetaAssembler::copyHandler()
{
	ui.textEdit->copy();
}

void MetaAssembler::pasteHandler()
{
	ui.textEdit->paste();
}

void MetaAssembler::deleteHandler()
{
	ui.textEdit->cut();
}

void MetaAssembler::editorViewHandler()
{
	if (ui.textEdit->isHidden())
		ui.textEdit->show();
	else
		ui.textEdit->hide();
}

void MetaAssembler::tableViewHandler()
{
	if (ui.tableView->isHidden())
		ui.tableView->show();
	else
		ui.tableView->hide();
}

void MetaAssembler::customiseHandler()
{
	bool done;
	QFont font = QFontDialog::getFont(&done, this);
	if (done)
		ui.textEdit->setFont(font);
}

void MetaAssembler::optionsHandler()
{
	Options *w = new Options(this);
	w->exec();
}

void MetaAssembler::helpHandler()
{
	QDesktopServices::openUrl(QUrl("http://mrjester.hapisan.com/04_MC68/"));
}

void MetaAssembler::aboutHandler()
{
	statusOutput->showMessage(0, 10);
}

void MetaAssembler::documentNHandler()
{
	if (QMessageBox::Yes == QMessageBox::question(this, tr("Save"), tr("Do you want to save the project first?"))) {
		saveHandler();
	}
	ui.textEdit->clear();
	ui.statusText->clear();
	clearTable();
}


void MetaAssembler::assemble()
{
	clearTable();
	string content = ui.textEdit->toPlainText().toStdString();
	string data = assembler->decode(content);
	if (data == "-1") {
		clearTable();
	}
}

void MetaAssembler::statusToggle()
{
	if (ui.statusText->isHidden())
		ui.statusText->show();
	else
		ui.statusText->hide();
}
void MetaAssembler::changeEvent(QEvent *event) {
	QWidget::changeEvent(event);
	if (event->type() == QEvent::ActivationChange) {
		if (this->isActiveWindow())
			assembler->reloadSet();
	}

}

void MetaAssembler::clearTable()
{
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 16; j++) {
			cedarTableModel->setItem(i, j, new QStandardItem(""));

		}
	}
}
