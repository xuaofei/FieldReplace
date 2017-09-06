#pragma once
#include <map>
using namespace std;


class CChineseCharacters
{
public:
	CChineseCharacters();
	~CChineseCharacters();

	CChineseCharacters* addNextChineseCharacters(wstring nextChineseCharacters);
	void removeNextChineseCharacters(wstring nextChineseCharacters);

	CChineseCharacters* findNextChineseCharacters(wstring nextChineseCharacters);

	int deep;
	bool end;
	wstring replaceString;
	wstring word;

	map<wstring, CChineseCharacters*> m_nextChineseCharacters;//ÏÂÒ»¸öºº×Ö
};

