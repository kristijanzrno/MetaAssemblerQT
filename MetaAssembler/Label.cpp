#include "Label.h"

Label::Label(int line, string text, int address, string value)
{
	this->address = address;
	this->value = value;
}

void Label::setValue(string mValue)
{
	value = mValue;
}

void Label::setAddress(int mAddress)
{
	address = mAddress;
}

string Label::getValue()
{
	return value;
}
