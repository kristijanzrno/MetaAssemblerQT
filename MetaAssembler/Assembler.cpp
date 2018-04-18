#include "Assembler.h"
#include <sstream>
using namespace std;

Assembler::Assembler(QTextEdit* statusText)
{
	fileHandler = new FileHandler();
	this->statusText = statusText;
	reloadSet();
}

bool Assembler::assemble(string text)
{
	instructions.clear();
	directives.clear();
	labels.clear();
	int lineCount = 0;
	string address;
	istringstream stream(text);
	string line;
	while (getline(stream, line)) {
		istringstream wstream(line);
		vector<string> words{ istream_iterator<string>{wstream}, istream_iterator<string>{} };
		for (int i = 0; i < words.size(); i++) {
			if (isInstruction(words[i])) {
				Instruction *inst = new Instruction(lineCount, words[i], instructionsList[words[i]]);
				if (inst->getDefinition().length() < 3) {
					inst->setValue(words[i + 1]);
				}
				instructions.push_back(inst);
				statusText->append("Definition:");
				statusText->append(QString::fromStdString(inst->getDefinition()));
				statusText->append("Value:");
				statusText->append(QString::fromStdString(inst->getValue()));
				break;
				
			}
			else if (isDirective(words[i])) {
				string directive = words[i];
				string extension = "";
				if (words[i].size() == 4) {
					directive = words[i].substr(0, 2);
					extension = words[i].substr(2, 4);
				}
				Directive *dir = new Directive(lineCount, directive, extension);
				directives.push_back(dir);
				statusText->append("Directive:");
				statusText->append(QString::fromStdString(directive));
				statusText->append(QString::fromStdString(extension));
				break;
			}
			else if (i == 0) {
				Label *label = new Label(lineCount, words[i], address);
				labels.push_back(label);
				statusText->append("Label:");
				statusText->append(QString::fromStdString(words[i]));
				
			}
			else {
				//Unknown error
			}

		}
	}
	return false;
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

	if (word == "org")
		return true;
	
	string dir = word.substr(0, 2);
	string def = word.substr(2, word.size());
	if (dir == "dc" || dir == "ds"){
		if (word.size() == 2) {
			return true;
		}
		else {
			if (def == ".b" || def == ".w" || def == ".l") {
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
