#include "Directive.h"
#include <sstream>
#include <iomanip>
using namespace std;

Directive::Directive(int address, int line, string type, string definition)
{
	//This class is used to carry and calculate the DS and DC directives data
	this->address = address;
	this->line = line;
	this->type = type;
	this->definition = definition;
}

int Directive::getSpace(vector<Label*> labels, ConversionUtils *cUtils) 
{
	//Calculates how much space a directive is using
	value = cUtils->toInt(definition);
	bool usesLabel = false;
	if (value == INT_MIN) {
		for (int i = 0; i < labels.size(); i++) {
			if (definition == labels.at(i)->getText()) {
				usesLabel = true;
				if (labels.at(i)->getValue() == INT_MIN)
					value = labels.at(i)->getAddress();
				else
					value = labels.at(i)->getValue();
				break;
			}
		}
	}
	if (value == INT_MIN && !usesLabel)
		//Definition is invalid
		return INT_MIN;

	// Converting definition to fixed hex value
	stringstream stream;
	stream << setfill('0') << setw(4) << uppercase << hex << value;
	definition = stream.str();
	//If there's overflow, add & symbol to indicate it to assembler
	 if (definition.size() > 4) {
		 definition = "&" + definition.substr(0, 4);
	}
	 //DS returns word * value
	if (type == "DS") {
		return value;
	}
	else {
		//DC takes one word
		return 1;
	}
}

int Directive::getValue()
{
	return value;
}

string Directive::getType()
{
	return type;
}

string Directive::getDefinition()
{
	return definition;
}

int Directive::getAddress()
{
	return address;
}

int Directive::getLine()
{
	return line;
}
