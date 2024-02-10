#pragma once


// CFGProps dialog

class CFGProps : public CPropertyPage
{
	DECLARE_DYNAMIC(CFGProps)

public:
	CFGProps();
	virtual ~CFGProps();

// Dialog Data
	enum { IDD = IDD_FG_PROPS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
