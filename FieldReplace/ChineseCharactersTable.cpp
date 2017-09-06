#include "stdafx.h"
#include "ChineseCharactersTable.h"

CChineseCharactersTable* CChineseCharactersTable::m_pInstance = NULL;
CChineseCharactersTable* CChineseCharactersTable::GetInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CChineseCharactersTable();
	}
	return m_pInstance;
}

CChineseCharactersTable::CChineseCharactersTable()
{
}


CChineseCharactersTable::~CChineseCharactersTable()
{
}

void CChineseCharactersTable::loadChineseCharactersFromFile(std::string filePath)
{

}


void CChineseCharactersTable::saveChineseCharactersToFile(std::string savePath)
{

}

int CChineseCharactersTable::addChineseCharacters(std::string chineseCharacters) {
	return 0;
}

void CChineseCharactersTable::removeChineseCharacters(std::string chineseCharacters)
{

}

int CChineseCharactersTable::getChineseCharactersIndex(std::string chineseCharacters)
{
	return -1;
}
