#include "ConversionUtils.h"

ConversionUtils::ConversionUtils()
{
}

int ConversionUtils::toInt(string address)
{
	if (address[0] == '$') {
		//Hex address
		address = address.substr(1, address.size());
		for (int i = 0; i < address.size(); i++) {
			if (i == 0 && address[i] == '-')
				continue;
			if (!(address[i] >= '0' && address[i] <= '9' || address[i] >= 'A' && address[i] <= 'F')) {
				//Error, invalid address
				return INT_MIN;
			}

		}
		return stoul(address, nullptr, 16);
	}
	//Decimal Address
	if (address[0] == '#')
		address = address.substr(1, address.size());

	for (int i = 0; i < address.size(); i++) {
		if (i == 0 && address[i] == '-')
			continue;
		if (!(address[i] >= '0' && address[i] <= '9')) {
			//Error, invalid address
			return INT_MIN;
		}
	}
	return stoi(address);
}
