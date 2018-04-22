#pragma once
#include <QDialog>
#include "ui_InstructionEditor.h"
#include "qstandarditemmodel.h"
#include "qtableview.h"

class InstructionEditor : public QDialog
{
	Q_OBJECT
public:
	InstructionEditor(QDialog *parent, QStandardItemModel *itemModel, QTableView *tableView, bool edit);
	~InstructionEditor();
private slots:
	void okHandler();
private:
	Ui::InstructionEditor ui;
	QTableView *tableView;
	QStandardItemModel *itemModel;
	void errorMessage(QString text);

	bool edit;
};
