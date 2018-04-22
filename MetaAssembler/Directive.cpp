#include "Directive.h"
#include <sstream>
#include <iomanip>
using namespace std;

Directive::Directive(int address, int line, string type, string definition)
{
	this->address = address;
	this->line = line;
	this->type = type;
	this->definition = definition;
}

int Directive::getSpace(vector<Label*> labels, ConversionUtils *cUtils) 
{
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
		return INT_MIN;

	stringstream stream;
	stream << setfill('0') << setw(4) << uppercase << hex << value;
	definition = stream.str();

	 if (definition.size() > 4) {
		 definition = "&" + definition.substr(0, 4);
	}

	if (type == "DS") {
		return value;
	}
	else {
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
