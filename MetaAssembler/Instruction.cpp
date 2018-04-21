#include "Instruction.h"
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

Instruction::Instruction(int address, int line, string type, string definition, vector<Label*> labels)
{
	this->type = type;
	this->definition = definition;
	this->address = address;
	this->labels = labels;
}

void Instruction::setValue(string val)
{
	value = val;
}

void Instruction::setAddress(int mAddress)
{
	address = mAddress;
}

string Instruction::getValue()
{
	return value;
}

string Instruction::getDefinition()
{
	return definition;
}

int Instruction::getLine()
{
	return 0;
}

string Instruction::decode()
{
	int definition = validData();
	bool valid;
	if (definition != -1) {
		
	}
	else {
		for (int i = 0; i < labels.size(); i++) {
			if (value == labels.at(i)->getText()) {
				int val;
				if (labels.at(i)->getValue() == INT_MIN)
					val = labels.at(i)->getAddress();
				else 
					val = labels.at(i)->getValue();
				stringstream stream;
				stream << hex << labels.at(i)->getAddress();
				value = stream.str();
			}
		}
	}
	return string();
}

int Instruction::validData()
{
	if (value[0] == '$') {
		value = value.substr(1, value.size());
		for (int i = 0; i < value.size(); i++) {
			if (!(value[i] >= '0' && value[i] <= '9' || value[i] >= 'A' && value[i] <= 'F')) {
				return -1;
			}
		}
		return stoul(value, nullptr, 16);
	}
	if (value[0] == '#')
		value = value.substr(1, value.size());

	for (int i = 0; i < value.size(); i++) {
		if (!(value[i] >= '0' && value[i] <= '9')) {
			return -1;
		}
	}
	return stoi(value);
}
