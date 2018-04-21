#pragma once
#include <string>
#include "Label.h"
#include <vector>

using namespace std;
class Instruction {
public:
	Instruction(int address, int line, string type, string definition, vector<Label*> labels);

	void setValue(string val);
	void setAddress(int mAddress);

	string getValue();
	string getDefinition();
	string decode();
	int getLine();

private:
	int validData();
	int line;
	int address;
	string type;
	string definition;
	string value;
	vector<Label*> labels;
};