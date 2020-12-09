
// BmpSlideShow.h : main header file for the BmpSlideShow application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBmpSlideShowApp:
// See BmpSlideShow.cpp for the implementation of this class
//

class CBmpSlideShowApp : public CWinApp
{
public:
	CBmpSlideShowApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBmpSlideShowApp theApp;
