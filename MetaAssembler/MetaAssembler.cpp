#include "MetaAssembler.h"
#include "Options.h"
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
	fileHandler.saveFile();
}

void MetaAssembler::exitHandler()
{
}

void MetaAssembler::reformatSelectionHandler()
{
}

void MetaAssembler::reformatDocumentHandler()
{
}

void MetaAssembler::cutHandler()
{
}

void MetaAssembler::copyHandler()
{
	
}

void MetaAssembler::pasteHandler()
{
}

void MetaAssembler::deleteHandler()
{
}

void MetaAssembler::editorViewHandler()
{
}

void MetaAssembler::tableViewHandler()
{
}

void MetaAssembler::customiseHandler()
{
}

void MetaAssembler::optionsHandler()
{
	Options *w = new Options();
	w->show();
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
