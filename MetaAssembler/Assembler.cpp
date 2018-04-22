#include "Assembler.h"
#include <sstream>
using namespace std;

Assembler::Assembler(QTextEdit* statusText, QStandardItemModel* itemModel)
{
	fileHandler = new FileHandler();
	statusOutput = new StatusOutput(statusText);
	cUtils = new ConversionUtils();

	this->itemModel = itemModel;
	this->sText = statusText;
	reloadSet();
}

string Assembler::decode(string text)
{
	if (text == "")
		return "";

	transform(text.begin(), text.end(), text.begin(), ::toupper);

	instructions.clear();
	directives.clear();
	labels.clear();

	int lineCount = 0;
	int address = 0;
	bool equFlag = false;
	bool ready = true;

	istringstream stream(text);
	string line;

	while (getline(stream, line)) {
		istringstream wstream(line);
		vector<string> words{ istream_iterator<string>{wstream}, istream_iterator<string>{} };

		for (int i = 0; i < words.size(); i++) {

			if (isInstruction(words[i])) {
				Instruction *inst = new Instruction(address, lineCount, words[i], instructionsList[words[i]]);
				if (inst->getDefinition().length() < 3) {
					if (!(i == words.size() - 1)) {
						if (i + 1 == words.size() - 1) {
							if (words[i + 1].size() < 8) {
								//Success
								inst->setValue(words[i + 1]);
							}
							else {
								//Too big value
								statusOutput->showMessage(lineCount, 12);
								ready = false;
							}
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
				if (words.size() - 1 != i + 1) {
					//Syntax error 
					statusOutput->showMessage(lineCount, 0);
					ready = false;
					break;
				}
				string directive = words[i];
				if (equFlag) {
					if (directive == "EQU") {
						if (words[i + 1].size() < 8) {
							statusOutput->showMessage(lineCount, 12);
							ready = false;
							break;
						}
						int value = cUtils->toInt(words[i + 1]);
						if (value != INT_MIN) {
							labels.at(labels.size() - 1)->setValue(value);
						}
						else {
							bool usingLabel = false;
							for (int j = 0; j < labels.size(); j++) {
								if (words[i + 1] == labels.at(j)->getText()) {
									usingLabel = true;
									if (labels.at(j)->getValue() != INT_MIN) {
										labels.at(labels.size() - 1)->setValue(labels.at(j)->getValue());
									}
								}
							}
							if (!usingLabel) {
								//Invalid syntax
								statusOutput->showMessage(lineCount, 0);
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
				statusOutput->showMessage(lineCount, 0);
				ready = false;
			}

		}
		equFlag = false;
		lineCount++;
	}
	if (ready)
		return addressing(text);
	else
		statusOutput->showMessage(0, 3);
	return "-1";
}

string Assembler::addressing(string text) {

	int lineCount = 0;
	int address = 0;
	int labelCounter = 0;
	int instructionCounter = 0;

	bool ready = true;
	bool equFlag = false;

	istringstream stream(text);
	string line;
	
	
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
					if (words[i + 1].size() > 8) {
						statusOutput->showMessage(lineCount, 12);
						ready = false;
						break;
					}
					if (words.size() != i + 1)
						if (words[i + 1] == "EQU")
							equFlag = true;
					int calculatedAddress = cUtils->toInt(words[i + 1]);
					if (calculatedAddress == INT_MIN) {
						//Address error
						statusOutput->showMessage(lineCount, 4);
						ready = false;
					}
					else {
						address = calculatedAddress;
					}
				}
				else if (directive == "EQU") {
					if (equFlag) {
						if (labels.at(labelCounter - 1)->getValue() == INT_MIN) {
							for (int j = 0; j < labels.size(); j++) {
								if (words[i + 1] == labels.at(j)->getText()) {
									labels.at(labelCounter - 1)->setValue(labels.at(j)->getAddress());
								}
							}
						}
					}
				}
				else {
					//Value size check
					if (words[i + 1].size() > 8) {
						statusOutput->showMessage(lineCount, 12);
						ready = false;
						break;
					}
					Directive *dir = new Directive(address, lineCount, directive, words[i + 1]);
					directives.push_back(dir);
					int moveTo = dir->getSpace(labels, cUtils);
					if (moveTo != INT_MIN) {
						address += moveTo;
					}
					else {
						statusOutput->showMessage(lineCount, 0);
						ready = false;
						break;
					}
				}
			}
			else if (i == 0) {
				if(words.size() != i+1)
					if (words[i + 1] == "EQU")
						equFlag = true;
				labels.at(labelCounter)->setAddress(address);
				labelCounter++;
			}
		}
		lineCount++;
		equFlag = false;
	}
	//Checking for address overflow
	if (address > 4096)
		statusOutput->showMessage(0, 11);

	if (ready)
		return assembling();
	else
		//error message
		statusOutput->showMessage(0, 3);

	return "-1";
}

string Assembler::assembling()
{
	string output;
	stringstream stream;
	stream << "# Instructions\n";
	for (int i = 0; i < instructions.size(); i++) {
		string value = "";
		if (instructions.at(i)->getDefinition().size() != 4)
			value = instructions.at(i)->decode(labels, cUtils);
		if (value == "**") {
			//Syntax error
			statusOutput->showMessage(0, 3);
			statusOutput->showMessage(instructions.at(i)->getLine(), 0);
			return "-1";
		}
		else {
			if (value[0] == '&') {
				statusOutput->showMessage(instructions.at(i)->getLine(), 9);
				value = value.substr(1, value.size());
			}
			int address = instructions.at(i)->getAddress();
			string val = instructions.at(i)->getDefinition() + value;
			stream << hex << address << " : " << val << endl;
			itemModel->setItem((address / 16), (address % 16), new QStandardItem(QString::fromStdString(val)));

		}
	}
	stream << "\n# Directives\n";
	for (int i = 0; i < directives.size(); i++) {
		string value = directives.at(i)->getDefinition();
		if (directives.at(i)->getType() == "DC") {
			if (value[0] == '&') {
				statusOutput->showMessage(directives.at(i)->getLine(), 9);
				value = value.substr(1, value.size());
			}
			int address = directives.at(i)->getAddress();
			stream << hex << address << " : " << value << endl;
			itemModel->setItem((address / 16), (address % 16), new QStandardItem(QString::fromStdString(value)));

		}
	}
	output = stream.str();
	sText->append(QString::fromStdString("Output:"));
	sText->append(QString::fromStdString(stream.str()));
	sText->ensureCursorVisible();
	return output;

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

	if (word == "DC" || word == "DS") {
		return true;
	}
	return false;
}

bool Assembler::isInstruction(string word)
{
	return instructionsList.count(word);
}

