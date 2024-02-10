// Trippindicular.h : main header file for the Trippindicular application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

#include "GLibMFCApp.h"
#include "Visualizer.h"		//The visualizer class

// CTrippindicularApp:
// See Trippindicular.cpp for the implementation of this class
//


class CTrippindicularApp : public CGLibMFCApp
{
public:
	CTrippindicularApp();
	~CTrippindicularApp();

	//The visualizer
	static CVisualizer		m_Viz;

// Overrides
public:
	virtual BOOL InitInstance();

	static DWORD MainInit(LPVOID data);

	//The main update loop for the visualizer
	static DWORD MainUpdateLoop(LPVOID data);

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTrippindicularApp theApp;