#pragma once


#define TDialogParentClass		CPropertyPage
								

// CLayerProps dialog

class CLayerProps : public TDialogParentClass
{
	DECLARE_DYNAMIC(CLayerProps)

public:
	CLayerProps();
	virtual ~CLayerProps();

	CToolTipCtrl	m_Tooltip;
	CString			m_strToolTipText;

// Dialog Data
	enum { IDD = IDD_LAYER_PROPS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	BOOL m_bUseSineX;
	BOOL m_bUseSineY;
	BOOL m_bUseSineR;
	BOOL m_bUseSineA;

	int m_ArgModeX_F;
	int m_ArgModeX_B;
	int m_ArgModeX_A;
	int m_ArgModeX_P;

	int m_ArgModeY_F;
	int m_ArgModeY_B;
	int m_ArgModeY_A;
	int m_ArgModeY_P;

	int m_ArgModeR_F;
	int m_ArgModeR_B;
	int m_ArgModeR_A;
	int m_ArgModeR_P;

	int m_ArgModeA_F;
	int m_ArgModeA_B;
	int m_ArgModeA_A;
	int m_ArgModeA_P;

	CString	m_strArgModeX_F;
	CString	m_strArgModeX_B;
	CString	m_strArgModeX_A;
	CString	m_strArgModeX_P;

	CString	m_strArgModeY_F;
	CString	m_strArgModeY_B;
	CString	m_strArgModeY_A;
	CString	m_strArgModeY_P;

	CString	m_strArgModeR_F;
	CString	m_strArgModeR_B;
	CString	m_strArgModeR_A;
	CString	m_strArgModeR_P;

	CString	m_strArgModeA_F;
	CString	m_strArgModeA_B;
	CString	m_strArgModeA_A;
	CString	m_strArgModeA_P;

protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

public:
	afx_msg void OnBnClickedColorFg();
	afx_msg void OnBnClickedColorBg();

	afx_msg void OnCbnSelchangeArgmodeXFreq();
	afx_msg void OnCbnSelchangeArgmodeXBase();
	afx_msg void OnCbnSelchangeArgmodeXAmp();
	afx_msg void OnCbnSelchangeArgmodeXPhase();

	afx_msg void OnCbnSelchangeArgmodeYFreq();
	afx_msg void OnCbnSelchangeArgmodeYBase();
	afx_msg void OnCbnSelchangeArgmodeYAmp();
	afx_msg void OnCbnSelchangeArgmodeYPhase();

	afx_msg void OnCbnSelchangeArgmodeRFreq();
	afx_msg void OnCbnSelchangeArgmodeRBase();
	afx_msg void OnCbnSelchangeArgmodeRAmp();
	afx_msg void OnCbnSelchangeArgmodeRPhase();

	afx_msg void OnCbnSelchangeArgmodeAFreq();
	afx_msg void OnCbnSelchangeArgmodeABase();
	afx_msg void OnCbnSelchangeArgmodeAAmp();
	afx_msg void OnCbnSelchangeArgmodeAPhase();
	
	afx_msg void OnBnClickedUseSineX();
	afx_msg void OnBnClickedUseSineY();
	afx_msg void OnBnClickedUseSineR();
	afx_msg void OnBnClickedUseSineA();

	afx_msg void OnEnUpdateArgmodeXFreqVal();
	afx_msg void OnEnUpdateArgmodeXBaseVal();
	afx_msg void OnEnUpdateArgmodeXAmpVal();
	afx_msg void OnEnUpdateArgmodeXPhaseVal();

	afx_msg void OnEnUpdateArgmodeYFreqVal();
	afx_msg void OnEnUpdateArgmodeYBaseVal();
	afx_msg void OnEnUpdateArgmodeYAmpVal();
	afx_msg void OnEnUpdateArgmodeYPhaseVal();

	afx_msg void OnEnUpdateArgmodeRFreqVal();
	afx_msg void OnEnUpdateArgmodeRBaseVal();
	afx_msg void OnEnUpdateArgmodeRAmpVal();
	afx_msg void OnEnUpdateArgmodeRPhaseVal();

	afx_msg void OnEnUpdateArgmodeAFreqVal();
	afx_msg void OnEnUpdateArgmodeABaseVal();
	afx_msg void OnEnUpdateArgmodeAAmpVal();
	afx_msg void OnEnUpdateArgmodeAPhaseVal();
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg BOOL OnTtnNeedText(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedClearTexture();
	afx_msg void OnBnClickedClearVerts();
	virtual void OnOK();
};
