#include "Label.h"

Label::Label(int line, string text, int address, int value)
{
	this->address = address;
	this->value = value;
	this->text = text;
}

void Label::setValue(int mValue)
{
	value = mValue;
}

void Label::setAddress(int mAddress)
{
	address = mAddress;
}

int Label::getValue()
{
	return value;
}

int Label::getAddress()
{
	return address;
}

string Label::getText()
{
	return text;
}
