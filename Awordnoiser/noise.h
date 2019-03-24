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
		{ _T("¨Í"), _T("©Í"), _T("£À"), _T("¢£"), _T("¡Ê"), _T("¥Á"), _T("¥Ë"), _T("¥á"), _T("£Á"), _T("£á") },
		{ _T("¨Î"), _T("©Î"), _T("¥Â"), _T("¥â"), _T("£Â"), _T("£â"), },
		{ _T("¨Ï"), _T("©Ï"), _T("¡É"), _T("£Ã"), _T("£ã"), },
		{ _T("¨Ð"), _T("©Ð"), _T("£Ä"), _T("£ä"), },
		{ _T("¨Ñ"), _T("©Ñ"), _T("¡ô"), _T("¢¤"), _T("¥Å"), _T("£Å"), _T("£å") },
		{ _T("¨Ò"), _T("©Ò"), _T("£Æ"), _T("¢µ"), _T("£Æ"), _T("£æ"), },
		{ _T("¨Ó"), _T("©Ó"), _T("£¹"), _T("£Ç"), _T("£ç"), },
		{ _T("¨Ô"), _T("©Ô"), _T("¦¢¦©"), _T("¦²¦¢"), _T("|¦©"), _T("¦§|"),_T("¦²|"), _T("|¦´"), _T("¥Ç"), _T("£è") },
		{ _T("¨Õ"), _T("©Õ"), _T("¥¡"), _T("¥°"), _T("£¡"), _T("£ü"), _T("¢®"), _T("¥É"), },
		{ _T("¨Ö"), _T("©Ö"), _T("£Ê"), _T("£ê"), },
		{ _T("¨×"), _T("©×"), _T("¢Þ"), _T("¥Ê"), _T("¥ê"),	_T("£Ë"), _T("£ë"), },
		{ _T("¨Ø"),	_T("©Ø"), _T("¦¦"), _T("¦±"), _T("¦Å"), _T("¦Æ"), _T("§¤"), _T("£Ì"), _T("£ì"), },
		{ _T("¨Ù"), _T("©Ù"), _T("§©"), _T("¥Ì"), _T("£Í"), _T("£í"), },
		{ _T("¨Ú"), _T("©Ú"), _T("¥Í"), _T("¥ç"), _T("£Î"), _T("£î"), },
		{ _T("¨Û"), _T("©Û"), _T("0"),  _T("¡Û"), _T("¡Ý"), _T("¡Ü"), _T("¢½"), _T("¢¾"), _T("¢Á"), _T("¥ò") },
		{ _T("¨Ü"), _T("©Ü"), _T("¥Ñ"), _T("£Ð"), _T("£ð"), },
		{ _T("¨Ý"), _T("©Ý"), _T("£Ñ"), _T("£ñ"), },
		{ _T("¨Þ"), _T("©Þ"), _T("¢ç"), _T("£Ò"), _T("£ò"), },
		{ _T("¨ß"), _T("©ß"), _T("£Ó"), _T("£ó"), },
		{ _T("¨à"), _T("©à"), _T("¥Ó"), _T("£Ô"), _T("£ô"), },
		{ _T("¨á"), _T("©á"), _T("¡ú"), _T("¥ô"), _T("£Õ"), _T("£õ"), },
		{ _T("¨â"), _T("©â"), _T("¥¥"), _T("¥´"), _T("¡î"), _T("¡ý"), _T("£Ö"), _T("£ö"), },
		{ _T("¨ã"), _T("©ã"), _T("¥ø"), _T("£×"), _T("£÷"), },
		{ _T("¨ä"), _T("©ä"), _T("¥ª"), _T("¥¹"), _T("¥ö"), _T("£Ø"), _T("£ø"), },
		{ _T("¨å"), _T("©å"), _T("¥Ô"), _T("£Ù"), _T("£ù"), },
		{ _T("¨æ"), _T("©æ"), _T("¥Æ"), _T("£Ú"), _T("£ú"), }
	};
};