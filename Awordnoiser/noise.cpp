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

BOOL CNoise::GetWordList(CStringList strList)
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

}

BOOL CNoise::AddSpecialChar(CStringList& strList)
{

}

BOOL CNoise::GetSpecialChar1(CStringList& strList)
{

}

BOOL CNoise::GetSpecialChar2(CStringList& strList)
{

}

BOOL CNoise::GetSpecialChar3(CStringList& strList)
{

}

BOOL CNoise::GetSpecialChar4(CStringList& strList)
{

}

BOOL CNoise::GetSpecialChar5(CStringList& strList)
{

}