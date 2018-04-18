#pragma once
#include <string>
#include "FileHandler.h"
#include <vector>
#include <map>
#include "qtextedit.h"
#include "Instruction.h"
#include "Directive.h"
#include "Label.h"
using namespace std;

class Assembler {
public:
	Assembler(QTextEdit *statusText);
	bool assemble(string text);

private:
	int position;
	void reloadSet();

	map <string, string> instructionsList;

	FileHandler* fileHandler;
	QTextEdit* statusText;

	bool isDirective(string word);
	bool isInstruction(string word);

	vector <Instruction*> instructions;
	vector<Directive*>	directives;
	vector<Label*>	labels;
};