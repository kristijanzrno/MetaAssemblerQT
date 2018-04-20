#include "MetaAssembler.h"
#include "Options.h"
#include <sstream>
#include "qfontdialog.h"
using namespace std;

MetaAssembler::MetaAssembler(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(documentNHandler()));
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openHandler()));
	connect(ui.actionSave_As, SIGNAL(triggered()), this, SLOT(saveHandler()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(exitHandler()));
	connect(ui.actionSelection, SIGNAL(triggered()), this, SLOT(reformatSelectionHandler()));
	connect(ui.actionDocument, SIGNAL(triggered()), this, SLOT(reformatDocumentHandler()));
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

	assembler = new Assembler(ui.statusText);
	//Populating the tableView
	cedarTableModel = new QStandardItemModel(256, 16, this);

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
}

void MetaAssembler::openHandler()
{
	string content = fileHandler.openFile("");
	if (content != "") {
		ui.textEdit->setText(QString::fromStdString(content));
	}
	else {
		//errorMessage("");
	}
}

void MetaAssembler::saveHandler()
{
	fileHandler.saveFile("","");
}

void MetaAssembler::exitHandler()
{
	//check if the user wants to save
	close();
}

void MetaAssembler::reformatSelectionHandler()
{
}

void MetaAssembler::reformatDocumentHandler()
{
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
}

void MetaAssembler::aboutHandler()
{
}

void MetaAssembler::documentNHandler()
{
}


void MetaAssembler::assemble()
{
	string content = ui.textEdit->toPlainText().toStdString();
	assembler->decode(content);
}

void MetaAssembler::statusToggle()
{
	if (ui.statusText->isHidden())
		ui.statusText->show();
	else
		ui.statusText->hide();
}
