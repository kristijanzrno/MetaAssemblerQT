#pragma once
#include <QWidget>
#include "ui_Options.h"
#include "FileHandler.h"

class Options : public QWidget
{
	Q_OBJECT

public:
	Options(QWidget *parent = Q_NULLPTR);
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
};
