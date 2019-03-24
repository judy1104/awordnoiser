#pragma once
#include <iostream>
#include <set>

using namespace std;

#define NUM_CNT_SPELLING		26
#define NUM_CNT_CHANGECHAR		10
#define NUM_START_ADDCHAR		1
#define NUM_START_ASCII_UPPER	65
#define NUM_START_ASCII_LOWER	97

class CNoise
{
public:
	CNoise(CString strWord, int nFilter = 0, BOOL bOption1 = TRUE, BOOL bOption2 = TRUE, BOOL bOption3 = TRUE, BOOL bOption4 = TRUE, BOOL bOption5 = TRUE);
	~CNoise();
	BOOL GetWordList(CStringList& strList);

private:	
	int GetCharcode(CString strChar);
	BOOL GetChangespelling(CStringList& strList);
	BOOL ChangeSpelling(CString strWord);
	BOOL SetListFilter(CStringList& strOrgList, CStringList& strRetList, int nFilter=0);
	BOOL AddSpecialChar(CStringList& strList);

	BOOL GetSpecialChar(CString strKey, CStringList& strList);
	BOOL GetSpecialCharset(CStringList& strList1, CStringList& strList2);

private:
	int			m_nIndex = 0;
	CString		m_strWord = _T("");
	int			m_nfilter = 0;
	BOOL		m_bOption1 = FALSE;
	BOOL		m_bOption2 = FALSE;
	BOOL		m_bOption3 = FALSE;
	BOOL		m_bOption4 = FALSE;
	BOOL		m_bOption5 = FALSE;	

	CStringList m_strlspecialChar; 
	CStringList listchar1;
	CStringList listchar2;
	CStringList listchar3;
	CStringList listchar4;

	set<CString> m_setwords;

// 	CString m_strUpper[NUM_CNT_SPELLING] = {
// 		_T("A"), _T("B"), _T("C"), _T("D"), _T("E"), _T("F"), _T("G"), _T("H"), _T("I"), _T("J"),
// 		_T("K"), _T("L"), _T("M"), _T("N"), _T("O"), _T("P"),_T("Q"),_T("R"), _T("S"), _T("T"),
// 		_T("U"), _T("V"), _T("W"), _T("X"), _T("Y"), _T("Z") };
// 
// 	CString m_strLower[NUM_CNT_SPELLING] = { _T("a"), _T("b"), _T("c"), _T("d"), _T("e"), _T("f"),_T("g"), _T("h"),_T("i"),_T("j"),
// 		_T("k"), _T("l"), _T("m"), _T("n"), _T("o"), _T("p"),_T("q"), _T("r"),_T("s"),_T("t"),
// 		_T("u"), _T("v"), _T("w"), _T("x"), _T("y"), _T("z") };

	CString m_strChange[NUM_CNT_SPELLING][NUM_CNT_CHANGECHAR] = {
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��") },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��") },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("����"), _T("����"), _T("|��"), _T("��|"),_T("��|"), _T("|��"), _T("��"), _T("��") },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),	_T("��"), _T("��"), },
		{ _T("��"),	_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("0"),  _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��") },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), }
	};
};