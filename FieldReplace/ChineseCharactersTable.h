#pragma once
#include <map>
class CChineseCharactersTable
{
public:
	static CChineseCharactersTable* GetInstance();
	~CChineseCharactersTable();

	void loadChineseCharactersFromFile(std::string filePath);
	void saveChineseCharactersToFile(std::string savePath);

	int addChineseCharacters(std::string chineseCharacters);
	void removeChineseCharacters(std::string chineseCharacters);

	int getChineseCharactersIndex(std::string chineseCharacters);

private:
	CChineseCharactersTable();
	std::map<std::string, int> m_ChineseCharactersTable;
	static CChineseCharactersTable* m_pInstance;
};

