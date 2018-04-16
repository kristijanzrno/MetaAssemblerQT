#pragma once

#include <QDialog>
#include "ui_InstructionEditor.h"

class InstructionEditor : public QDialog
{
	Q_OBJECT

public:
	InstructionEditor(QWidget *parent = Q_NULLPTR);
	~InstructionEditor();

private:
	Ui::InstructionEditor ui;
};
