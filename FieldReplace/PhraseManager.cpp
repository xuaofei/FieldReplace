#include "stdafx.h"
#include "PhraseManager.h"
#include <vector>

using namespace std;


CPhraseManager* CPhraseManager::m_pInstance = NULL;
CPhraseManager* CPhraseManager::GetInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CPhraseManager();
	}
	return m_pInstance;
}

void CPhraseManager::ReleaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

CPhraseManager::CPhraseManager()
{

}


CPhraseManager::~CPhraseManager()
{
	this->relaseAll();
}


wstring CPhraseManager::getSeparator()
{
	return L"=";
}

CChineseCharacters* CPhraseManager::findFristChineseCharacters(wstring &chineseCharacters)
{
	auto iter = m_PhraseTable.find(chineseCharacters);
	if (iter != m_PhraseTable.end())
	{
		return iter->second;
	}
	return NULL;
}

void CPhraseManager::addOnePhrase(wstring &phrase, wstring &replaceString)
{
	if (phrase.empty())
	{
		return;
	}

	wstring fristString = phrase.substr(0, 1);
	CChineseCharacters* fristChineseCharacters = this->findFristChineseCharacters(fristString);
	if (!fristChineseCharacters)
	{
		fristChineseCharacters = new CChineseCharacters();
		fristChineseCharacters->deep = 1;
		fristChineseCharacters->word = fristString;
		m_PhraseTable.insert(make_pair(fristString, fristChineseCharacters));
	}

	CChineseCharacters* currentChineseCharacters = fristChineseCharacters;
	CChineseCharacters* nextChineseCharacters = NULL;
	for (size_t i = 1; i < phrase.size() ; i++)
	{
		wstring nextString = phrase.substr(i, 1);
		nextChineseCharacters = currentChineseCharacters->findNextChineseCharacters(nextString);
		if (nextChineseCharacters)
		{
			currentChineseCharacters = nextChineseCharacters;
		}
		else
		{
			currentChineseCharacters = currentChineseCharacters->addNextChineseCharacters(nextString);
		}
	}
	currentChineseCharacters->end = true;
	currentChineseCharacters->replaceString = replaceString;
}


wstring CPhraseManager::removeOnePhrase(wstring &phrase)
{
	if (phrase.empty())
	{
		return L"";
	}

	vector<CChineseCharacters*> chineseCharactersForPhrase;
	wstring fristString = phrase.substr(0, 1);
	CChineseCharacters* fristChineseCharacters = this->findFristChineseCharacters(fristString);
	if (!fristChineseCharacters)
	{
		return L"";
	}
	chineseCharactersForPhrase.push_back(fristChineseCharacters);

	CChineseCharacters* currentChineseCharacters = fristChineseCharacters;
	CChineseCharacters* nextChineseCharacters = NULL;
	for (size_t i = 1; i < phrase.size() - 1; i++)
	{
		wstring nextString = phrase.substr(i, 1);
		nextChineseCharacters = currentChineseCharacters->findNextChineseCharacters(nextString);
		if (nextChineseCharacters)
		{
			currentChineseCharacters = nextChineseCharacters;
			chineseCharactersForPhrase.push_back(nextChineseCharacters);
		}
		else
		{
			break;
		}
	}

	bool needDelete = true;
	wstring replaceString;
	//包含完整的Phrase
	if (phrase.size() == chineseCharactersForPhrase.size())
	{
		//清空词尾标记和替换词语
		currentChineseCharacters->end = false;
		currentChineseCharacters->replaceString = L"";

		//比如删除‘123’ 但是存在‘1234’，不需要删除
		if (currentChineseCharacters->m_nextChineseCharacters.size() > 0)
		{
			needDelete = false;
		}
		replaceString = (*chineseCharactersForPhrase.rend())->replaceString;
	}
	else
	{
		//不包含完整的Phrase，删除失败。
		needDelete = false;
	}



	//删除
	if (needDelete)
	{
		vector<CChineseCharacters*> needDeleteChineseCharacters;
		CChineseCharacters* chineseCharacters = NULL;


		for (auto iter = chineseCharactersForPhrase.rend(); iter != chineseCharactersForPhrase.rbegin(); iter++)
		{
			chineseCharacters = *iter;
			if (iter == chineseCharactersForPhrase.rend())
			{
				needDeleteChineseCharacters.push_back(chineseCharacters);
			}
			else
			{
				if (chineseCharacters->m_nextChineseCharacters.size() == 1)
				{
					needDeleteChineseCharacters.push_back(chineseCharacters);
				}
				else
				{
					break;
				}
			}
		}

		for (auto iter = needDeleteChineseCharacters.begin(); iter != needDeleteChineseCharacters.end(); iter++)
		{
			delete *(iter++);
		}
		
	}

	return replaceString;
}

void CPhraseManager::getSubChineseCharacters(CChineseCharacters* parent, vector<CChineseCharacters*>& subChineseCharacters)
{
	for (auto iter = parent->m_nextChineseCharacters.begin(); iter != parent->m_nextChineseCharacters.end(); iter++)
	{
		subChineseCharacters.push_back(iter->second);
	}
}

void CPhraseManager::relaseAll()
{
	for (auto iter = m_PhraseTable.begin(); iter != m_PhraseTable.end(); iter++)
	{
		delete iter->second;
	}
}

void CPhraseManager::FindPhrase(wstring& phrase, vector<CChineseCharacters*>& vecChineseCharacters)
{
	if (phrase.empty())
	{
		return;
	}

	CChineseCharacters* fristChineseCharacters = CPhraseManager::GetInstance()->findFristChineseCharacters(phrase.substr(0, 1));
	if (fristChineseCharacters == NULL)
	{
		return;
	}
	vecChineseCharacters.push_back(fristChineseCharacters);

	CChineseCharacters* currentChineseCharacters = fristChineseCharacters;
	for (size_t i = 1; i < phrase.size(); i++)
	{
		currentChineseCharacters = currentChineseCharacters->findNextChineseCharacters(phrase.substr(i, 1));
		if (currentChineseCharacters)
		{
			vecChineseCharacters.push_back(currentChineseCharacters);
		}
		else
		{
			break;
		}
	}

	//未找到完整的phrase
	if (vecChineseCharacters.size() != phrase.size())
	{
		vecChineseCharacters.clear();
	}
}

void CPhraseManager::FindPhraseWithPrefix(wstring& prefix, vector<wstring>& originalPhrase, vector<wstring>& newPhrase)
{
	vector<CChineseCharacters*> vecChineseCharacters;
	FindPhrase(prefix, vecChineseCharacters);

	if (vecChineseCharacters.empty())
	{
		return;
	}

	CChineseCharacters* prefixLastChineseCharacters = *vecChineseCharacters.rbegin();
	originalPhrase.push_back(prefix);
	newPhrase.push_back(prefixLastChineseCharacters->replaceString);

	vector<CChineseCharacters*> subChineseCharacters;
	getSubChineseCharacters(prefixLastChineseCharacters, subChineseCharacters);
	for (size_t i = 0; i < subChineseCharacters.size(); i++)
	{
		CChineseCharacters* chineseCharacters = subChineseCharacters[i];
		if (chineseCharacters->end)
		{
			wstring& newPrefix(prefix + chineseCharacters->word);
			FindPhraseWithPrefix(newPrefix, originalPhrase, newPhrase);
		}
	}
}