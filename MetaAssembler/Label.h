#pragma once
#pragma once
#include <string>
using namespace std;
class Label {
public:
	Label(int line, string text, int address, string value);
	void setValue(string mValue);
	void setAddress(int mAddress);
	string getValue();

private:
	int text;
	string address;
	string value;
};