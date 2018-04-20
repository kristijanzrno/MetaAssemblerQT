#pragma once
#pragma once
#include <string>
using namespace std;
class Label {
public:
	Label(int line, string text, int address);
private:
	int text;
	string address;
};