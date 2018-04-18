#pragma once
#include <string>
using namespace std;
class Instruction {
public:
	Instruction(int line, string type, string definition);

	void setValue(string val);
	void setAddress();

	string getValue();
	string getDefinition();
	int getLine();

private:
	int line;
	string type;
	string definition;
	string value;
};