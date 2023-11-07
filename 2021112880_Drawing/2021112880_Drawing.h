
// 2021112880_Drawing.h: 2021112880_Drawing 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// CMy2021112880DrawingApp:
// 有关此类的实现，请参阅 2021112880_Drawing.cpp
//

class CMy2021112880DrawingApp : public CWinApp
{
public:
	CMy2021112880DrawingApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy2021112880DrawingApp theApp;
