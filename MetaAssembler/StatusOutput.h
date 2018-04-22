#pragma once
#include <string>
#include "qtextedit.h"
using namespace std;

class StatusOutput {
public:
	StatusOutput(QTextEdit *statusText);
	void showMessage(int line, int code);
private:
	string findColor(int code);
	QTextEdit * statusText;
	void introMessages();
};