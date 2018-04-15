#pragma once

#include <QWidget>
#include "ui_InstructionEditor.h"

class InstructionEditor : public QWidget
{
	Q_OBJECT

public:
	InstructionEditor(QWidget *parent = Q_NULLPTR);
	~InstructionEditor();

private:
	Ui::InstructionEditor ui;
};
