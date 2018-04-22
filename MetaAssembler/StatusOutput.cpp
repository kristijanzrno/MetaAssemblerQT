#include "StatusOutput.h"
#include "qtextcursor.h"
using namespace std;

StatusOutput::StatusOutput(QTextEdit * statusText)
{
	this->statusText = statusText;
	introMessages();
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
		message = "Could not assemble program... ";
		break;
	case 4:
		message = "Address error at line: " + to_string(lineNumber);
		break;

	}
	statusText->textCursor().movePosition(QTextCursor::End);
	statusText->insertHtml(QString::fromStdString((color + message + html)));

}

string StatusOutput::findColor(int code)
{
	switch (code) {
	case 0:
		return "<font color = \"Green\">";
	case 1:
		return "<font color = \"Blue\">";
	case 2:
		return "<font color = \"Red\">";
	}
	return "";
}

void StatusOutput::introMessages()
{
	string html = "</font><br>";
	string color = findColor(0);
	string message = "Use $ prefix to specify hex values, # or no symbol for decimal values.<br>Instruction list can be edited in options.<br>Supported directive formats:<br>ORG address<br>label EQU constant/label<br>";
	statusText->textCursor().movePosition(QTextCursor::End);
	statusText->insertHtml(QString::fromStdString((color + message + html)));
}

