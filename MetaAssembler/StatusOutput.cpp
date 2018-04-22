#include "StatusOutput.h"
#include "qtextcursor.h"

using namespace std;

StatusOutput::StatusOutput(QTextEdit * statusText)
{
	//Since there is a lot of error checking in the assembling process, this class was introduced with error codes 
	//This is used to keep the error messages separate from the assembling code and to keep the code cleaner
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
		message = "Could not assemble program... ";
		break;
	case 4:
		message = "Address error at line: " + to_string(lineNumber);
		break;
	case 5:
		message = "Could not open a file...";
		break;
	case 6:
		color = findColor(0);
		message = "Successfully opened a file...";
		break;
	case 7:
		message = "Could not save the file...";
		break;
	case 8:
		color = findColor(0);
		message = "Successfully saved a file...";
		break;
	case 9:
		color = findColor(1);
		message = "Value size warning - value will be cut to a fixed size (16 bits) at line: " + to_string(lineNumber);
		break;
	case 10:
		introMessages();
		break;
	case 11:
		color = findColor(1);
		message = "Warning - Address overflow - Cedar logic won't load anything beyond 0xfff";
		break;
	case 12:
		message = "Too big value at line: " + to_string(lineNumber);
		break;
	}
	//Appending the text as HTML to enable colored messages
	statusText->moveCursor(QTextCursor::End);
	statusText->insertHtml(QString::fromStdString((color + message + html)));
	statusText->moveCursor(QTextCursor::End);
	statusText->ensureCursorVisible();
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
	string message = "Use $ prefix to specify hex values, # or no symbol for decimal values.<br>Instruction list can be edited in options.<br>Supported directive formats:<br>ORG address<br>label EQU constant(dec or hex)/label<br> label DS constant(dec or hex)/label<br> label DC constant(dec or hex)/label<br>";
	statusText->moveCursor(QTextCursor::End);
	statusText->insertHtml(QString::fromStdString((color + message + html)));
	statusText->moveCursor(QTextCursor::End);

}

