#include "Assembler.h"
#include <sstream>
using namespace std;

Assembler::Assembler(QTextEdit* statusText)
{
	fileHandler = new FileHandler();
	statusOutput = new StatusOutput(statusText);
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
					//syntax error 
					statusOutput->showMessage(lineCount, 3);
					ready = false;
					break;
				}
				string directive = words[i];
				if (equFlag) {
					if (directive == "EQU") {
						labels.at(labels.size() - 1)->setValue(words[i + 1]);
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
				Label *label = new Label(lineCount, lab, 0, "");
				labels.push_back(label);
			}
			else {
				//Syntax error
				statusOutput->showMessage(lineCount, 3);
				ready = false;
			}

		}
		equFlag = false;
		lineCount++;
	}
	if (ready)
		addressing(text);
	else
		statusOutput->showMessage(-1, 4);
	return false;
}

void Assembler::addressing(string text) {
	int lineCount;
	istringstream stream(text);
	string line;
	int address = 0;
	string output;
	int labelCounter = 0;
	while (getline(stream, line)) {
		istringstream wstream(line);
		vector<string> words{ istream_iterator<string>{wstream}, istream_iterator<string>{} };
		for (int i = 0; i < words.size(); i++) {
			if (isInstruction(words[i])) {
				address++;
			}
			else if (isDirective(words[i])) {
				string directive = words[i];
				if (directive == "ORG") {
					//Setting the address
					int calculatedAddress = calculateAddress(words[i + 1]);
					if (calculatedAddress == -1) {
						//address error
						statusOutput->showMessage(0,0);
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
				labels.at(labelCounter)->setAddress(0);
				labelCounter++;
			}
		}
		statusOutput->showMessage(address, 1);
		lineCount++;
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

int Assembler::calculateAddress(string address)
{
	if (address[0] == '#') {
		//Hex address
		address = address.substr(1, address.size());
		for (int i = 0; i < address.size(); i++) {
			if (!(address[i] >= '0' && address[i] <= '9' || address[i] >= 'A' && address[i] <= 'F')) {
				//Error, invalid address
				return -1;
			}

		}
		return stoul(address, nullptr, 16);
	}
		if (address[0] == '$')
			address = address.substr(1, address.size());

		for (int i = 0; i < address.size(); i++) {
			if (!(address[i] >= '0' && address[i] <= '9')) {
				//Error, invalid address
				return -1;
			}
		}
		return stoi(address);
		return 0;
}

