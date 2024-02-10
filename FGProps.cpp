// FGProps.cpp : implementation file
//

#include "stdafx.h"
#include "Trippindicular.h"
#include "FGProps.h"


// CFGProps dialog

IMPLEMENT_DYNAMIC(CFGProps, CPropertyPage)

CFGProps::CFGProps()
	: CPropertyPage(CFGProps::IDD)
{

}

CFGProps::~CFGProps()
{
}

void CFGProps::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFGProps, CPropertyPage)
END_MESSAGE_MAP()


// CFGProps message handlers
