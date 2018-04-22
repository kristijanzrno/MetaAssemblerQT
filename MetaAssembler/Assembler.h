#pragma once
#include <string>
#include <vector>
#include <map>
#include "FileHandler.h"
#include "Instruction.h"
#include "Directive.h"
#include "Label.h"
#include "StatusOutput.h"
#include "ConversionUtils.h"
#include "qtextedit.h"
#include "qstandarditemmodel.h"

using namespace std;

class Assembler {
public:
	Assembler(QTextEdit* statusText, QStandardItemModel* itemModel);

	string decode(string text);
	void reloadSet();

private:
	int position;
	string addressing(string text);
	string assembling();

	map <string, string> instructionsList;

	FileHandler* fileHandler;
	ConversionUtils* cUtils;
	QStandardItemModel* itemModel;
	StatusOutput* statusOutput;

	bool isDirective(string word);
	bool isInstruction(string word);

	QTextEdit* sText;
	vector <Instruction*> instructions;
	vector <Directive*>	directives;
	vector <Label*>	labels;
};