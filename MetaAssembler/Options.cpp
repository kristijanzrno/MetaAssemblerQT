#include "Options.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "FileHandler.h"
#include "InstructionEditor.h"
#include "qstandarditemmodel.h"
#include "qmessagebox.h"
using namespace std;

Options::Options(QMainWindow *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//This class is used to edit the instructions list 

	connect(ui.addButton, SIGNAL(clicked()), this, SLOT(addHandler()));
	connect(ui.editButton, SIGNAL(clicked()), this, SLOT(editHandler()));
	connect(ui.removeButton, SIGNAL(clicked()), this, SLOT(removeHandler()));
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(okHandler()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(close()));

	//Creating the tableview model
	itemModel = new QStandardItemModel(0, 3, this);
	itemModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Instruction")));
	itemModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Definition")));
	itemModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Operand Size (characters)")));

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
	//Using instruction editor to add an instruction
	InstructionEditor *editor = new InstructionEditor(this, itemModel, ui.tableView, false);
	editor->exec();
}

void Options::okHandler()
{
	//Saving instructions to the file after the editing is done
	int numberOfItems = itemModel->rowCount();
	string instructions;
	for (int i = 0; i < numberOfItems; i++) {
		for (int j = 0; j < 3; j++) {
			instructions += itemModel->data(itemModel->index(i, j), Qt::DisplayRole).toString().toUtf8().constData();
			if (j != 2)
				instructions += "\t";
		}
		instructions += "\n";
	}
	fileHandler->saveFile("instructions.txt", instructions);
	close();

}

void Options::editHandler()
{
	//If nothing is selected no row can be edited
	QModelIndexList selectedIndex = ui.tableView->selectionModel()->selectedIndexes();
	if (selectedIndex.isEmpty()) {
		QMessageBox message;
		message.setWindowTitle("Error");
		message.setText("Please select an instruction.");
		message.exec();
	}
	else {
		InstructionEditor *editor = new InstructionEditor(this, itemModel, ui.tableView, true);
		editor->exec();
	}
}

void Options::loadData()
{
	//Loading data to a string from instructions file using the FileHandler
	int instructionCount = 0;
	string instructions = fileHandler->openFile("instructions.txt");
	istringstream stream(instructions);
	string line;
	while (getline(stream, line)) {
		istringstream wstream(line);
		itemModel->appendRow(new QStandardItem(QString("")));
		int wordCount = 0;
		for (string word; wstream >> word;) {
			//Passing data to the tableview
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