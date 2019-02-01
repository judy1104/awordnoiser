#pragma once


class CNoise
{
public:
	CNoise(CString strWord, int nFilter = 0, BOOL bOption1 = TRUE, BOOL bOption2 = TRUE, BOOL bOption3 = TRUE, BOOL bOption4 = TRUE, BOOL bOption5 = TRUE);
	~CNoise();
	BOOL GetWordList(CStringList& strList);

private:	
	BOOL ChangeSpelling(CStringList& strList);
	BOOL AddSpecialChar(CStringList& strList);

	BOOL GetSpecialChar1(CStringList& strList);
	BOOL GetSpecialChar2(CStringList& strList1, CStringList& strList2);
	BOOL GetSpecialChar3(CStringList& strList2, CStringList& strList3);
	BOOL GetSpecialChar4(CStringList& strList3, CStringList& strList4);
	BOOL GetSpecialChar5(CStringList& strList4, CStringList& strList5);

private:
	CString		m_strWord = _T("");
	int			m_nfilter = 0;
	BOOL		m_bOption1 = FALSE;
	BOOL		m_bOption2 = FALSE;
	BOOL		m_bOption3 = FALSE;
	BOOL		m_bOption4 = FALSE;
	BOOL		m_bOption5 = FALSE;	
};