#include "stdafx.h"
#include "NoiseKor.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <windows.h>
#include <locale>
using namespace std;

CNoiseKor::CNoiseKor()
{
	setlocale(LC_ALL, "Korean");
}

CNoiseKor::~CNoiseKor()
{

}

BOOL CNoiseKor::GetWordList(CString strWord, CStringList& retList)
{
	BOOL bResult = TRUE;
	int nStep1 = 0, nStep2 = 0;

	// 1) Ư�� ���� �߰�
	AddSpecialChar(strWord, retList);

	// 2) �ؽ�Ʈ �и� 2-1) ö�� 1���� �и� 2-2) ö�� 2�� �и�
	cout << "�ܾ� ������...#2 SplitWord" << endl;
	GetSplitWord(strWord, retList);

	nStep1 = retList.GetCount();
	nStep2 = retList.GetCount() - nStep1;

	while (nStep2 < nStep1)
	{
		// 3) ������ �Ʒ��ٿ� �߰�**
		cout << "�ܾ� ������...#3 GetNewlineWord" << endl;
		GetNewlineWord(strWord, retList);

		// 4) �ܾ� ��ü
		if (m_strlLineWord1.IsEmpty() == FALSE)
		{
			POSITION posLine1 = m_strlLineWord1.GetHeadPosition();

			while (posLine1 != m_strlLineWord1.GetTailPosition())
			{
				cout << "�ܾ� ������...#4-1 ChangeWordset" << endl;
				GetChangeWordset(m_strlLineWord1.GetNext(posLine1), retList, 0);
			}
			
		}
		if (m_strlLineWord2.IsEmpty() == FALSE)
		{
			POSITION posLine2 = m_strlLineWord2.GetHeadPosition();

			while (posLine2 != m_strlLineWord2.GetTailPosition())
			{
				cout << "�ܾ� ������...#4-2 ChangeWordset" << endl;
				GetChangeWordset(m_strlLineWord2.GetNext(posLine2), retList, 1);
			}			
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
		cout << "�ܾ� ������...#1 AddSpecialChar" << endl;
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
			if (retList.GetCount() > NUM_FILECOUNT / 2)
			{
				break;
			}
			GetSpecialCharAdd(strlRet1.GetNext(posRet1), retList, 3);
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
			if (retList.GetCount() > NUM_FILECOUNT / 2)
			{
				break;
			}
			GetSpecialCharAdd(strlRet1.GetNext(posRet1), strlRet2, 2);
		}

		POSITION posRet2 = strlRet2.GetHeadPosition();
		while (posRet2 != strlRet2.GetTailPosition())
		{
			if (retList.GetCount() > NUM_FILECOUNT / 2)
			{
				break;
			}
			GetSpecialCharAdd(strlRet2.GetNext(posRet2), retList, 3);
		}
	}

	return bResult;
}

BOOL CNoiseKor::GetParsedKorean(CString strChar, CString& strParsed)
{
	BOOL bResult = TRUE;
	if ((strChar.IsEmpty() == TRUE) || (strChar.GetLength() > 1))
	{
		return FALSE;
	}

	CString strCho = _T(""), strJung = _T(""), strJong = _T("");
	
	wchar_t CompleteCode = (int)strChar.GetAt(0);
	wchar_t UniValue = CompleteCode - 0xAC00;

	int nJong = UniValue % 28;
	int nJung = ((UniValue - nJong) / 28) % 21;
	int nCho = ((UniValue - nJong) / 28) / 21;	

	if (nJong > 28 || nJung > 21 || nCho > 19)
	{
		return FALSE; 
	}

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

BOOL CNoiseKor::GetParsedKoreanToChar(CString strChar, CString& strCho, CString& strJung, CString& strJong)
{
	BOOL bresult = FALSE;

	wchar_t CompleteCode = (int)strChar.GetAt(0);
	wchar_t UniValue = CompleteCode - 0xAC00;

	int		nCho = 0, nJung = 0, nJong = 0;

	nJong = UniValue % 28;
	nJung = ((UniValue - nJong) / 28) % 21;
	nCho = ((UniValue - nJong) / 28) / 21;

	strCho = hanTable[0][nCho];
	strJung = hanTable[1][nJung];
	strJong = hanTable[2][nJong];

	return bresult; 
}

BOOL CNoiseKor::GetSplitWord(CString strWord, CStringList& retList)
{
	BOOL bResult = TRUE;

	if (strWord.GetLength() < 1)
	{
		return FALSE;
	}	

	// 1) ù��° ���� �Ľ�
	CString strChar1 = strWord.Mid(0, 1);
	CString strText1 = _T("");
	CString strParse1 = _T("");

	GetParsedKorean(strChar1, strParse1);
	strText1.Format(_T("%s%s"), strParse1, strWord.Right(strWord.GetLength() - 1));
	retList.AddTail(strText1);
	m_strlParsedWord.AddTail(strText1);

	// 2) �ι�° ���� �Ľ�	
	CString strChar2 = strWord.Mid(1, 2);
	CString strText2 = _T("");
	CString strParse2 = _T("");

	GetParsedKorean(strChar2, strParse2);
	strText2.Format(_T("%s%s"), strWord.Left(strWord.GetLength() - 1), strParse2);
	retList.AddTail(strText2);
	m_strlParsedWord.AddTail(strText2);

	// 3) �α��� �Ľ�
	CString strText3 = _T("");
	strText3.Format(_T("%s%s"), strParse1, strParse2);
	retList.AddTail(strText3);
	m_strlParsedWord.AddTail(strText3);

	return bResult;
}

BOOL CNoiseKor::GetNewlineWord(CString strWord, CStringList& retList)
{
	BOOL	bResult = TRUE;

	// 1) ù��° ���� ����
	if (strWord.GetLength() >= 1)
	{
		srand((unsigned int)time(NULL));
		int nCase = rand() % 4;

		CString strChar1 = strWord.Mid(0, 1);
		CString strCho = _T(""), strJung = _T(""), strJong = _T("");
		CString strEnter1 = _T("");

		GetParsedKoreanToChar(strChar1, strCho, strJung, strJong);
		
		switch (nCase)
		{
		case 0:
			strEnter1.Format(_T("%s%s%s\r\n%s"), strCho, strJung, strWord.Right(strWord.GetLength() - 1), strJong);
			break;
		case 1:
			strEnter1.Format(_T("%s%s%s\r\n %s"), strCho, strJung, strWord.Right(strWord.GetLength() - 1), strJong);
			break;
		case 2:
			strEnter1.Format(_T("%s%s%s\r\n  %s"), strCho, strJung, strWord.Right(strWord.GetLength() - 1), strJong);
			break;
		case 3:
			strEnter1.Format(_T("%s%s%s\r\n   %s"), strCho, strJung, strWord.Right(strWord.GetLength() - 1), strJong);
			break;
		default:
			strEnter1.Format(_T("%s%s%s\r\n%s"), strCho, strJung, strWord.Right(strWord.GetLength() - 1), strJong);
			break;
		}

		retList.AddTail(strEnter1);
		m_strlLineWord1.AddTail(strEnter1);
	}	

	// 2) �ι�° ���� ����
	if (strWord.GetLength() >= 2)
	{
		srand((unsigned int)time(NULL));
		int nCase = rand() % 4;

		CString strChar2 = strWord.Mid(1, 2);
		CString strCho = _T(""), strJung = _T(""), strJong = _T("");
		CString strEnter2 = _T("");

		GetParsedKoreanToChar(strChar2, strCho, strJung, strJong);
				
		strEnter2.Format(_T("%s%s%s\r\n   %s"), strWord.Left(strWord.GetLength() - 1), strCho, strJung, strJong);

		switch (nCase)
		{
		case 0:
			strEnter2.Format(_T("%s%s%s\r\n  %s"), strWord.Left(strWord.GetLength() - 1), strCho, strJung, strJong);
			break;
		case 1:
			strEnter2.Format(_T("%s%s%s\r\n   %s"), strWord.Left(strWord.GetLength() - 1), strCho, strJung, strJong);
			break;
		case 2:
			strEnter2.Format(_T("%s%s%s\r\n    %s"), strWord.Left(strWord.GetLength() - 1), strCho, strJung, strJong);
			break;
		case 3:
			strEnter2.Format(_T("%s%s%s\r\n     %s"), strWord.Left(strWord.GetLength() - 1), strCho, strJung, strJong);
			break;
		default:
			strEnter2.Format(_T("%s%s%s\r\n   %s"), strWord.Left(strWord.GetLength() - 1), strCho, strJung, strJong);
			break;
		}

		retList.AddTail(strEnter2);
		m_strlLineWord2.AddTail(strEnter2);
	}

	// 3) �ι�° ���� ����
	if (strWord.GetLength() >= 2)
	{
		srand((unsigned int)time(NULL));
		int nCase = rand() % 9;

		CString strChar1 = strWord.Mid(0, 1);
		CString strChar2 = strWord.Mid(1, 2);

		CString strCho1 = _T(""), strJung1 = _T(""), strJong1 = _T("");
		CString strCho2 = _T(""), strJung2 = _T(""), strJong2 = _T("");

		CString strEnter = _T("");

		GetParsedKoreanToChar(strChar1, strCho1, strJung1, strJong1);
		GetParsedKoreanToChar(strChar2, strCho2, strJung2, strJong2);
				
		switch (nCase)
		{
		case 0:
			strEnter.Format(_T("%s%s%s%s\r\n %s %s"), strCho1, strJung1, strCho2, strJung2, strJong1, strJong2);
			break;
		case 1:
			strEnter.Format(_T("%s%s%s%s\r\n %s  %s"), strCho1, strJung1, strCho2, strJung2, strJong1, strJong2);
			break;
		case 2:
			strEnter.Format(_T("%s%s%s%s\r\n %s   %s"), strCho1, strJung1, strCho2, strJung2, strJong1, strJong2);
			break;
		case 3:
			strEnter.Format(_T("%s%s%s%s\r\n  %s %s"), strCho1, strJung1, strCho2, strJung2, strJong1, strJong2);
			break;
		case 4:
			strEnter.Format(_T("%s%s%s%s\r\n  %s  %s"), strCho1, strJung1, strCho2, strJung2, strJong1, strJong2);
			break;
		case 5:
			strEnter.Format(_T("%s%s%s%s\r\n  %s   %s"), strCho1, strJung1, strCho2, strJung2, strJong1, strJong2);
			break;
		case 6:
			strEnter.Format(_T("%s%s%s%s\r\n   %s %s"), strCho1, strJung1, strCho2, strJung2, strJong1, strJong2);
			break;
		case 7:
			strEnter.Format(_T("%s%s%s%s\r\n   %s  %s"), strCho1, strJung1, strCho2, strJung2, strJong1, strJong2);
			break;
		case 8:
			strEnter.Format(_T("%s%s%s%s\r\n   %s   %s"), strCho1, strJung1, strCho2, strJung2, strJong1, strJong2);
			break;
		default:
			strEnter.Format(_T("%s%s%s%s\r\n %s %s"), strCho1, strJung1, strCho2, strJung2, strJong1, strJong2);
			break;
		}		
		retList.AddTail(strEnter);
		m_strlLineWord3.AddTail(strEnter);
	}

	return bResult;
}

int CNoiseKor::GetKoreanCharJACode(CString strChar)
{
	int nCode = -1;

	int nInput = __toascii(*(strChar));

	int a = __toascii(*(_T("��")));//49
	int b = __toascii(*(_T("��")));//78
	switch (nInput)
	{
	case __toascii(*(_T("��"))):
	{
		nCode = 0;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 1;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 2;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 3;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 4;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 5;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 6;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 7;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 8;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 9;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 10;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 11;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 12;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 13;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 14;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 15;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 16;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 17;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 18;
	}break;

	default:
		break;
	}

	return nCode;
}

int CNoiseKor::GetKoreanCharMOCode(CString strChar)
{
	int nCode = -1;

	int nInput = __toascii(*(strChar));

	int a = __toascii(*(_T("��"))); //79
	int b = __toascii(*(_T("��"))); //99

	switch (nInput)
	{
	case __toascii(*(_T("��"))):
	{
		nCode = 0;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 1;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 2;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 3;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 4;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 5;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 6;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 7;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 8;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 9;
	}break;

	case __toascii(*(_T("��"))):
	{
		nCode = 10;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 11;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 12;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 13;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 14;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 15;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 16;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 17;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 18;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 19;
	}break;
	case __toascii(*(_T("��"))):
	{
		nCode = 20;
	}break;
	default:
		break;
	}

	return nCode;
}

BOOL CNoiseKor::GetChangeWordset(CString strWord, CStringList& retList, int nIndex)
{
	BOOL bResult = FALSE;
	int nSize = strWord.GetLength();

	for (int i = 0; i < nSize; ++i)
	{
		CString strText = strWord;
		CString strChange = _T("");
		CString strRet = _T("");
		CString strChar1 = strText.Mid(0 + i, 1 + i);
		if (strChar1.IsEmpty() == TRUE)
		{
			continue;
		}

		int nCode = __toascii(*(strChar1)); 

		if ((nCode >= 49) && (nCode <= 78))
		{
			nCode = GetKoreanCharJACode(strChar1);
			if ((nCode < 0) || (nCode > 18))
			{
				continue;
			}
			for (int j = 0; j < 10; ++j)
			{				
				strChange = hanTableCho[nCode][j];
				if (strChange.IsEmpty() == TRUE)
				{
					break;
				}
				else
				{
					if (i == 0)
					{
						strRet.Format(_T("%s%s%s"), strText.Left(i), strChange, strText.Right(strText.GetLength() - i - 1));
					}
					else
					{
						strRet.Format(_T("%s%s%s"), strText.Left(i-1), strChange, strText.Right(strText.GetLength() - i));
					}
					
					retList.AddTail(strRet);
				}
			}
		}
		else if ((nCode >= 79) && (nCode <= 99))
		{
			nCode = GetKoreanCharMOCode(strChar1);
			if ((nCode < 0) || (nCode > 21))
			{
				continue;
			}
			for (int j = 0; j < 10; ++j)
			{
				strChange = hanTableMO[nCode][j];
				if (strChange.IsEmpty() == TRUE)
				{
					break;
				}
				else
				{
					if (i == 0)
					{
						strRet.Format(_T("%s%s%s"), strText.Left(i), strChange, strText.Right(strText.GetLength() - i - 1));
					}
					else
					{
						strRet.Format(_T("%s%s%s"), strText.Left(i - 1), strChange, strText.Right(strText.GetLength() - i));
					}
					
					retList.AddTail(strRet);
				}
			}
		}
	}

	return bResult; 
}