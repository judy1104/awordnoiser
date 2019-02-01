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
	m_strlspecialChar.AddTail(_T("££"));
	m_strlspecialChar.AddTail(_T("£¦"));
	m_strlspecialChar.AddTail(_T("£ª"));
	m_strlspecialChar.AddTail(_T("£À"));
	m_strlspecialChar.AddTail(_T("¡×"));
	m_strlspecialChar.AddTail(_T("¡Ø"));
	m_strlspecialChar.AddTail(_T("¡Ù"));
	m_strlspecialChar.AddTail(_T("¡Ú"));
	m_strlspecialChar.AddTail(_T("¡Û"));
	m_strlspecialChar.AddTail(_T("¡Ü"));
	m_strlspecialChar.AddTail(_T("¡Ý"));
	m_strlspecialChar.AddTail(_T("¡Þ"));
	m_strlspecialChar.AddTail(_T("¡ß"));
	m_strlspecialChar.AddTail(_T("¡à"));
	m_strlspecialChar.AddTail(_T("¡á"));
	m_strlspecialChar.AddTail(_T("¡â"));
	m_strlspecialChar.AddTail(_T("¡ã"));
	m_strlspecialChar.AddTail(_T("¡ä"));
	m_strlspecialChar.AddTail(_T("¡å"));
	m_strlspecialChar.AddTail(_T("¢·"));
	m_strlspecialChar.AddTail(_T("¢¸"));
	m_strlspecialChar.AddTail(_T("¢¹"));
	m_strlspecialChar.AddTail(_T("¢º"));
	m_strlspecialChar.AddTail(_T("¢»"));
	m_strlspecialChar.AddTail(_T("¢¼"));
	m_strlspecialChar.AddTail(_T("¢½"));
	m_strlspecialChar.AddTail(_T("¢¾"));
	m_strlspecialChar.AddTail(_T("¢¿"));
	m_strlspecialChar.AddTail(_T("¢À"));
	m_strlspecialChar.AddTail(_T("¢Á"));
	m_strlspecialChar.AddTail(_T("¢Â"));
	m_strlspecialChar.AddTail(_T("¢Ã"));
	m_strlspecialChar.AddTail(_T("¢Ä"));
	m_strlspecialChar.AddTail(_T("¢Å"));
	m_strlspecialChar.AddTail(_T("¢Æ"));
	m_strlspecialChar.AddTail(_T("¢Ç"));
	m_strlspecialChar.AddTail(_T("¢È"));
	m_strlspecialChar.AddTail(_T("¢É"));
	m_strlspecialChar.AddTail(_T("¢Ê"));
	m_strlspecialChar.AddTail(_T("¢Ë"));
	m_strlspecialChar.AddTail(_T("¢Ì"));
	m_strlspecialChar.AddTail(_T("¢Í"));
	m_strlspecialChar.AddTail(_T("¢Î"));
	m_strlspecialChar.AddTail(_T("¢Ï"));
	m_strlspecialChar.AddTail(_T("¢Ú"));
	m_strlspecialChar.AddTail(_T("¢Û"));
	m_strlspecialChar.AddTail(_T("¢Ü"));
	m_strlspecialChar.AddTail(_T("¢Ý"));
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
	
	strChar.MakeUpper();

	TCHAR* szChar; 
	szChar = (LPTSTR)(LPCTSTR)strChar;
	int iAscii = __toascii(*(szChar));

	return (iAscii - NUM_START_ASCII);
}

BOOL CNoise::GetChangespelling(CStringList& strList)
{
	BOOL bResult = TRUE;
	if (m_strWord.IsEmpty() == TRUE)
	{
		return FALSE; 
	}

	ChangeSpelling(m_strWord);

	// º¹»ç
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
			CString strnew = m_strChange[GetCharcode(strChar)][i];
			if (strnew.IsEmpty() == FALSE)
			{
				strResult.Replace(strChar, strnew);
				m_setwords.insert(strResult);
			}			
		}
	}

	return bResult; 
}

BOOL CNoise::AddSpecialChar(CStringList& strList)
{
	BOOL bResult = TRUE; 

	CStringList listchar1;
	CStringList listchar2;
	CStringList listchar3;
	CStringList listchar4;

	GetSpecialChar(m_strWord, listchar1);
	GetSpecialCharset(listchar1, listchar2);
	GetSpecialCharset(listchar2, listchar3);
	GetSpecialCharset(listchar3, listchar4);

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
		strList.AddTail(&listchar4);
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

	while (posList1 != strList1.GetHeadPosition())
	{
		CString	 strKey = _T("");
		strKey = strList1.GetNext(posList1);
		GetSpecialChar(strKey, strList2);
	}

	return bResult;
}
