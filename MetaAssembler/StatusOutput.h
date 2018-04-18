#pragma once
#include "qtextedit.h"
#include <string>

class StatusOutput {
public:
	StatusOutput(QTextEdit *statusText);
	void showMessage(int line, int code);
private:
	std::string findColor(int code);
	QTextEdit * statusText;
};