#pragma once

#include "ChineseCharacters.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

//���������
class CPhraseManager
{
public:
	static CPhraseManager* GetInstance();
	static void ReleaseInstance();

	wstring getSeparator();

	CChineseCharacters* findFristChineseCharacters(wstring &chineseCharacters);

	void addOnePhrase(wstring &phrase, wstring &replaceString);
	wstring removeOnePhrase(wstring &phrase);

	//�������ַ�
	void getSubChineseCharacters(CChineseCharacters* parent, vector<CChineseCharacters*>& subChineseCharacters);
	//���Ҵ���
	void FindPhrase(wstring& phrase, vector<CChineseCharacters*>& vecChineseCharacters);
	//������prefixΪǰ׺�Ĵ���
	void FindPhraseWithPrefix(wstring& prefix, vector<wstring>& originalPhrase, vector<wstring>& newPhrase);
private:
	CPhraseManager();
	~CPhraseManager();
	
	void relaseAll();
	
	std::map<wstring, CChineseCharacters*> m_PhraseTable;
	static CPhraseManager* m_pInstance;
	
};