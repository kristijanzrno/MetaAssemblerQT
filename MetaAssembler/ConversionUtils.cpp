#include "ConversionUtils.h"

ConversionUtils::ConversionUtils()
{
	//This class is used to handle hex-int conversions
	//More functions like intToHex, hexToBinary will be added here in futurue
}

int ConversionUtils::toInt(string value)
{
	//Takes a string value and checks if it's hex or decimal based on prefix
	//Will return INT_MIN if value is invalid (perhaps label instead of numerical constant)

	if (value[0] == '$') {
		//Hex value
		value = value.substr(1, value.size());
		for (int i = 0; i < value.size(); i++) {
			if (i == 0 && value[i] == '-')
				continue;
			if (!(value[i] >= '0' && value[i] <= '9' || value[i] >= 'A' && value[i] <= 'F')) {
				//Error, invalid value
				return INT_MIN;
			}

		}
		return stoul(value, nullptr, 16);
	}
	//Decimal value
	if (value[0] == '#')
		value = value.substr(1, value.size());

	for (int i = 0; i < value.size(); i++) {
		if (i == 0 && value[i] == '-')
			continue;
		if (!(value[i] >= '0' && value[i] <= '9')) {
			//Error, invalid value
			return INT_MIN;
		}
	}
	return stoi(value);
}
