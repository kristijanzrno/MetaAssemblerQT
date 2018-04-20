#pragma once
#include <string>
using namespace std;
class Directive {
public:
	Directive(int address, int line, string type, string extension);
private:
	int address;
	string type;
	string definition;
};