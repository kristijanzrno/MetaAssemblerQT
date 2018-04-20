#include "StatusOutput.h"
#include "qtextcursor.h"
using namespace std;

StatusOutput::StatusOutput(QTextEdit * statusText)
{
	this->statusText = statusText;
}

void StatusOutput::showMessage(int line, int code)
{
	int lineNumber = line + 1;
	string html = "</font><br>";
	string color = findColor(2);
	string message;
	switch (code) {
	case 0:
		message = "Syntax error at line: " + to_string(lineNumber);
		break;
	case 1:
		message = "Operand missing at line: " + to_string(lineNumber);
		break;
	case 2:
		message = "Found an unneccesary argument at line: " + to_string(lineNumber);
		break;
	case 3:
		message = "Syntax error at line: " + to_string(lineNumber);
		break;
	}
	statusText->insertHtml(QString::fromStdString((color + message + html)));
	statusText->textCursor().movePosition(QTextCursor::End);

}

string StatusOutput::findColor(int code)
{
	switch (code) {
	case 0:
		return "<font color = \"Lime\">";
	case 1:
		return "<font color = \"Blue\">";
	case 2:
		return "<font color = \"Red\">";
	}
	return "";
}
