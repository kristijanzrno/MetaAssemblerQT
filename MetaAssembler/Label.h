#pragma once
#pragma once
#include <string>
using namespace std;
class Label {
public:
	Label(int line, string text, int address, int value);
	void setValue(int mValue);
	void setAddress(int mAddress);
	int getValue();
	int getAddress();
	string getText();


private:
	string text;
	int address;
	int value;
};