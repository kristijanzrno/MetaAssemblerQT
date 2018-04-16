#include "Options.h"
#include "FileHandler.h"
#include "qstandarditemmodel.h"
#include <string>
#include <sstream>
#include "InstructionEditor.h"
#include <iostream>
#include <fstream>
using namespace std;

Options::Options(QMainWindow *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.addButton, SIGNAL(clicked()), this, SLOT(addHandler()));
	connect(ui.editButton, SIGNAL(clicked()), this, SLOT(editHandler()));
	connect(ui.removeButton, SIGNAL(clicked()), this, SLOT(removeHandler()));
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(okHandler()));

	itemModel = new QStandardItemModel(0, 3, this);
	itemModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Instruction")));
	itemModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Definition")));
	itemModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Operand Size (bytes)")));

	fileHandler = new FileHandler;
	loadData();
}

Options::~Options()
{
	delete fileHandler;
}

void Options::removeHandler()
{
	//Selection mode is "Single Selection" -> Only one selected index (0) 
	QModelIndex selectedIndex = ui.tableView->selectionModel()->selectedIndexes()[0];
	itemModel->removeRow(selectedIndex.row());
}

void Options::addHandler()
{
	InstructionEditor *editor = new InstructionEditor(this, itemModel, ui.tableView, false);
	editor->exec();
}

void Options::okHandler()
{
	int numberOfItems = itemModel->rowCount();
	string instructions;
	for (int i = 0; i < numberOfItems; i++) {
		for (int j = 0; j < 3; j++) {
			instructions += itemModel->data(itemModel->index(i,j), Qt::DisplayRole).toString().toUtf8().constData();
			if(j!=2)
				instructions += "\t";
		}
		instructions += "\n";
	}
	fileHandler->saveFile("inst.txt", instructions);
}

void Options::editHandler()
{
	InstructionEditor *editor = new InstructionEditor(this, itemModel, ui.tableView, true);
	editor->exec();
}

void Options::loadData()
{
	int instructionCount = 0;
	string instructions = fileHandler->openFile("inst.txt");
	istringstream stream(instructions);
	string line;
	while (getline(stream, line)) {
		istringstream wstream(line);
		itemModel->appendRow(new QStandardItem(QString("")));
		int wordCount = 0;
		for (string word; wstream >> word;) {
			QStandardItem *data = new QStandardItem(QString(word.c_str()));
			itemModel->setItem(instructionCount, wordCount, data);
			wordCount++;
		}
		instructionCount++;
	}
	ui.tableView->setModel(itemModel);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}