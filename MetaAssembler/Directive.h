#pragma once
#include <string>
using namespace std;
class Directive {
public:
	Directive( int address, int line, string type, string extension, string definition);
	int getSpace();
private:
	int address;
	int line;
	string type;
	string extension;
	string definition;
};