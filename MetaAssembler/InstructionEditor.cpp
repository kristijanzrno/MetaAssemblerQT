#include "InstructionEditor.h"
#include <QMessageBox>
#include <string>
using namespace std;


InstructionEditor::InstructionEditor(QDialog *parent, QStandardItemModel *itemModel, QTableView *tableView, bool edit)
	: QDialog(parent)
{
	//This class is used to handle the instruction editor window and to edit the instructions from Options

	ui.setupUi(this);

	this->tableView = tableView;
	this->itemModel = itemModel;
	this->edit = edit;

	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(okHandler()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(close()));

	ui.opSize->setCurrentIndex(0);
	//Seting UI values according to the selected instruction
	if (edit) {
		QModelIndex selectedIndex = tableView->selectionModel()->selectedIndexes()[0];
		int row = selectedIndex.row();
		int column = selectedIndex.column();
		ui.instructionText->setText(itemModel->data(itemModel->index(row, 0), Qt::DisplayRole).toString());
		ui.definitionText->setText(itemModel->data(itemModel->index(row, 1), Qt::DisplayRole).toString());
		ui.opSize->setCurrentText(itemModel->data(itemModel->index(row, 2), Qt::DisplayRole).toString());
	}

}

InstructionEditor::~InstructionEditor()
{
}

void InstructionEditor::okHandler()
{
	int row = 0;
	if (edit) {
		QModelIndex selectedIndex = tableView->selectionModel()->selectedIndexes()[0];
		row = selectedIndex.row();
	}
	//Checking fields
	if (ui.definitionText->text() == "" || ui.instructionText->text() == "") {
		errorMessage("This instruction/definition cannot be empty.");
		return;
	}
	//Checking definition
	string definition = ui.definitionText->text().toStdString();
	for (char& c : definition) {
		if (c >= '0' && c <= '9' || c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F') {
			continue;
		}
		errorMessage("The definition characters must be in hex range(0-F).");
		return;
	}

	int numberOfItems = itemModel->rowCount();
	for (int i = 0; i < numberOfItems; i++) {
		//Checking if instruction already exists
		if (ui.instructionText->text() == itemModel->data(itemModel->index(i, 0), Qt::DisplayRole).toString()) {
			if (!(edit && (row == i))) {
				errorMessage("This instruction already exists.");
				return;
			}
		}
		//Checking if definition already exists
		if (ui.definitionText->text() == itemModel->data(itemModel->index(i, 1), Qt::DisplayRole).toString()) {
			if (!(edit && (row == i))) {
				errorMessage("This definition already exists.");
				return;
			}
		}
	}
	//Checking the instruction size
	if (ui.definitionText->text().count() + ui.opSize->currentIndex() != 4) {
		errorMessage("Instruction definition + Operand size must equal 4");
		return;
	}
	int indexToEdit;
	if (edit) {
		indexToEdit = row;
	}
	else {
		indexToEdit = numberOfItems;
		itemModel->appendRow(new QStandardItem(QString("")));
	}
	//Saving the instruction as new one or at selected row (edit)
	itemModel->setItem(indexToEdit, 0, new QStandardItem(ui.instructionText->text()));
	itemModel->setItem(indexToEdit, 1, new QStandardItem(ui.definitionText->text()));
	itemModel->setItem(indexToEdit, 2, new QStandardItem(ui.opSize->currentText()));
	close();
}

void InstructionEditor::errorMessage(QString text)
{
	QMessageBox message;
	message.setWindowTitle("Error");
	message.setText(text);
	message.exec();
}
