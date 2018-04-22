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
	//First step in program assembling
	//This function decodes all the instructions and labels and puts them in their vectors
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
		vector<string> words{ istream_iterator<string>{wstream}, istream_iterator<string>{}};
		for (int i = 0; i < words.size(); i++) {
			if (isInstruction(words[i])) {
				//Instruction found, proceed to error checking
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
				//Place the created instruction in the vector
				instructions.push_back(inst);
				break;
			}
			else if (isDirective(words[i])) {
				//Found a directive
				//Proceed to error checking
				if (words.size() - 1 != i + 1) {
					//Syntax error 
					statusOutput->showMessage(lineCount, 0);
					ready = false;
					break;
				}
				string directive = words[i];
				if (equFlag) {
					if (directive == "EQU") {
						if (words[i + 1].size() > 8) {
							//Too big value
							statusOutput->showMessage(lineCount, 12);
							ready = false;
							break;
						}
						int value = cUtils->toInt(words[i + 1]);
						//Check if value is proper number
						if (value != INT_MIN) {
							labels.at(labels.size() - 1)->setValue(value);
						}
						else {
							//If it's not a proper number, check if it's one of the labels
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
				//Labels will always be on index 0
				string lab = words[i];
				//Remove ':' from label if it's existing
				if (lab[lab.size() - 1] == ':') {
					lab = lab.substr(0, lab.size() - 1);
				}
				equFlag = true;
				//Create a new label with it's data
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
	//If all error checks have passed, go to the next stage
	if (ready)
		return addressing(text);
	else
		statusOutput->showMessage(0, 3);
	//If there are some errors with the code, assembler wont proceed to the stage 2(addressing)
	return "-1";
}

string Assembler::addressing(string text) {
	
	//This is the second stage of the assembling process
	//In this section we are giving each instruction it's address
	//We are also considering ORG, EQU, DC, DS directives 
	//DS directive spaces will be processed here

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
		vector<string> words{istream_iterator<string>{wstream}, istream_iterator<string>{}};
		for (int i = 0; i < words.size(); i++) {
			if (isInstruction(words[i])) {
				//Instructions are fixed length and we'll increase the address by 1
				instructions.at(instructionCounter)->setAddress(address);
				instructionCounter++;
				address++;
			}
			else if (isDirective(words[i])) {
				//Value size check
				if (words[i + 1].size() > 8) {
					//Too big value
					statusOutput->showMessage(lineCount, 12);
					ready = false;
					break;
				}
				string directive = words[i];
				//Processing directives
				if (directive == "ORG") {
					//Setting the address
					int calculatedAddress = cUtils->toInt(words[i + 1]);
					if (calculatedAddress == INT_MIN) {
						//ORG can't take labels so if the address is not valid we'll get an error
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
					//Create an DC/DS directive and put it in the vector
					Directive *dir = new Directive(address, lineCount, directive, words[i + 1]);
					directives.push_back(dir);
					//Calculate the space that directive occupies (DC - 1; DS - *)
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
				//Addressing label
				if (words.size() != i + 1)
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
	//4096 is max dec address in CedarLogic
	if (address > 4096)
		statusOutput->showMessage(0, 11);

	//If there are no errors, proceed to the last stage
	if (ready)
		return assembling();
	else
		//error message
		statusOutput->showMessage(0, 3);

	//Return error code "-1"
	return "-1";
}

string Assembler::assembling()
{
	//Last stage of assembling process
	//Fetch all instructions and calculate their values

	string output;
	stringstream stream;

	stream << "# Instructions\n";
	for (int i = 0; i < instructions.size(); i++) {
		//Listing all instructions and appending them to the stream one by one
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
			//& indicator is used to indicate value overflow and show the warning message
			if (value[0] == '&') {
				statusOutput->showMessage(instructions.at(i)->getLine(), 9);
				value = value.substr(1, value.size());
			}
			int address = instructions.at(i)->getAddress();
			string val = instructions.at(i)->getDefinition() + value;
			stream << hex << address << " : " << val << endl;
			//Putting the value in the cedar logic table too
			itemModel->setItem((address / 16), (address % 16), new QStandardItem(QString::fromStdString(val)));

		}
	}
	stream << "\n# Directives\n";
	for (int i = 0; i < directives.size(); i++) {
		//Listing all directives and appending them to the stream one by one
		string value = directives.at(i)->getDefinition();
		if (directives.at(i)->getType() == "DC") {
			//DS directives dont contain any data so we are processing only DC ones
			if (value[0] == '&') {
				statusOutput->showMessage(directives.at(i)->getLine(), 9);
				value = value.substr(1, value.size());
			}
			int address = directives.at(i)->getAddress();
			stream << hex << address << " : " << value << endl;
			//Adding the value to table view
			itemModel->setItem((address / 16), (address % 16), new QStandardItem(QString::fromStdString(value)));

		}
	}
	output = stream.str();
	sText->append(QString::fromStdString("Output:"));
	sText->append(QString::fromStdString(stream.str()));
	sText->ensureCursorVisible();
	//String output has been built, can be stored in a file (saving)
	return output;

}

void Assembler::reloadSet()
{
	//Using the filehandler class to catch all instructions
	//instructions need to be reloaded during the runtime if user edits them in options

	instructionsList.clear();
	string loadedInst = fileHandler->openFile("instructions.txt");
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
	//Checking if word is directive

	if (word == "ORG" || word == "EQU")
		return true;

	if (word == "DC" || word == "DS") {
		return true;
	}
	return false;
}

bool Assembler::isInstruction(string word)
{
	//Checking if word is instruction
	return instructionsList.count(word);
}

