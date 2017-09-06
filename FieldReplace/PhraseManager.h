#pragma once

#include "ChineseCharacters.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

//词组管理器
class CPhraseManager
{
public:
	static CPhraseManager* GetInstance();
	static void ReleaseInstance();

	wstring getSeparator();

	CChineseCharacters* findFristChineseCharacters(wstring &chineseCharacters);

	void addOnePhrase(wstring &phrase, wstring &replaceString);
	wstring removeOnePhrase(wstring &phrase);

	//查找子字符
	void getSubChineseCharacters(CChineseCharacters* parent, vector<CChineseCharacters*>& subChineseCharacters);
	//查找词组
	void FindPhrase(wstring& phrase, vector<CChineseCharacters*>& vecChineseCharacters);
	//查找以prefix为前缀的词组
	void FindPhraseWithPrefix(wstring& prefix, vector<wstring>& originalPhrase, vector<wstring>& newPhrase);
private:
	CPhraseManager();
	~CPhraseManager();
	
	void relaseAll();
	
	std::map<wstring, CChineseCharacters*> m_PhraseTable;
	static CPhraseManager* m_pInstance;
	
};