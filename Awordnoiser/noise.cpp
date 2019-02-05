#include "stdafx.h"
#include "noise.h"

CNoise::CNoise(CString strWord, int nFilter /*= 0*/, BOOL bOption1 /*= TRUE*/, BOOL bOption2 /*= TRUE*/, BOOL bOption3 /*= TRUE*/, BOOL bOption4 /*= TRUE*/, BOOL bOption5 /*= TRUE*/)
{
	m_strWord = strWord;
	m_nfilter = nFilter; 
	m_bOption1 = bOption1;
	m_bOption2 = bOption2;
	m_bOption3 = bOption3;
	m_bOption4 = bOption4;
	m_bOption5 = bOption5;

	m_strlspecialChar.AddTail(_T("  "));
// 	m_strlspecialChar.AddTail(_T("＃"));
// 	m_strlspecialChar.AddTail(_T("＆"));
// 	m_strlspecialChar.AddTail(_T("＊"));
// 	m_strlspecialChar.AddTail(_T("＠"));
// 	m_strlspecialChar.AddTail(_T("§"));
	m_strlspecialChar.AddTail(_T("※"));
	m_strlspecialChar.AddTail(_T("☆"));
// 	m_strlspecialChar.AddTail(_T("★"));
// 	m_strlspecialChar.AddTail(_T("○"));
// 	m_strlspecialChar.AddTail(_T("●"));
 	m_strlspecialChar.AddTail(_T("◎"));
// 	m_strlspecialChar.AddTail(_T("◇"));
// 	m_strlspecialChar.AddTail(_T("◆"));
// 	m_strlspecialChar.AddTail(_T("□"));
 	m_strlspecialChar.AddTail(_T("■"));
// 	m_strlspecialChar.AddTail(_T("△"));
// 	m_strlspecialChar.AddTail(_T("▲"));
// 	m_strlspecialChar.AddTail(_T("▽"));
// 	m_strlspecialChar.AddTail(_T("▼"));
 	m_strlspecialChar.AddTail(_T("◁"));
// 	m_strlspecialChar.AddTail(_T("◀"));
// 	m_strlspecialChar.AddTail(_T("▷"));
// 	m_strlspecialChar.AddTail(_T("▶"));
// 	m_strlspecialChar.AddTail(_T("♤"));
 	m_strlspecialChar.AddTail(_T("♠"));
 	m_strlspecialChar.AddTail(_T("♡"));
 	m_strlspecialChar.AddTail(_T("♥"));
 	m_strlspecialChar.AddTail(_T("♧"));
 	m_strlspecialChar.AddTail(_T("♣"));
// 	m_strlspecialChar.AddTail(_T("⊙"));
 	m_strlspecialChar.AddTail(_T("◈"));
// 	m_strlspecialChar.AddTail(_T("▣"));
// 	m_strlspecialChar.AddTail(_T("◐"));
// 	m_strlspecialChar.AddTail(_T("◑"));
// 	m_strlspecialChar.AddTail(_T("▒"));
// 	m_strlspecialChar.AddTail(_T("▤"));
// 	m_strlspecialChar.AddTail(_T("▥"));
// 	m_strlspecialChar.AddTail(_T("▨"));
// 	m_strlspecialChar.AddTail(_T("▧"));
// 	m_strlspecialChar.AddTail(_T("▦"));
// 	m_strlspecialChar.AddTail(_T("▩"));
// 	m_strlspecialChar.AddTail(_T("♨"));
 	m_strlspecialChar.AddTail(_T("☏"));
// 	m_strlspecialChar.AddTail(_T("☎"));
 	m_strlspecialChar.AddTail(_T("♭"));
// 	m_strlspecialChar.AddTail(_T("♩"));
 	m_strlspecialChar.AddTail(_T("♪"));
// 	m_strlspecialChar.AddTail(_T("♬"));
}

CNoise::~CNoise()
{

}

BOOL CNoise::GetWordList(CStringList& strList)
{
	BOOL bResult = TRUE; 

	strList.RemoveAll();

	if (m_bOption1 == TRUE)
	{
		GetChangespelling(strList);
	}
	
	if ((m_bOption2 | m_bOption3 | m_bOption4 | m_bOption5) == TRUE)
	{
		AddSpecialChar(strList);
	}

	return bResult; 
}

int CNoise::GetCharcode(CString strChar)
{
	if (strChar.GetLength() != 1 )
	{
		return -1; 
	}
	
	//strChar.MakeUpper();

	TCHAR* szChar; 
	szChar = (LPTSTR)(LPCTSTR)strChar;
	int iAscii = __toascii(*(szChar));

	return (iAscii - NUM_START_ASCII_UPPER) < NUM_CNT_SPELLING ? (iAscii - NUM_START_ASCII_UPPER) : (iAscii - NUM_START_ASCII_LOWER);
}

BOOL CNoise::GetChangespelling(CStringList& strList)
{
	BOOL bResult = TRUE;
	if (m_strWord.IsEmpty() == TRUE)
	{
		return FALSE; 
	}

	ChangeSpelling(m_strWord);

	// 복사
	for (set<CString>::iterator it = m_setwords.begin(); it != m_setwords.end(); ++it)
	{
		strList.AddTail(*it);
	}

	return bResult;
}

BOOL CNoise::ChangeSpelling(CString strWord)
{
	BOOL bResult = TRUE;

	// case 1
	set<CString> setChar;
	for (int i = 0; i < m_strWord.GetLength(); ++i)
	{
		setChar.insert(m_strWord.Mid(i, 1));
	}

	for (set<CString>::iterator it = setChar.begin(); it != setChar.end(); ++it)
	{
		for (int i = 0; i < NUM_CNT_CHANGECHAR; ++i)
		{
			CString strResult = strWord;
			CString strChar = *it;
			int nPos = GetCharcode(strChar);
			if (nPos > 0 && nPos < NUM_CNT_SPELLING)
			{
				CString strnew = m_strChange[nPos][i];
				if (strnew.IsEmpty() == FALSE)
				{
					strResult.Replace(strChar, strnew);
					m_setwords.insert(strResult);
					++m_nIndex;
					cout << "변환 작업중...#" << m_nIndex << endl;
				}
			}						
		}
	}

	return bResult; 
}

BOOL CNoise::SetListFilter(CStringList& strOrgList, CStringList& strRetList, int nFilter/*=0*/)
{
	BOOL	bResult = FALSE; 
	if ((strOrgList.IsEmpty() == TRUE) || (nFilter == 0))
	{
		return FALSE; 
	}

	int nFilterInddex = 0;
	POSITION posList = strOrgList.GetHeadPosition();
	while (posList != strOrgList.GetTailPosition())
	{
		if (nFilterInddex % nFilter == 0)
		{
			strRetList.AddTail(strOrgList.GetNext(posList));
		}
		else
		{
			strOrgList.GetNext(posList);
		}
		++nFilterInddex;
	}

	return bResult; 
}

BOOL CNoise::AddSpecialChar(CStringList& strList)
{
	BOOL bResult = TRUE; 
	CStringList nextlist;

	GetSpecialChar(m_strWord, listchar1);
	nextlist.RemoveAll(); 
	SetListFilter(listchar1, nextlist, m_nfilter);
	
	GetSpecialCharset(nextlist, listchar2);
	nextlist.RemoveAll();
	SetListFilter(listchar2, nextlist, m_nfilter);

	GetSpecialCharset(nextlist, listchar3);
	nextlist.RemoveAll();
	SetListFilter(listchar3, nextlist, m_nfilter);

	GetSpecialCharset(nextlist, listchar4);
	nextlist.RemoveAll();
	SetListFilter(listchar4, nextlist, m_nfilter);

	if (m_bOption2 == TRUE)
	{
		strList.AddTail(&listchar1);
	}

	if (m_bOption3 ==TRUE)
	{
		strList.AddTail(&listchar2);
	}

	if (m_bOption4 == TRUE)
	{
		strList.AddTail(&listchar3);
	}

	if (m_bOption5 == TRUE)
	{
		strList.AddTail(&nextlist);
	}

	return bResult; 
}

BOOL CNoise::GetSpecialChar(CString strKey, CStringList& strList)
{
	BOOL bResult = TRUE;

	if (strKey.GetLength() > NUM_START_ADDCHAR)
	{
		for (int i = NUM_START_ADDCHAR; i <= strKey.GetLength() - 1; ++i)
		{
			POSITION posSpecialChar = m_strlspecialChar.GetHeadPosition();
			
			while (posSpecialChar != m_strlspecialChar.GetTailPosition())
			{
				CString strResult = strKey;
				strResult.Insert(i, m_strlspecialChar.GetNext(posSpecialChar));
				strList.AddTail(strResult);
				++m_nIndex;
				cout << "변환 작업중...#" << m_nIndex << endl;
			}
		}
	}	

	return bResult;
}

BOOL CNoise::GetSpecialCharset(CStringList& strList1, CStringList& strList2)
{
	BOOL bResult = TRUE;

	POSITION posList1;
	posList1 = strList1.GetHeadPosition();

	while (posList1 != strList1.GetTailPosition())
	{
		CString	 strKey = _T("");
		strKey = strList1.GetNext(posList1);
		GetSpecialChar(strKey, strList2);
	}

	return bResult;
}
