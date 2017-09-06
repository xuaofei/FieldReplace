#include "stdafx.h"
#include "ChineseCharacters.h"

CChineseCharacters::CChineseCharacters()
{
	deep = 1;
	end = false;
}


CChineseCharacters::~CChineseCharacters()
{
	for (auto iter = m_nextChineseCharacters.begin(); iter != m_nextChineseCharacters.end(); iter++)
	{
		delete iter->second;
	}
}

CChineseCharacters* CChineseCharacters::addNextChineseCharacters(wstring nextChineseCharacters)
{
	auto iter = m_nextChineseCharacters.find(nextChineseCharacters);
	if (iter != m_nextChineseCharacters.end())
	{
		return iter->second;
	}

	CChineseCharacters* chineseCharacters = new CChineseCharacters();
	chineseCharacters->deep = this->deep + 1;
	chineseCharacters->word = nextChineseCharacters;


	m_nextChineseCharacters.insert(make_pair(nextChineseCharacters, chineseCharacters));

	return chineseCharacters;
}

void CChineseCharacters::removeNextChineseCharacters(wstring nextChineseCharacters)
{
	auto iter = m_nextChineseCharacters.find(nextChineseCharacters);
	if (iter != m_nextChineseCharacters.end())
	{
		delete iter->second;
		m_nextChineseCharacters.erase(iter);
	}
}

CChineseCharacters* CChineseCharacters::findNextChineseCharacters(wstring nextChineseCharacters)
{
	auto iter = m_nextChineseCharacters.find(nextChineseCharacters);
	if (iter != m_nextChineseCharacters.end())
	{
		return iter->second;
	}

	return NULL;
}
