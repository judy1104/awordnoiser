#include "stdafx.h"
#include "NoiseKor.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;

CNoiseKor::CNoiseKor()
{
}

CNoiseKor::~CNoiseKor()
{

}

BOOL CNoiseKor::GetWordList(CString strWord, CStringList& retList)
{
	// 1) 특수 문자 추가
	AddSpecialChar(strWord, retList);

	// 2) 텍스트 분리
	// 2-1) 철자 1개만 분리
	// 2-2) 철자 2개 분리
	GetSplitWord(strWord, retList);
	
	// 3) 종음은 아랫줄에 추가**

	// 4) 단어 교체


}


void CNoiseKor::GetRandomSpecial(CStringList& strlSpecial)
{
	int nCNTSpecial1 = NUM_KO_CNT_SPECIAL1;
	int nCNTSpecial2 = NUM_KO_CNT_SPECIAL2;

	set<int> mySet;
	srand((unsigned int)time(NULL));

	while (mySet.size() < 30)
	{
		mySet.insert(rand() % nCNTSpecial1);
	}

	for (set<int>::iterator it = mySet.begin(); it != mySet.end(); ++it)
	{
		strlSpecial.AddTail(m_special1[*it]);
	}

	mySet.clear();

	while (mySet.size() < 5)
	{
		mySet.insert(rand() % nCNTSpecial2);
	}

	for (set<int>::iterator it = mySet.begin(); it != mySet.end(); ++it)
	{
		strlSpecial.AddTail(m_special2[*it]);
	}
}

BOOL CNoiseKor::GetSpecialCharAdd(CString strWord, CStringList& retList, int nIndex)
{
	BOOL bResult = TRUE;

	CStringList strlSpecial;
	GetRandomSpecial(strlSpecial);

	POSITION pos = strlSpecial.GetHeadPosition();
	while (pos != strlSpecial.GetTailPosition())
	{
		CString strText = strWord;
		CString strSpecial = strlSpecial.GetNext(pos);

		strWord.Insert(nIndex, strSpecial);
		retList.AddTail(strWord);
	}

	return bResult;
}

BOOL CNoiseKor::AddSpecialChar(CString strWord, CStringList& retList)
{
	BOOL bResult = TRUE;

	if (strWord.GetLength() > 1)
	{
		GetSpecialCharAdd(strWord, retList, 1);
	}

	if (strWord.GetLength() > 2)
	{
		CStringList strlRet1;
		GetSpecialCharAdd(strWord, strlRet1, 1);

		POSITION posRet1 = strlRet1.GetHeadPosition();
		while (posRet1 != strlRet1.GetTailPosition())
		{
			GetSpecialCharAdd(strWord, retList, 3);		
		}
	}

	if (strWord.GetLength() > 3)
	{
		CStringList strlRet1;
		CStringList strlRet2;

		GetSpecialCharAdd(strWord, strlRet1, 1);
				
		POSITION posRet1 = strlRet1.GetHeadPosition();
		while (posRet1 != strlRet1.GetTailPosition())
		{
			GetSpecialCharAdd(strWord, strlRet2, 3);
		}

		POSITION posRet2 = strlRet2.GetHeadPosition();
		while (posRet2 != strlRet2.GetTailPosition())
		{
			GetSpecialCharAdd(strWord, retList, 5);
		}
	}

	return bResult;
}

BOOL CNoiseKor::GetParsedKorean(CString strChar, CString& strParsed)
{
	BOOL bResult = TRUE;

	if (strChar.GetLength() > 1)
	{
		return FALSE;
	}

	TCHAR* szChar;
	szChar = (LPTSTR)(LPCTSTR)strChar;
	int nAscii = __toascii(*(szChar)) - UNICODE_KOREAN_START;

	CString strCho = _T(""), strJung = _T(""), strJong = _T("");
	int		nCho = 0, nJung = 0, nJong = 0;

	nCho = nAscii / (21 * 28);
	nJung = (nAscii % (21 * 28)) / 28;
	nJong = nAscii % 28;

	strCho = hanTable[0][nCho];
	strJung = hanTable[1][nJung];
	strJong = hanTable[2][nJong];

	strParsed.Format(_T("%s%s%s"), strCho, strJung, strJong);
	if (strParsed.IsEmpty() == FALSE)
	{
		bResult = TRUE;
	}

	return bResult;
}

BOOL CNoiseKor::GetSplitWord(CString strWord, CStringList& retList)
{
	BOOL bResult = TRUE;

	if (strWord.GetLength() < 1)
	{
		return FALSE;
	}

	// 1) 첫번째 글자 파싱
	CString strChar1 = strWord.Mid(0, 1);
	CString strText1 = _T("");
	CString strParse1 = _T("");

	GetParsedKorean(strChar1, strParse1);
	strText1.Format(_T("%s%s"), strParse1, strWord.Right(strWord.GetLength() - 1));
	retList.AddTail(strText1);
	m_strlParsedWord.AddTail(strText1);

	// 2) 두번째 글자 파싱	
	CString strChar2 = strWord.Mid(1, 2);
	CString strText2 = _T("");
	CString strParse2 = _T("");

	GetParsedKorean(strChar2, strParse2);
	strText2.Format(_T("%s%s"), strWord.Left(strWord.GetLength() - 1), strParse2);
	retList.AddTail(strText2);
	m_strlParsedWord.AddTail(strText2);

	// 3) 두글자 파싱
	CString strText3 = _T("");
	strText3.Format(_T("%s%s"), strParse1, strParse2);
	retList.AddTail(strText3);
	m_strlParsedWord.AddTail(strText3);

	return bResult;
}

BOOL CNoiseKor::GetNewlineWord(CString strWord, CStringList& retList)
{
	BOOL	bResult = TRUE;

	// 1) 첫번째 글자 엔터
	if (strWord.GetLength() >= 1)
	{
		CString strChar1 = strWord.Mid(0, 1);
		CString strEnter1 = _T("");

		TCHAR* szChar;
		szChar = (LPTSTR)(LPCTSTR)strChar1;
		int nAscii = __toascii(*(szChar)) - UNICODE_KOREAN_START;

		CString strCho = _T(""), strJung = _T(""), strJong = _T("");
		int		nCho = 0, nJung = 0, nJong = 0;

		nCho = nAscii / (21 * 28);
		nJung = (nAscii % (21 * 28)) / 28;
		nJong = nAscii % 28;

		strCho = hanTable[0][nCho];
		strJung = hanTable[1][nJung];
		strJong = hanTable[2][nJong];

		strEnter1.Format(_T("%s%s%s\n %s"), strCho, strJung, strWord.Right(strWord.GetLength() - 1), strJong);
		retList.AddTail(strEnter1);
		m_strlLineWord.AddTail(strEnter1);
	}	

	// 2) 두번째 글자 엔터
	if (strWord.GetLength() >= 2)
	{
		CString strChar2 = strWord.Mid(1, 2);
		CString strEnter2 = _T("");

		TCHAR* szChar;
		szChar = (LPTSTR)(LPCTSTR)strChar2;
		int nAscii = __toascii(*(szChar)) - UNICODE_KOREAN_START;

		CString strCho = _T(""), strJung = _T(""), strJong = _T("");
		int		nCho = 0, nJung = 0, nJong = 0;

		nCho = nAscii / (21 * 28);
		nJung = (nAscii % (21 * 28)) / 28;
		nJong = nAscii % 28;

		strCho = hanTable[0][nCho];
		strJung = hanTable[1][nJung];
		strJong = hanTable[2][nJong];

		strEnter2.Format(_T("%s%s%s\n   %s"), strWord.Left(strWord.GetLength() - 1), strCho, strJung, strJong);
		retList.AddTail(strEnter2);
		m_strlLineWord.AddTail(strEnter2);
	}

	// 3) 두번째 글자 엔터
	if (strWord.GetLength() >= 2)
	{
		CString strChar1 = strWord.Mid(0, 1);
		CString strChar2 = strWord.Mid(1, 2);
		CString strEnter = _T("");

		TCHAR* szChar1;
		TCHAR* szChar2;
		szChar1 = (LPTSTR)(LPCTSTR)strChar1;
		szChar2 = (LPTSTR)(LPCTSTR)strChar2;

		int nAscii1 = __toascii(*(szChar1)) - UNICODE_KOREAN_START;
		int nAscii2 = __toascii(*(szChar2)) - UNICODE_KOREAN_START;

		CString strCho1 = _T(""), strJung1 = _T(""), strJong1 = _T("");
		CString strCho2 = _T(""), strJung2 = _T(""), strJong2 = _T("");
		int		nCho1 = 0, nJung1 = 0, nJong1 = 0;
		int		nCho2 = 0, nJung2 = 0, nJong2 = 0;

		nCho1 = nAscii1 / (21 * 28);
		nJung1 = (nAscii1 % (21 * 28)) / 28;
		nJong1 = nAscii1 % 28;

		nCho2 = nAscii2 / (21 * 28);
		nJung2 = (nAscii2 % (21 * 28)) / 28;
		nJong2 = nAscii2 % 28;

		strCho1 = hanTable[0][nCho1];
		strJung1 = hanTable[1][nJung1];
		strJong1 = hanTable[2][nJong1];		

		strCho2 = hanTable[0][nCho2];
		strJung2 = hanTable[1][nJung2];
		strJong2 = hanTable[2][nJong2];
				
		strEnter.Format(_T("%s%s%s%s\n %s %s"), strCho1, strJung1, strCho2, strJung2, strJong1, strJong2);
		retList.AddTail(strEnter);
		m_strlLineWord.AddTail(strEnter);
	}

	return bResult;
}