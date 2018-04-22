#include "Assembler.h"
#include <sstream>
using namespace std;

Assembler::Assembler(QTextEdit* statusText)
{
	fileHandler = new FileHandler();
	statusOutput = new StatusOutput(statusText);
	this->sText = statusText;
	cUtils = new ConversionUtils();
	reloadSet();
}

bool Assembler::decode(string text)
{
	instructions.clear();
	directives.clear();
	labels.clear();
	int lineCount = 0;
	int address = 0;
	transform(text.begin(), text.end(), text.begin(), ::toupper);
	istringstream stream(text);
	string line;
	bool equFlag;
	bool ready = true;
	while (getline(stream, line)) {
		istringstream wstream(line);
		vector<string> words{ istream_iterator<string>{wstream}, istream_iterator<string>{} };
		for (int i = 0; i < words.size(); i++) {
			if (isInstruction(words[i])) {
				Instruction *inst = new Instruction(address, lineCount, words[i], instructionsList[words[i]]);
				if (inst->getDefinition().length() < 3) {
					if (!(i == words.size() - 1)) {
						if (i + 1 == words.size() - 1) {
							//Success
							inst->setValue(words[i + 1]);
						}
						else {
							//Too many arguments
							statusOutput->showMessage(lineCount, 0);
							ready = false;
						}
					}
					else {
						//Operand missing
						statusOutput->showMessage(lineCount, 1);
						ready = false;
					}
				}
				else {
					if (i < words.size() - 1) {
						//Unnecessary argument
						statusOutput->showMessage(lineCount, 2);
						ready = false;
					}

				}
				instructions.push_back(inst);
				break;
			}
			else if (isDirective(words[i])) {
				if (words.size()-1 != i+1) {
					//Syntax error 
					statusOutput->showMessage(lineCount, 2);
					ready = false;
					break;
				}
				string directive = words[i];
				if (equFlag) {
					if (directive == "EQU") {
						int value = cUtils->toInt(words[i + 1]);
						if (value != INT_MIN) {
							labels.at(labels.size() - 1)->setValue(value);
						}
						else {
							bool usingLabel = false;
							for (int j = 0; j < labels.size(); j++) {
								if (words[i + 1] == labels.at(j)->getText()) {
									usingLabel = true;
									if (labels.at(j)->getValue() == INT_MIN) {
										labels.at(labels.size() - 1)->setValue(labels.at(j)->getAddress());
									}
									else {
										labels.at(labels.size() - 1)->setValue(labels.at(j)->getValue());
									}
								}
							}
							if (!usingLabel) {
								//Invalid syntax
								statusOutput->showMessage(lineCount, 3);
								ready = false;
							}
						}
						break;
					}
				}

				break;
			}
			else if (i == 0) {
				string lab = words[i];
				if (lab[lab.size() - 1] == ':') {
					lab = lab.substr(0, lab.size() - 1);
				}
				equFlag = true;
				Label *label = new Label(lineCount, lab, 0, INT_MIN);
				labels.push_back(label);
			}
			else {
				//Syntax error
				statusOutput->showMessage(lineCount, 2);
				ready = false;
			}

		}
		equFlag = false;
		lineCount++;
	}
	if (ready)
		addressing(text);
	else
		statusOutput->showMessage(3, 0);
	return false;
}

void Assembler::addressing(string text) {
	int lineCount = 0;
	istringstream stream(text);
	string line;
	int address = 0;
	int labelCounter = 0;
	int instructionCounter = 0;
	bool ready = true;
	while (getline(stream, line)) {
		istringstream wstream(line);
		vector<string> words{ istream_iterator<string>{wstream}, istream_iterator<string>{} };
		for (int i = 0; i < words.size(); i++) {
			if (isInstruction(words[i])) {
				instructions.at(instructionCounter)->setAddress(address);
				instructionCounter++;
				address++;
			}
			else if (isDirective(words[i])) {
				string directive = words[i];
				if (directive == "ORG") {
					//Setting the address
					int calculatedAddress = cUtils->toInt(words[i + 1]);
					if (calculatedAddress == INT_MIN) {
						//address error
						statusOutput->showMessage(lineCount, 4);
						ready = false;
					}
					else {
						address = calculatedAddress;
					}
				}
				else {
					string extension = "";
					if (words[i].size() == 4) {
						directive = words[i].substr(0, 2);
						extension = words[i].substr(2, 4);
					}
					Directive *dir = new Directive(address, lineCount, directive, extension, words[i + 1]);
					directives.push_back(dir);
					address += dir->getSpace();
				}
			}
			else if (i == 0) {
				labels.at(labelCounter)->setAddress(address);
				labelCounter++;
			}
		}
		lineCount++;
	}
	if (ready)
		assembling();
	else
		//error message
		statusOutput->showMessage(0,3);
}
void Assembler::assembling()
{
	string output;
	for (int i = 0; i < instructions.size(); i++) {
		string value = instructions.at(i)->decode(labels, cUtils);
		if (value == "**") {
			statusOutput->showMessage(0,3);
			statusOutput->showMessage(instructions.at(i)->getLine(), 0);
		}

	}
}
void Assembler::reloadSet()
{
	instructionsList.clear();
	string loadedInst = fileHandler->openFile("inst.txt");
	istringstream stream(loadedInst);
	string line;
	while (getline(stream, line)) {
		istringstream wstream(line);
		int wordCount = 0;
		string instruction;
		for (string word; wstream >> word;) {
			if (wordCount == 0) {
				instruction = word;
			}
			else if (wordCount == 1) {
				instructionsList.insert(make_pair(instruction, word));
			}
			wordCount++;
		}
	}
}

bool Assembler::isDirective(string word)
{
	if (word.size() < 2)
		return false;

	if (word == "ORG" || word == "EQU")
		return true;

	string dir = word.substr(0, 2);
	string def = word.substr(2, word.size());
	if (dir == "DC" || dir == "DS") {
		if (word.size() == 2) {
			return true;
		}
		else {
			if (def == ".N" || def == ".W" || def == ".L") {
				return true;
			}
		}
	}
	return false;
}

bool Assembler::isInstruction(string word)
{
	return instructionsList.count(word);
}

