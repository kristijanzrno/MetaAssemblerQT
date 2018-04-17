#pragma once
#include <string>
#include "FileHandler.h"
#include <vector>
using namespace std;

class Assembler {
public:
	Assembler(string text);
private:
	string text;
	int position;
	bool assemble();
	void reloadSet();
	vector<string> instructions;
	vector<string> definitions;
	FileHandler* fileHandler;
};