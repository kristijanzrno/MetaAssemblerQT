#pragma once
#include <string>
#include "FileHandler.h"
#include <vector>
#include <map>
#include "qtextedit.h"
#include "Instruction.h"
#include "Directive.h"
#include "Label.h"
#include "StatusOutput.h"
using namespace std;

class Assembler {
public:
	Assembler(QTextEdit *statusText);
	bool decode(string text);

private:
	int position;
	void addressing(string text);
	void reloadSet();

	map <string, string> instructionsList;

	FileHandler* fileHandler;
	
	StatusOutput* statusOutput;
	bool isDirective(string word);
	bool isInstruction(string word);

	int calculateAddress(string address);

	vector <Instruction*> instructions;
	vector <Directive*>	directives;
	vector <Label*>	labels;
};