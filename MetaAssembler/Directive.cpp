#include "Directive.h"

Directive::Directive(int address, int line, string type, string extension, string definition)
{
	this->address = address;
	this->line = line;
	this->type = type;
	this->extension = extension;
	this->definition = definition;
}

int Directive::getSpace()
{
	return 0;
}
