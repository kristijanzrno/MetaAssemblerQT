#pragma once
#include <string>
using namespace std;
class Directive {
public:
	Directive(int line, string type, string extension);
private:
	string type;
	string definition;
};