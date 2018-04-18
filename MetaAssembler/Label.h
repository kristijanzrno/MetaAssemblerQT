#pragma once
#pragma once
#include <string>
using namespace std;
class Label {
public:
	Label(int line, string text, string address);
private:
	string text;
	string address;
};