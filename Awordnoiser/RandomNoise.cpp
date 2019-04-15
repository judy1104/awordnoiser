#include "stdafx.h"
#include "RandomNoise.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;

CRandomNoise::CRandomNoise()
{
}

CRandomNoise::~CRandomNoise()
{
	m_rndSpecial.RemoveAll();
	m_rndChange[NUM_CNT_SPELLING][NUM_CNT_RNDCHANGE] = { _T(""), };
}

BOOL CRandomNoise::GetWordList(CString strWord, CStringList& retList)
{
	BOOL bResult = FALSE;

	if (strWord.GetLength() < 2)
	{
		return FALSE;
	}

	retList.RemoveAll();

	GetChangespelling(strWord, retList);
	if (retList.GetCount() < NUM_CNT_MAX / 100)
	{
		CStringList strlAddChar;
		AddSpecialChar(strWord, strlAddChar, TRUE);

		POSITION pos = strlAddChar.GetHeadPosition();
		while (pos != strlAddChar.GetTailPosition())
		{
			if (retList.GetCount() > NUM_CNT_MAX / 100)
			{
				break;
			}
			GetChangespelling(strlAddChar.GetNext(pos), retList);
		}
	}

	AddSpecialChar(strWord, retList);
	
	if (retList.IsEmpty() == FALSE)
	{
		bResult = TRUE;
	}

	return bResult;
}

int CRandomNoise::GetCharcode(CString strChar)
{
	if (strChar.GetLength() != 1)
	{
		return -1;
	}

	TCHAR* szChar;
	szChar = (LPTSTR)(LPCTSTR)strChar;
	int nAscii = __toascii(*(szChar));

	return (nAscii - NUM_START_ASCII_UPPER) < NUM_CNT_SPELLING ? (nAscii - NUM_START_ASCII_UPPER) : (nAscii - NUM_START_ASCII_LOWER);
}

BOOL CRandomNoise::ChangeSpelling(CString strWord, CStringList& retList, int nPos)
{
	BOOL bResult = TRUE;

	CString strText = strWord;
	CString strChar = strText.Mid(nPos, 1);
	int nCode = GetCharcode(strChar);

	if (nCode >= 0 && nCode < NUM_CNT_SPELLING)
	{
		for (int i = 0; i < NUM_CNT_RNDCHANGE; ++i)
		{
			CString strnew = m_rndChange[nCode][i];
			if (strnew.IsEmpty() == FALSE)
			{
				CString str1 = strText.Left(nPos);
				CString str2 = strnew;
				CString str3 = strText.Right(strWord.GetLength() - nPos - 1);
				CString str4 = _T("");
				str4.Format(_T("%s%s%s"), str1, str2, str3);
				retList.AddTail(str4);

				cout << "단어 생성중...#ChangeSpelling"<< endl;
			}
		}
	}

	return bResult;
}

BOOL CRandomNoise::Changespelling(CString strWord, CStringList& retList)
{
	BOOL bResult = TRUE;
	CString strText = strWord;
	set<CString> mySet; 

	for (int i = 0; i < strWord.GetLength(); ++i)
	{
		CString strChar = strText.Mid(i, 1);
		int nPos = GetCharcode(strChar);

		if (nPos >= 0 && nPos < NUM_CNT_SPELLING)
		{
			for (int j = 0; j < NUM_CNT_RNDCHANGE; ++j)
			{
				CString strnew = m_rndChange[nPos][j];
				if (strnew.IsEmpty() == FALSE)
				{
					strText.Replace(strChar, strnew);
					mySet.insert(strText);
				}
			}
		}
	}

	if (mySet.size() < NUM_CNT_MAX)
	{
		for (set<CString>::iterator it = mySet.begin(); it != mySet.end(); ++it)
		{
			if (mySet.size() < NUM_CNT_MAX)
			{
				break;
			}
			strText = *it;

			for (int i = 0; i < strText.GetLength(); ++i)
			{
				if (mySet.size() < NUM_CNT_MAX)
				{
					break;
				}
				CString strChar = strText.Mid(i, 1);
				int nPos = GetCharcode(strChar);

				if (nPos >= 0 && nPos < NUM_CNT_SPELLING)
				{
					for (int j = 0; j < NUM_CNT_RNDCHANGE; ++j)
					{
						CString strnew = m_rndChange[nPos][j];
						if (strnew.IsEmpty() == FALSE)
						{
							strText.Replace(strChar, strnew);
							mySet.insert(strText);
						}
					}
				}
			}
		}
	}

	if (mySet.size() < NUM_CNT_MAX)
	{
		for (set<CString>::iterator it = mySet.begin(); it != mySet.end(); ++it)
		{
			if (mySet.size() < NUM_CNT_MAX)
			{
				break;
			}
			strText = *it;

			for (int i = 0; i < strText.GetLength(); ++i)
			{
				if (mySet.size() < NUM_CNT_MAX)
				{
					break;
				}
				CString strChar = strText.Mid(i, 1);
				int nPos = GetCharcode(strChar);

				if (nPos >= 0 && nPos < NUM_CNT_SPELLING)
				{
					for (int j = 0; j < NUM_CNT_RNDCHANGE; ++j)
					{
						CString strnew = m_rndChange[nPos][j];
						if (strnew.IsEmpty() == FALSE)
						{
							strText.Replace(strChar, strnew);
							mySet.insert(strText);
						}
					}
				}
			}
		}
	}

	CStringList	myList;
	for (auto it = mySet.begin(); it != mySet.end(); it++) 
	{
		if (myList.GetCount() > NUM_CNT_MAX/10)
		{
			break;
		}
		RunAddingSpecial(*it, myList);
	}

	POSITION pos = myList.GetHeadPosition();
	while (pos != myList.GetTailPosition())
	{
		mySet.insert(myList.GetNext(pos));
	}

	for (set<CString>::iterator it = mySet.begin(); it != mySet.end(); ++it)
	{
		retList.AddTail(*it);
	}

	return bResult;
}

BOOL CRandomNoise::GetChangespelling(CString strWord, CStringList& retList)
{
	BOOL bResult = FALSE;

	CStringList myList; 
	set<CString> mySet; 

	// case 1
	for (int i = 0; i < strWord.GetLength(); ++i)
	{
		GetRandomChange();
		ChangeSpelling(strWord, myList, i);
	}

	POSITION pos = myList.GetHeadPosition();
	while (pos != myList.GetTailPosition())
	{
		mySet.insert(myList.GetNext(pos));
	}
	for (set<CString>::iterator it = mySet.begin(); it != mySet.end(); ++it)
	{
		myList.AddTail(*it);
	}

	// case 2
	if (myList.GetCount() < NUM_CNT_MAX / 10)
	{
		myList.RemoveAll();
		for (int i = 0; i < strWord.GetLength(); ++i)
		{
			GetRandomChange();
			ChangeSpelling(strWord, myList, i);
		}

		pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			if (myList.GetCount() > NUM_CNT_MAX / 10)
			{
				break;
			}
			CString strText = myList.GetNext(pos);
			for (int j = 0; j < strText.GetLength(); ++j)
			{
				if (myList.GetCount() > NUM_CNT_MAX / 10)
				{
					break;
				}
				GetRandomChange();
				ChangeSpelling(strWord, myList, j);
			}
		}

		pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			mySet.insert(myList.GetNext(pos));
		}
		for (set<CString>::iterator it = mySet.begin(); it != mySet.end(); ++it)
		{
			myList.AddTail(*it);
		}
	}

	// case 3
	if (myList.GetCount() < NUM_CNT_MAX / 10)
	{
		myList.RemoveAll();
		for (int i = 0; i < strWord.GetLength(); ++i)
		{
			GetRandomChange();
			ChangeSpelling(strWord, myList, i);
		}

		pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			if (myList.GetCount() > NUM_CNT_MAX / 10)
			{
				break;
			}
			CString strText = myList.GetNext(pos);
			for (int j = 0; j < strText.GetLength(); ++j)
			{
				if (myList.GetCount() > NUM_CNT_MAX / 10)
				{
					break;
				}
				GetRandomChange();
				ChangeSpelling(strWord, myList, j);
			}
		}

		pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			if (myList.GetCount() > NUM_CNT_MAX)
			{
				break;
			}
			CString strText = myList.GetNext(pos);
			for (int j = 0; j < strText.GetLength(); ++j)
			{
				if (myList.GetCount() > NUM_CNT_MAX)
				{
					break;
				}
				GetRandomChange();
				ChangeSpelling(strWord, myList, j);
			}
		}

		pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			mySet.insert(myList.GetNext(pos));
		}
	}	

	for (set<CString>::iterator it = mySet.begin(); it != mySet.end(); ++it)
	{
		retList.AddTail(*it);
	}

	return bResult;
}

BOOL CRandomNoise::AddSpecialChar(CString strWord, CStringList& retList, BOOL bAddTwoChar/*=FALSE*/)
{
	BOOL bResult = TRUE;
	int nLenWord = strWord.GetLength();

	CStringList myList; 
	set<CString> mySet; 
	
	RunAddingSpecial(strWord, myList);

	POSITION pos = myList.GetHeadPosition();
	while (pos != myList.GetTailPosition())
	{
		cout << "단어 생성중...#AddSpecialChar1" << endl;
		mySet.insert(myList.GetNext(pos));
	}

	if (mySet.size() < NUM_CNT_MAX/2)
	{
		myList.RemoveAll();
		RunAddingSpecial(strWord, myList);

		set<CString> mySet2;
		POSITION pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			cout << "단어 생성중...#AddSpecialChar2-1" << endl;
			mySet2.insert(myList.GetNext(pos));
		}

		myList.RemoveAll();
		for (set<CString>::iterator it = mySet2.begin(); it != mySet2.end(); ++it)
		{
			if (myList.GetCount() > NUM_CNT_MAX / 100)
			{
				break;
			}
			CString strText = *it;
			RunAddingSpecial(strText, myList);
		}

		pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			cout << "단어 생성중...#AddSpecialChar2-2" << endl;
			mySet.insert(myList.GetNext(pos));
		}
	}

	if ((bAddTwoChar == FALSE) && (mySet.size() < NUM_CNT_MAX/2))
	{
		myList.RemoveAll();
		RunAddingSpecial(strWord, myList);

		set<CString> mySet2;
		POSITION pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			cout << "단어 생성중...#AddSpecialChar3-1" << endl;
			mySet2.insert(myList.GetNext(pos));
		}

		myList.RemoveAll();
		for (set<CString>::iterator it = mySet2.begin(); it != mySet2.end(); ++it)
		{
			if (myList.GetCount() > NUM_CNT_MAX / 100)
			{
				break;
			}
			CString strText = *it;
			RunAddingSpecial(strText, myList);
		}

		set<CString> mySet3;
		pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			cout << "단어 생성중...#AddSpecialChar3-2" << endl;
			mySet3.insert(myList.GetNext(pos));
		}

		myList.RemoveAll();
		for (set<CString>::iterator it = mySet3.begin(); it != mySet3.end(); ++it)
		{
			if (myList.GetCount() > NUM_CNT_MAX / 100)
			{
				break;
			}
			CString strText = *it;
			RunAddingSpecial(strText, myList);
		}

		pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			cout << "단어 생성중...#AddSpecialChar3-3" << endl;
			mySet.insert(myList.GetNext(pos));
		}
	}	

	if ((bAddTwoChar == FALSE) && (mySet.size() < NUM_CNT_MAX / 2))
	{
		myList.RemoveAll();
		RunAddingSpecial(strWord, myList);

		set<CString> mySet2;
		POSITION pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			cout << "단어 생성중...#AddSpecialChar4-1" << endl;
			mySet2.insert(myList.GetNext(pos));
		}

		myList.RemoveAll();
		for (set<CString>::iterator it = mySet2.begin(); it != mySet2.end(); ++it)
		{
			if (myList.GetCount() > NUM_CNT_MAX / 100)
			{
				break;
			}
			CString strText = *it;
			RunAddingSpecial(strText, myList);
		}

		set<CString> mySet3;
		pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			cout << "단어 생성중...#AddSpecialChar4-2" << endl;
			mySet3.insert(myList.GetNext(pos));
		}

		myList.RemoveAll();
		for (set<CString>::iterator it = mySet3.begin(); it != mySet3.end(); ++it)
		{
			if (myList.GetCount() > NUM_CNT_MAX / 100)
			{
				break;
			}
			CString strText = *it;
			RunAddingSpecial(strText, myList);
		}

		set<CString> mySet4;
		pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			cout << "단어 생성중...#AddSpecialChar4-3" << endl;
			mySet4.insert(myList.GetNext(pos));
		}

		myList.RemoveAll();
		for (set<CString>::iterator it = mySet4.begin(); it != mySet4.end(); ++it)
		{
			if (myList.GetCount() > NUM_CNT_MAX / 100)
			{
				break;
			}
			CString strText = *it;
			RunAddingSpecial(strText, myList);
		}

		pos = myList.GetHeadPosition();
		while (pos != myList.GetTailPosition())
		{
			cout << "단어 생성중...#AddSpecialChar4-4" << endl;
			mySet.insert(myList.GetNext(pos));
		}	
	}

	for (set<CString>::iterator it = mySet.begin(); it != mySet.end(); ++it)
	{
		retList.AddTail(*it);
		cout << "단어 생성중...#AddSpecialChar 정리" << endl;
	}

	return bResult;
}

BOOL CRandomNoise::SetAddingSpecial(CString strWord, CStringList& retList, int nPos)
{	
	if (retList.GetCount() > NUM_CNT_MAX/10)
	{
		return FALSE;
	}

	BOOL bResult = TRUE;
	GetRandomSpecial();

	POSITION pos = m_rndSpecial.GetHeadPosition();
	while (pos != m_rndSpecial.GetTailPosition())
	{
		if (retList.GetCount() > NUM_CNT_MAX/10)
		{
			break;
		}
		CString strText = strWord;
		strText.Insert(nPos, m_rndSpecial.GetNext(pos));
		retList.AddTail(strText);
	}
	m_rndSpecial.RemoveAll();

	return bResult; 
}

BOOL CRandomNoise::RunAddingSpecial(CString strWord, CStringList& retList)
{
	BOOL bResult = TRUE;
	int nLenWord = strWord.GetLength();

	if (nLenWord == 1)
	{
		bResult = FALSE;
	}
	else if ((nLenWord > 1) && (nLenWord < 5))
	{
		for (int i = 1; i < nLenWord; i = i+2)
		{
			if (retList.GetCount() > NUM_CNT_MAX / 10)
			{
				break;
			}
			SetAddingSpecial(strWord, retList, i);
			cout << "단어 생성중...#RunAddingSpecial" << endl;
		}
	}
	else
	{
		set<int> mySet;
		srand((unsigned int)time(NULL));

		int nCount = nLenWord - 4;

		while (mySet.size() < nCount)
		{
			mySet.insert(rand() % (nLenWord-1) +1);
		}

		for (set<int>::iterator it = mySet.begin(); it != mySet.end(); ++it)
		{
			if (retList.GetCount() > NUM_CNT_MAX / 10)
			{
				break;
			}
			SetAddingSpecial(strWord, retList, *it);
			cout << "단어 생성중...#RunAddingSpecial" << endl;
		}

		mySet.clear();
		srand((unsigned int)time(NULL));
		
		while (mySet.size() < nCount)
		{
			mySet.insert(rand() % (nLenWord - 1) + 1);
		}

		for (set<int>::iterator it = mySet.begin(); it != mySet.end(); ++it)
		{
			if (retList.GetCount() > NUM_CNT_MAX / 10)
			{
				break;
			}
			SetAddingSpecial(strWord, retList, *it);
			cout << "단어 생성중...#RunAddingSpecial2" << endl;
		}

		mySet.clear();
		srand((unsigned int)time(NULL));
				
		while (mySet.size() < nCount)
		{
			mySet.insert(rand() % (nLenWord - 1) + 1);
		}

		for (set<int>::iterator it = mySet.begin(); it != mySet.end(); ++it)
		{
			if (retList.GetCount() > NUM_CNT_MAX / 10)
			{
				break;
			}
			SetAddingSpecial(strWord, retList, *it);
			cout << "단어 생성중...#RunAddingSpecial3" << endl;
		}
	}

	return bResult;
}

void CRandomNoise::GetRandomChange()
{
	for (int i = 0; i < NUM_CNT_SPELLING; ++i)
	{
		int	nCount = NUM_CNT_CHANGECHAR;

		for (int j = 0; j < NUM_CNT_CHANGECHAR; ++j)
		{
			if (m_strChange[i][j] == _T(""))
			{
				nCount = j + 1; 
				break;
			}
		}

		set<int> mySet;
		srand((unsigned int)time(NULL));

		while (mySet.size() < 5)
		{
			mySet.insert(rand() % nCount);
		}

		int ncol = 0; 
		for (set<int>::iterator it = mySet.begin(); it != mySet.end(); ++it)
		{
			m_rndChange[i][ncol] = m_strChange[i][*it];
			++ncol;
		}
	}
}

void CRandomNoise::GetRandomSpecial()
{
	int nCNTSpecial1 = NUM_CNT_SPECIAL1;
	int nCNTSpecial2 = NUM_CNT_SPECIAL2;

	set<int> mySet;
	srand((unsigned int)time(NULL));

	while (mySet.size() < 30)
	{
		mySet.insert(rand() % nCNTSpecial1);
	}

	for (set<int>::iterator it = mySet.begin(); it != mySet.end(); ++it)
	{
		m_rndSpecial.AddTail(m_special1[*it]);
	}

	mySet.clear();

	while (mySet.size() < 5)
	{
		mySet.insert(rand() % nCNTSpecial2);
	}

	for (set<int>::iterator it = mySet.begin(); it != mySet.end(); ++it)
	{
		m_rndSpecial.AddTail(m_special2[*it]);
	}
}