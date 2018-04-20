#include "Instruction.h"

Instruction::Instruction(int address, int line, string type, string definition)
{
	this->type = type;
	this->definition = definition;
	this->address = address;
}

void Instruction::setValue(string val)
{
	value = val;
}

void Instruction::setAddress()
{
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
