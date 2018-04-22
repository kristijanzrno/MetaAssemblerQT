#pragma once
#include <string>
#include <vector>
#include "Label.h"
#include "ConversionUtils.h"
using namespace std;
class Instruction {
public:
	Instruction(int address, int line, string type, string definition);

	void setValue(string val);
	void setAddress(int mAddress);

	string decode(vector<Label*> labels, ConversionUtils * cUtils);

	string getValue();
	string getDefinition();
	int getLine();
	int getAddress();

private:
	int line;
	int address;
	string type;
	string definition;
	string value;
};