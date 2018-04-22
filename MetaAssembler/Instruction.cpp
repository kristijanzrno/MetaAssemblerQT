#include "Instruction.h"
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

Instruction::Instruction(int address, int line, string type, string definition)
{
	//This class is used to carry and calculate instructions data
	this->type = type;
	this->line = line;
	this->definition = definition;
	this->address = address;
}

string Instruction::decode(vector<Label*> labels, ConversionUtils * cUtils)
{
	//Using conversionUtils to determine if word is valid data
	int val = cUtils->toInt(value);
	bool usesLabel = false;
	if (val == INT_MIN) {
		//value is not a valid number so check the labels for value
		for (int i = 0; i < labels.size(); i++) {
			if (value == labels.at(i)->getText()) {
				usesLabel = true;
				//Deciding to use label address or value(if existing with EQU directive)
				if (labels.at(i)->getValue() == INT_MIN)
					val = labels.at(i)->getAddress();
				else
					val = labels.at(i)->getValue();
				//If the instruction is relative, calculate the relative jump
				if (definition.size() == 2) {
					val = val - address;
					val -= 1;
				}
				break;

			}
		}
	}
	//If value is not a valid number or label return ** error code to the assembler
	if (val == INT_MIN && !usesLabel)
		return "**";

	stringstream stream;
	stream << setfill('0') << setw(4 - definition.size()) << uppercase << hex << val;
	value = stream.str();
	//Outputing the final value to fixed length hex number
	if (val < 0)
		return value.substr(value.size() - (4 - definition.size()), value.size());
	//Add & symbol to indicate overflow
	else if (value.size() > (4 - definition.size())) {
		//size warning
		value = "&" + value.substr(0, (4 - definition.size()));
	}
	return value;
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
	return line;
}

int Instruction::getAddress()
{
	return address;
}

