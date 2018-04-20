#pragma once
#include <string>
using namespace std;
class Instruction {
public:
	Instruction(int address, int line, string type, string definition);

	void setValue(string val);
	void setAddress();

	string getValue();
	string getDefinition();
	int getLine();

private:
	int line;
	int address;
	string type;
	string definition;
	string value;
};