
// Task3-5(my).h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTask35myApp:
// �� Ŭ������ ������ ���ؼ��� Task3-5(my).cpp�� �����Ͻʽÿ�.
//

class CTask35myApp : public CWinApp
{
public:
	CTask35myApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTask35myApp theApp;