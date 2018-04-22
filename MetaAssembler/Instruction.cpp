#include "Instruction.h"
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

Instruction::Instruction(int address, int line, string type, string definition)
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

int Instruction::getAddress()
{
	return address;
}

string Instruction::decode(vector<Label*> labels, ConversionUtils * cUtils)
{
 	int val = cUtils->toInt(value);
	bool usesLabel = false;
	if (val == INT_MIN) {
		for (int i = 0; i < labels.size(); i++) {
			if (value == labels.at(i)->getText()) {
				usesLabel = true;
				if (labels.at(i)->getValue() == INT_MIN)
					val = labels.at(i)->getAddress();
				else
					val = labels.at(i)->getValue();
				if (definition.size() == 2)
					val = val - address;
				break;
				
			}
		}
	}
 
	stringstream stream;
	stream << hex << val;
	value = stream.str();
	if (val < 0 ) {
		return value.substr(value.size() - (4-definition.size()), value.size());
	}
	return value;
	
	}

