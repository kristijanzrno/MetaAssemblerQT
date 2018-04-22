#pragma once
#include <string>
using namespace std;

class ConversionUtils {
public:
	ConversionUtils();
	int toInt(string address);
	int calcRelative(int startAddress, int endAddress);
};