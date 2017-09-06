#pragma once
#include <string>
using namespace std;

class CChinese2PinYin
{
public:
	CChinese2PinYin();
	~CChinese2PinYin();

	static void GetPinYin(string& Chinese, string& PinYin);

private:
	static void GetOtherCodePinYin(int nCode, string& strValue);
};

