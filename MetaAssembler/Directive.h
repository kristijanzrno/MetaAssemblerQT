#pragma once
#include <string>
#include <vector>
#include "ConversionUtils.h"
#include "Label.h"
using namespace std;

class Directive {
public:
	Directive( int address, int line, string type, string definition);

	int getSpace(vector<Label*> labels, ConversionUtils *cUtils);
	int getValue();
	int getAddress();
	int getLine();

	string getType();
	string getDefinition();
	
private:
	int value;
	int address;
	int line;
	string type;
	string definition;
};