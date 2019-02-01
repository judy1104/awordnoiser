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
		ChangeSpelling(strList);
	}
	
	if ((m_bOption2 | m_bOption3 | m_bOption4 | m_bOption5) == TRUE)
	{
		ChangeSpelling(strList);
	}

	return bResult; 
}

BOOL CNoise::ChangeSpelling(CStringList& strList)
{
	BOOL bResult = TRUE;


	return bResult;
}

BOOL CNoise::AddSpecialChar(CStringList& strList)
{
	BOOL bResult = TRUE; 

	CStringList listchar1;
	CStringList listchar2;
	CStringList listchar3;
	CStringList listchar4;

	GetSpecialChar1(listchar1);
	GetSpecialChar2(listchar1, listchar2);
	GetSpecialChar3(listchar2, listchar3);
	GetSpecialChar4(listchar3, listchar4);

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

BOOL CNoise::GetSpecialChar1(CStringList& strList)
{
	BOOL bResult = TRUE;


	return bResult;
}

BOOL CNoise::GetSpecialChar2(CStringList& strList1, CStringList& strList2)
{
	BOOL bResult = TRUE;


	return bResult;
}

BOOL CNoise::GetSpecialChar3(CStringList& strList2, CStringList& strList3)
{
	BOOL bResult = TRUE;


	return bResult;
}

BOOL CNoise::GetSpecialChar4(CStringList& strList3, CStringList& strList4)
{
	BOOL bResult = TRUE;


	return bResult;
}

BOOL CNoise::GetSpecialChar5(CStringList& strList4, CStringList& strList5)
{
	BOOL bResult = TRUE;


	return bResult;
}