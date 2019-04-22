#pragma once

#define NUM_KO_CNT_SPECIALCHAR1	200
#define NUM_KO_CNT_SPECIALCHAR2	100
#define NUM_KO_CNT_SPECIAL1		170
#define NUM_KO_CNT_SPECIAL2		90
#define UNICODE_KOREAN_START	2752

class CNoiseKor
{
public:
	CNoiseKor();
	~CNoiseKor();
	BOOL GetWordList(CString strWord, CStringList& retList);

private:	
	void GetRandomSpecial(CStringList& strlSpecial);
	BOOL GetSpecialCharAdd(CString strWord, CStringList& retList, int nIndex);
	BOOL AddSpecialChar(CString strWord, CStringList& retList);

	BOOL GetParsedKorean(CString strChar, CString& strParsed);
	BOOL GetParsedKorean_python(CString strChar, CString& strParsed);
	BOOL GetSplitWord(CString strWord, CStringList& retList);

	BOOL GetNewlineWord(CString strWord, CStringList& retList);
	BOOL GetChangeWordset(CString strWord, CStringList& retList, int nIndex);

private:
	CStringList m_strlParsedWord;
	CStringList m_strlLineWord1;
	CStringList m_strlLineWord2;
	CStringList m_strlLineWord3;

	CString m_special1[NUM_KO_CNT_SPECIALCHAR1] = {
		_T("~"), _T("!"), _T("@"), _T("#"), _T("$"), _T("%"), _T("^"), _T("&"), _T("*"), _T("\\"),
		_T("\""), _T("'"), _T("+"), _T("="), _T("`"), _T("|"), _T(":"), _T(";"), _T("-"), _T("_"),
		_T("-"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"),	_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��") ,_T("��"), 
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"), _T("~~"), _T("~~~"),_T("^^"), _T("~~~~~~"), _T("~~~~~~~~~~"), _T("~.~"), _T(";;"), _T(";;;"),
	};

	CString m_special2[NUM_KO_CNT_SPECIALCHAR2] = {
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
	};

	CString hanTable[3][28] = {
		{ _T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"), },
		{ _T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"), },
		{ _T("  "),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"), } 
	};
	
	CString hanTableCho[28][10] = {
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T(""), _T("")},
		{ _T("��"), _T("����"), _T("����"), _T("����"), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("L"), _T("|_"), _T("��"), _T("��"), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("����"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("����"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T("����"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T("") },

		{ _T("��"), _T("����"), _T("TH"), _T("th"), _T("����"), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("0"), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("����"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },

		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
	};

	CString hanTableJung[28][10] = {
		{ _T("��"), _T("|-"), _T("l-"), _T("r"), _T("��"), _T("��"), _T("��"), _T(""), _T(""), _T("") },
		{ _T("��"), _T("H"), _T("l-l"), _T("����"), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("����"), _T("�Ӥ�"), _T("�Ԥ�"), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("-��"), _T("��"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("�ä�"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("�Ť�"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("����"), _T("�Ǥ�"), _T("����"), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },

		{ _T("��"), _T("�Ǥ�"), _T("�Ǥ�"), _T("�Ǥä�"), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("�Ǥ�"), _T("����"), _T("����"), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("T"), _T("t"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("T��"), _T("�Ӥ�"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("�Ӥ�"), _T("�̤ä�"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("�Ӥ�"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("�Ԥ�"), _T("�Ѥ�"), _T("�Ѥä�"), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("�Ԥ�"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("TT"), _T("tt"), _T("�Ԧ�"), _T("�Ӧ�"), _T(""), _T(""), _T(""), _T(""), _T("") },

		{ _T("��"), _T("��"), _T("--"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("�Ѥ�"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T("��"), _T("��"), _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
	};

	CString hanTableJong[28][10] = {
		{ _T(" "), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },

		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },

		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
		{ _T("��"), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T(""), _T("") },
	};
};