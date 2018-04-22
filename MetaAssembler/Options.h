#pragma once
#include <QDialog>
#include "ui_Options.h"
#include "FileHandler.h"
#include "qstandarditemmodel.h"
class Options : public QDialog
{
	Q_OBJECT

public:
	Options(QMainWindow *parent);
	~Options();

private slots:
	void removeHandler();
	void addHandler();
	void okHandler();
	void editHandler();

private:
	void loadData();
	FileHandler *fileHandler;

private:
	Ui::Options ui;
	QStandardItemModel *itemModel;
};
