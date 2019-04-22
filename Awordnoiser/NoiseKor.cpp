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
	BOOL bResult = TRUE;
	int nStep1 = 0, nStep2 = 0;

	// 1) 특수 문자 추가
	AddSpecialChar(strWord, retList);

	// 2) 텍스트 분리 2-1) 철자 1개만 분리 2-2) 철자 2개 분리
	GetSplitWord(strWord, retList);

	nStep1 = retList.GetCount();
	nStep2 = retList.GetCount() - nStep1;

	while (nStep2 < nStep1)
	{
		// 3) 종음은 아랫줄에 추가**
		GetNewlineWord(strWord, retList);

		// 4) 단어 교체
		if (m_strlLineWord1.IsEmpty() == FALSE)
		{
			GetChangeWordset(strWord, retList, 0);
		}
		if (m_strlLineWord2.IsEmpty() == FALSE)
		{
			GetChangeWordset(strWord, retList, 1);
		}

		nStep2 = retList.GetCount() - nStep1;
	}	

	return bResult;
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

		strText.Insert(nIndex, strSpecial);
		retList.AddTail(strText);
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

BOOL CNoiseKor::GetParsedKorean_python(CString strChar, CString& strParsed)
{
	BOOL bResult = TRUE;

// 	if (strChar.GetLength() > 1)
// 	{
// 		return FALSE;
// 	}
// 
// 	setlocale(LC_ALL, "Korean");
// 	WORD in_char, in_cho, in_jung, in_jong;
// 	WORD result;
// 
// 	_tcscpy(in_char, strChar);
// 	in_char = strChar;
// 	printf("Input a letter : ");
// 	wscanf(L"%c", &in_char);
// 
// 	// 초`중`종성 분해
// 	in_char = in_char - 0xAC00;
// 	//in_cho = in_char / (21 * 28);
// 	in_cho = in_char / (0x0015 * 0x001C);
// 	//in_jung = (in_char / 28) % 21;
// 	in_jung = (in_char / 0x001C) % 0x0015;
// 	//in_jong = in_char % 28;
// 	in_jong = in_char % 0x001C;
// 
// 
// 	// 초`중`종성 print
// 	if (in_jong == 0)
// 		wprintf(L"%c => %c + %c\n", in_char + 0xAC00, in_cho + 0x1100, in_jung + 0x1161);
// 	else
// 		wprintf(L"%c => %c + %c + %c\n", in_char + 0xAC00, in_cho + 0x1100, in_jung + 0x1161, in_jong + 0x11A7);

	return bResult;
}

BOOL CNoiseKor::GetParsedKorean(CString strChar, CString& strParsed)
{
	BOOL bResult = TRUE;

	if (strChar.GetLength() > 1)
	{
		return FALSE;
	}

	strChar = _T("보");

		
	TCHAR* szChar = (TCHAR*)(LPCTSTR)strChar;
	//szChar = (LPTSTR)(LPCTSTR)strChar;
	//int nAscii = __toascii(*(szChar)) - __toascii(*(_T("가")));
	//int nAscii = __toascii(*(strChar));

	int nAscii = (int)szChar - 0xAC00;

	CString strCho = _T(""), strJung = _T(""), strJong = _T("");
	int		nCho = 0, nJung = 0, nJong = 0;

	nCho = nAscii / (0x0015 * 0x001C);
	nJung = (nAscii / 0x001C) % 0x0015;
	nJong = nAscii % 0x001C;

//  	nJong = nAscii % 28;
//  	nJung = ((nAscii - nJong) / 28) % 21;
//  	nCho = ((nAscii - nJong) / 28 - nJung)/ 21;
	
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
		int nAscii = __toascii(*(szChar)) - __toascii(*(_T("가")));

		CString strCho = _T(""), strJung = _T(""), strJong = _T("");
		int		nCho = 0, nJung = 0, nJong = 0;

		nCho = nAscii / (21 * 28);
		nJung = (nAscii % (21 * 28)) / 28;
		nJong = nAscii % 28;

		strCho = hanTable[0][nCho];
		strJung = hanTable[1][nJung];
		strJong = hanTable[2][nJong];

		strEnter1.Format(_T("%s%s%s\r\n %s"), strCho, strJung, strWord.Right(strWord.GetLength() - 1), strJong);
		retList.AddTail(strEnter1);
		m_strlLineWord1.AddTail(strEnter1);
	}	

	// 2) 두번째 글자 엔터
	if (strWord.GetLength() >= 2)
	{
		CString strChar2 = strWord.Mid(1, 2);
		CString strEnter2 = _T("");

		TCHAR* szChar;
		szChar = (LPTSTR)(LPCTSTR)strChar2;
		int nAscii = __toascii(*(szChar)) - __toascii(*(_T("가")));

		CString strCho = _T(""), strJung = _T(""), strJong = _T("");
		int		nCho = 0, nJung = 0, nJong = 0;

		nCho = nAscii / (21 * 28);
		nJung = (nAscii % (21 * 28)) / 28;
		nJong = nAscii % 28;

		strCho = hanTable[0][nCho];
		strJung = hanTable[1][nJung];
		strJong = hanTable[2][nJong];

		strEnter2.Format(_T("%s%s%s\r\n   %s"), strWord.Left(strWord.GetLength() - 1), strCho, strJung, strJong);
		retList.AddTail(strEnter2);
		m_strlLineWord2.AddTail(strEnter2);
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

		int nAscii1 = __toascii(*(szChar1)) - __toascii(*(_T("가")));
		int nAscii2 = __toascii(*(szChar2)) - __toascii(*(_T("가")));

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
				
		strEnter.Format(_T("%s%s%s%s\r\n %s %s"), strCho1, strJung1, strCho2, strJung2, strJong1, strJong2);
		retList.AddTail(strEnter);
		m_strlLineWord3.AddTail(strEnter);
	}

	return bResult;
}

BOOL CNoiseKor::GetChangeWordset(CString strWord, CStringList& retList, int nIndex)
{
	BOOL bResult = FALSE;
	int nSize = strWord.GetLength();

	// 1) 첫번째 글자 쪼갬
	CString strText = strWord;
	CString strChar1 = strText.Mid(0 + nIndex, 1 + nIndex);

	TCHAR* szChar1;
	szChar1 = (LPTSTR)(LPCTSTR)strChar1;

	int nAscii1 = __toascii(*(strChar1)) - __toascii(*(_T("ㄱ")));

	if (nAscii1 > 0)
	{
		for (int i = 0; i < 10; ++i)
		{
			CString strRet = _T("");
			CString strChange = hanTableCho[nAscii1][i];
			if (strChange.IsEmpty() == TRUE)
			{
				break;
			}
			strRet.Format(_T("%s%s"), strChange, strText.Right(strText.GetLength() - 1));
			retList.AddTail(strRet);
		}
	}

	strText = strWord;
	CString strChar2 = strText.Mid(1 + nIndex, 2 + nIndex);
	TCHAR* szChar2;
	szChar2 = (LPTSTR)(LPCTSTR)strChar2;

	int nAscii2 = __toascii(*(szChar2)) - __toascii(*(_T("ㅏ")));

	if (nAscii2 > 0)
	{
		for (int i = 0; i < 10; ++i)
		{
			CString strRet = _T("");
			CString strChange = hanTableJung[nAscii2][i];
			if (strChange.IsEmpty() == TRUE)
			{
				break;
			}
			strRet.Format(_T("%s%s%s"), strText.Mid(0, 1), strChange, strText.Right(strText.GetLength() - 2));
			retList.AddTail(strRet);
		}
	}
	
	// 3) 두 글자 모두 쪼갬


	return bResult; 
}