
// Awordnoiser.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CAwordnoiserApp:
// �� Ŭ������ ������ ���ؼ��� Awordnoiser.cpp�� �����Ͻʽÿ�.
//

class CAwordnoiserApp : public CWinApp
{
public:
	CAwordnoiserApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CAwordnoiserApp theApp;