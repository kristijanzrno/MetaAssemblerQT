#include "InstructionEditor.h"
#include <QMessageBox>
InstructionEditor::InstructionEditor(QDialog *parent, QStandardItemModel *itemModel, QTableView *tableView, bool edit)
	: QDialog(parent)
{
	ui.setupUi(this);

	this->tableView = tableView;
	this->itemModel = itemModel;
	this->edit = edit;

	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(okHandler()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	ui.opSize->setCurrentIndex(0);
	if (edit) {
		QModelIndex selectedIndex = tableView->selectionModel()->selectedIndexes()[0];
		int row = selectedIndex.row();
		int column = selectedIndex.column();
		ui.instructionText->setText(itemModel->data(itemModel->index(row,0), Qt::DisplayRole).toString());
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
	//Security checks
	int numberOfItems = itemModel->rowCount();
	for (int i = 0; i < numberOfItems; i++) {
		//Checking if instruction already exists
		if (ui.instructionText->text() == itemModel->data(itemModel->index(i, 0), Qt::DisplayRole).toString()) {
			if (!edit && !(row == i)) {
				errorMessage("This instruction/definition already exists.");
				return;
			}
		}
		//Checking if definition already exists
		if (ui.definitionText->text() == itemModel->data(itemModel->index(i, 1), Qt::DisplayRole).toString()) {
			if (!edit && !(row == i)) {
				errorMessage("This instruction/definition already exists.");
				return;
			}
		}
	}
	//Checking the instruction size
	if (ui.definitionText->text().count() + ui.opSize->currentIndex() > 4) {
		errorMessage("Instruction definition exceeds maximum size.");
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
