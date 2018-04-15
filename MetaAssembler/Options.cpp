#include "Options.h"
#include "FileHandler.h"
#include "qstandarditemmodel.h"
#include <string>
#include "InstructionEditor.h"
using namespace std;

Options::Options(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.addButton, SIGNAL(clicked()), this, SLOT(addHandler()));
	connect(ui.editButton, SIGNAL(clicked()), this, SLOT(editHandler()));
	connect(ui.removeButton, SIGNAL(clicked()), this, SLOT(removeHandler()));
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(okHandler()));

	fileHandler = new FileHandler;
	loadData();
}

Options::~Options()
{
	delete fileHandler;
}

void Options::removeHandler()
{
}

void Options::addHandler()
{
	InstructionEditor *editor = new InstructionEditor();
	editor->show();
}

void Options::okHandler()
{
}

void Options::editHandler()
{
	InstructionEditor *editor = new InstructionEditor();
	editor->show();
}

void Options::loadData()
{
	string instructions = fileHandler->openFile("instructions.txt");
	QStandardItemModel *itemModel = new QStandardItemModel(0, 3, this);
	itemModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Instruction")));
	itemModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Definition")));
	itemModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Operand Size (bytes)")));
	ui.tableView->setModel(itemModel);
}
