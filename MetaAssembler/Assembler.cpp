#include "Assembler.h"
#include <sstream>
using namespace std;

Assembler::Assembler(string text)
{
	this->text = text;
	fileHandler = new FileHandler();
}

bool Assembler::assemble()
{
	int lineCount = 0;
	istringstream stream(text);
	string line;
	while (getline(stream, line)) {
		istringstream wstream(line);
		int wordIndex = 0;
		int wordCount = 0;
		for (string word; wstream >> word;) {
			wordCount++;
			if (wordIndex == 0 || wordIndex == 1) {
				if (find(instructions.begin(), instructions.end(), word) != instructions.end()) {

				}
			}
			wordIndex++;
		}
		lineCount++;
	}
	return false;
}

void Assembler::reloadSet()
{
	instructions.clear();
	definitions.clear();
	string loadedInst = fileHandler->openFile("inst.txt");
	istringstream stream(loadedInst);
	string line;
	while (getline(stream, line)) {
		istringstream wstream(line);
		int wordCount = 0;
		for (string word; wstream >> word;) {
			if (wordCount == 0) {
				instructions.push_back(word);
			}
			else if (wordCount == 1) {
				definitions.push_back(word);
			}
			wordCount++;
		}
	}
}
