#pragma once
#include <string>
#include "Label.h"
#include <vector>
#include "ConversionUtils.h"
using namespace std;
class Instruction {
public:
	Instruction(int address, int line, string type, string definition);

	void setValue(string val);
	void setAddress(int mAddress);

	string getValue();
	string getDefinition();
	string decode(vector<Label*> labels, ConversionUtils * cUtils);
	int getLine();
	int getAddress();

private:
	int line;
	int address;
	string type;
	string definition;
	string value;
	vector<Label*> labels;
};