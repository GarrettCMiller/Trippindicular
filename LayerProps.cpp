// LayerProps.cpp : implementation file
//

#include "stdafx.h"
#include "Trippindicular.h"
#include "LayerProps.h"

#include "GlobalFuncs.h"

// CLayerProps dialog

IMPLEMENT_DYNAMIC(CLayerProps, TDialogParentClass)

CLayerProps::CLayerProps()
	: TDialogParentClass(CLayerProps::IDD)
	, m_bUseSineX(FALSE)
	, m_bUseSineY(FALSE)
	, m_bUseSineR(FALSE)
	, m_bUseSineA(FALSE)
	, m_ArgModeX_F(0)
	, m_ArgModeX_B(0)
	, m_ArgModeX_A(0)
	, m_ArgModeX_P(0)
	, m_ArgModeY_F(0)
	, m_ArgModeY_B(0)
	, m_ArgModeY_A(0)
	, m_ArgModeY_P(0)
	, m_ArgModeR_F(0)
	, m_ArgModeR_B(0)
	, m_ArgModeR_A(0)
	, m_ArgModeR_P(0)
	, m_ArgModeA_F(0)
	, m_ArgModeA_B(0)
	, m_ArgModeA_A(0)
	, m_ArgModeA_P(0)
{

}

CLayerProps::~CLayerProps()
{
}

void CLayerProps::DoDataExchange(CDataExchange* pDX)
{
	TDialogParentClass::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_USE_SINE_X, m_bUseSineX);
	DDX_Check(pDX, IDC_USE_SINE_Y, m_bUseSineY);
	DDX_Check(pDX, IDC_USE_SINE_R, m_bUseSineR);
	DDX_Check(pDX, IDC_USE_SINE_A, m_bUseSineA);

	//DDV_MinMaxInt(pDX, m_ArgModeX_F, 0, 4);

	DDX_CBIndex(pDX, IDC_ARGMODE_X_FREQ, m_ArgModeX_F);
	DDX_CBIndex(pDX, IDC_ARGMODE_X_BASE, m_ArgModeX_B);
	DDX_CBIndex(pDX, IDC_ARGMODE_X_AMP, m_ArgModeX_A);
	DDX_CBIndex(pDX, IDC_ARGMODE_X_PHASE, m_ArgModeX_P);

	DDX_CBIndex(pDX, IDC_ARGMODE_Y_FREQ, m_ArgModeY_F);
	DDX_CBIndex(pDX, IDC_ARGMODE_Y_BASE, m_ArgModeY_B);
	DDX_CBIndex(pDX, IDC_ARGMODE_Y_AMP, m_ArgModeY_A);
	DDX_CBIndex(pDX, IDC_ARGMODE_Y_PHASE, m_ArgModeY_P);

	DDX_CBIndex(pDX, IDC_ARGMODE_R_FREQ, m_ArgModeR_F);
	DDX_CBIndex(pDX, IDC_ARGMODE_R_BASE, m_ArgModeR_B);
	DDX_CBIndex(pDX, IDC_ARGMODE_R_AMP, m_ArgModeR_A);
	DDX_CBIndex(pDX, IDC_ARGMODE_R_PHASE, m_ArgModeR_P);

	DDX_CBIndex(pDX, IDC_ARGMODE_A_FREQ, m_ArgModeA_F);
	DDX_CBIndex(pDX, IDC_ARGMODE_A_BASE, m_ArgModeA_B);
	DDX_CBIndex(pDX, IDC_ARGMODE_A_AMP, m_ArgModeA_A);
	DDX_CBIndex(pDX, IDC_ARGMODE_A_PHASE, m_ArgModeA_P);
	
	DDX_Text(pDX, IDC_ARGMODE_X_FREQ_VAL, m_strArgModeX_F);
	DDX_Text(pDX, IDC_ARGMODE_X_BASE_VAL, m_strArgModeX_B);
	DDX_Text(pDX, IDC_ARGMODE_X_AMP_VAL, m_strArgModeX_A);
	DDX_Text(pDX, IDC_ARGMODE_X_PHASE_VAL, m_strArgModeX_P);

	DDX_Text(pDX, IDC_ARGMODE_Y_FREQ_VAL, m_strArgModeY_F);
	DDX_Text(pDX, IDC_ARGMODE_Y_BASE_VAL, m_strArgModeY_B);
	DDX_Text(pDX, IDC_ARGMODE_Y_AMP_VAL, m_strArgModeY_A);
	DDX_Text(pDX, IDC_ARGMODE_Y_PHASE_VAL, m_strArgModeY_P);

	DDX_Text(pDX, IDC_ARGMODE_R_FREQ_VAL, m_strArgModeR_F);
	DDX_Text(pDX, IDC_ARGMODE_R_BASE_VAL, m_strArgModeR_B);
	DDX_Text(pDX, IDC_ARGMODE_R_AMP_VAL, m_strArgModeR_A);
	DDX_Text(pDX, IDC_ARGMODE_R_PHASE_VAL, m_strArgModeR_P);

	DDX_Text(pDX, IDC_ARGMODE_A_FREQ_VAL, m_strArgModeA_F);
	DDX_Text(pDX, IDC_ARGMODE_A_BASE_VAL, m_strArgModeA_B);
	DDX_Text(pDX, IDC_ARGMODE_A_AMP_VAL, m_strArgModeA_A);
	DDX_Text(pDX, IDC_ARGMODE_A_PHASE_VAL, m_strArgModeA_P);
}


BEGIN_MESSAGE_MAP(CLayerProps, TDialogParentClass)
	ON_BN_CLICKED(IDC_COLOR_FG, &CLayerProps::OnBnClickedColorFg)
	ON_BN_CLICKED(IDC_COLOR_BG, &CLayerProps::OnBnClickedColorBg)

	ON_CBN_SELCHANGE(IDC_ARGMODE_X_FREQ, &CLayerProps::OnCbnSelchangeArgmodeXFreq)
	ON_CBN_SELCHANGE(IDC_ARGMODE_X_BASE, &CLayerProps::OnCbnSelchangeArgmodeXBase)
	ON_CBN_SELCHANGE(IDC_ARGMODE_X_AMP, &CLayerProps::OnCbnSelchangeArgmodeXAmp)
	ON_CBN_SELCHANGE(IDC_ARGMODE_X_PHASE, &CLayerProps::OnCbnSelchangeArgmodeXPhase)

	ON_CBN_SELCHANGE(IDC_ARGMODE_Y_FREQ, &CLayerProps::OnCbnSelchangeArgmodeYFreq)
	ON_CBN_SELCHANGE(IDC_ARGMODE_Y_BASE, &CLayerProps::OnCbnSelchangeArgmodeYBase)
	ON_CBN_SELCHANGE(IDC_ARGMODE_Y_AMP, &CLayerProps::OnCbnSelchangeArgmodeYAmp)
	ON_CBN_SELCHANGE(IDC_ARGMODE_Y_PHASE, &CLayerProps::OnCbnSelchangeArgmodeYPhase)

	ON_CBN_SELCHANGE(IDC_ARGMODE_R_FREQ, &CLayerProps::OnCbnSelchangeArgmodeRFreq)
	ON_CBN_SELCHANGE(IDC_ARGMODE_R_BASE, &CLayerProps::OnCbnSelchangeArgmodeRBase)
	ON_CBN_SELCHANGE(IDC_ARGMODE_R_AMP, &CLayerProps::OnCbnSelchangeArgmodeRAmp)
	ON_CBN_SELCHANGE(IDC_ARGMODE_R_PHASE, &CLayerProps::OnCbnSelchangeArgmodeRPhase)

	ON_CBN_SELCHANGE(IDC_ARGMODE_A_FREQ, &CLayerProps::OnCbnSelchangeArgmodeAFreq)
	ON_CBN_SELCHANGE(IDC_ARGMODE_A_BASE, &CLayerProps::OnCbnSelchangeArgmodeABase)
	ON_CBN_SELCHANGE(IDC_ARGMODE_A_AMP, &CLayerProps::OnCbnSelchangeArgmodeAAmp)
	ON_CBN_SELCHANGE(IDC_ARGMODE_A_PHASE, &CLayerProps::OnCbnSelchangeArgmodeAPhase)
	
	ON_BN_CLICKED(IDC_USE_SINE_X, &CLayerProps::OnBnClickedUseSineX)
	ON_BN_CLICKED(IDC_USE_SINE_Y, &CLayerProps::OnBnClickedUseSineY)
	ON_BN_CLICKED(IDC_USE_SINE_R, &CLayerProps::OnBnClickedUseSineR)
	ON_BN_CLICKED(IDC_USE_SINE_A, &CLayerProps::OnBnClickedUseSineA)
	
	ON_EN_UPDATE(IDC_ARGMODE_X_FREQ_VAL, &CLayerProps::OnEnUpdateArgmodeXFreqVal)
	ON_EN_UPDATE(IDC_ARGMODE_X_BASE_VAL, &CLayerProps::OnEnUpdateArgmodeXBaseVal)
	ON_EN_UPDATE(IDC_ARGMODE_X_AMP_VAL, &CLayerProps::OnEnUpdateArgmodeXAmpVal)
	ON_EN_UPDATE(IDC_ARGMODE_X_PHASE_VAL, &CLayerProps::OnEnUpdateArgmodeXPhaseVal)

	ON_EN_UPDATE(IDC_ARGMODE_Y_FREQ_VAL, &CLayerProps::OnEnUpdateArgmodeYFreqVal)
	ON_EN_UPDATE(IDC_ARGMODE_Y_BASE_VAL, &CLayerProps::OnEnUpdateArgmodeYBaseVal)
	ON_EN_UPDATE(IDC_ARGMODE_Y_AMP_VAL, &CLayerProps::OnEnUpdateArgmodeYAmpVal)
	ON_EN_UPDATE(IDC_ARGMODE_Y_PHASE_VAL, &CLayerProps::OnEnUpdateArgmodeYPhaseVal)

	ON_EN_UPDATE(IDC_ARGMODE_R_FREQ_VAL, &CLayerProps::OnEnUpdateArgmodeRFreqVal)
	ON_EN_UPDATE(IDC_ARGMODE_R_BASE_VAL, &CLayerProps::OnEnUpdateArgmodeRBaseVal)
	ON_EN_UPDATE(IDC_ARGMODE_R_AMP_VAL, &CLayerProps::OnEnUpdateArgmodeRAmpVal)
	ON_EN_UPDATE(IDC_ARGMODE_R_PHASE_VAL, &CLayerProps::OnEnUpdateArgmodeRPhaseVal)

	ON_EN_UPDATE(IDC_ARGMODE_A_FREQ_VAL, &CLayerProps::OnEnUpdateArgmodeAFreqVal)
	ON_EN_UPDATE(IDC_ARGMODE_A_BASE_VAL, &CLayerProps::OnEnUpdateArgmodeABaseVal)
	ON_EN_UPDATE(IDC_ARGMODE_A_AMP_VAL, &CLayerProps::OnEnUpdateArgmodeAAmpVal)
	ON_EN_UPDATE(IDC_ARGMODE_A_PHASE_VAL, &CLayerProps::OnEnUpdateArgmodeAPhaseVal)
	
	ON_WM_CREATE()

	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, &CLayerProps::OnTtnNeedText)
	//ON_NOTIFY_EX(TTN_GETDISPINFO, 0, &CLayerProps::OnTtnNeedText)

	ON_BN_CLICKED(IDC_CLEAR_TEXTURE, &CLayerProps::OnBnClickedClearTexture)
	ON_BN_CLICKED(IDC_CLEAR_VERTS, &CLayerProps::OnBnClickedClearVerts)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

#define SET_TOOLTIP(id)		GetDlgItem(id)->GetWindowRect(&rect); ScreenToClient(&rect); m_Tooltip.AddTool(this, LPSTR_TEXTCALLBACK, &rect, id);
//////////////////////////////////////////////////////////////////////////
// CLayerProps message handlers

int CLayerProps::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CLayerProps::OnInitDialog()
{
	CDialog::OnInitDialog();

	EnableToolTips(TRUE);
	//EnableTrackingToolTips(TRUE);

	if (!::IsWindow(m_Tooltip.GetSafeHwnd()))
	{
		m_Tooltip.Create(this, TTS_ALWAYSTIP);
	}
	
	m_Tooltip.Activate(true);

	//m_Tooltip.SetT

	CRect rect;

	/*SET_TOOLTIP(IDC_COLOR_FG);
	SET_TOOLTIP(IDC_COLOR_BG);

	SET_TOOLTIP(IDC_USE_SINE_X);*/

	CVisualizer& viz = theApp.m_Viz;

	m_strArgModeX_F = FloatToString(viz.VelArgsX.freq).c_str();
	m_strArgModeX_B = FloatToString(viz.VelArgsX.base).c_str();
	m_strArgModeX_A = FloatToString(viz.VelArgsX.amp).c_str();
	m_strArgModeX_P = FloatToString(viz.VelArgsX.phase).c_str();

	m_strArgModeY_F = FloatToString(viz.VelArgsY.freq).c_str();
	m_strArgModeY_B = FloatToString(viz.VelArgsY.base).c_str();
	m_strArgModeY_A = FloatToString(viz.VelArgsY.amp).c_str();
	m_strArgModeY_P = FloatToString(viz.VelArgsY.phase).c_str();

	m_strArgModeR_F = FloatToString(viz.VelArgsR.freq).c_str();
	m_strArgModeR_B = FloatToString(viz.VelArgsR.base).c_str();
	m_strArgModeR_A = FloatToString(viz.VelArgsR.amp).c_str();
	m_strArgModeR_P = FloatToString(viz.VelArgsR.phase).c_str();

	m_strArgModeA_F = FloatToString(viz.VelArgsA.freq).c_str();
	m_strArgModeA_B = FloatToString(viz.VelArgsA.base).c_str();
	m_strArgModeA_A = FloatToString(viz.VelArgsA.amp).c_str();
	m_strArgModeA_P = FloatToString(viz.VelArgsA.phase).c_str();

	m_ArgModeX_F	= viz.ArgModeX.freq;
	m_ArgModeX_B	= viz.ArgModeX.base;
	m_ArgModeX_A	= viz.ArgModeX.amp;
	m_ArgModeX_P	= viz.ArgModeX.phase;

	m_ArgModeY_F	= viz.ArgModeY.freq;
	m_ArgModeY_B	= viz.ArgModeY.base;
	m_ArgModeY_A	= viz.ArgModeY.amp;
	m_ArgModeY_P	= viz.ArgModeY.phase;

	m_ArgModeR_F	= viz.ArgModeR.freq;
	m_ArgModeR_B	= viz.ArgModeR.base;
	m_ArgModeR_A	= viz.ArgModeR.amp;
	m_ArgModeR_P	= viz.ArgModeR.phase;

	m_ArgModeA_F	= viz.ArgModeA.freq;
	m_ArgModeA_B	= viz.ArgModeA.base;
	m_ArgModeA_A	= viz.ArgModeA.amp;
	m_ArgModeA_P	= viz.ArgModeA.phase;
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CLayerProps::OnTtnNeedText(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(id);

	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
	UINT_PTR nID = pNMHDR->idFrom;
	BOOL bRet = FALSE;

	if (pTTT->uFlags & TTF_IDISHWND)
	{
	  // idFrom is actually the HWND of the tool
	  nID = ::GetDlgCtrlID((HWND)nID);
	  if(nID)
	  {
		 TCHAR szBuff[64];
		 _stprintf_s(szBuff, sizeof(szBuff) / sizeof(TCHAR), 
			_T("Control ID = %d"), nID);
		 pTTT->lpszText = szBuff;
		 pTTT->hinst = AfxGetResourceHandle();
		 bRet = TRUE;
	  }
	}

	*pResult = 0;

	return bRet;
}

//////////////////////////////////////////////////////////////////////////

BOOL CLayerProps::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	LPNMHDR pNmHdr = (LPNMHDR) lParam;
	UINT code = pNmHdr->code;

	if ( code == TTN_NEEDTEXT ) 
	{
		int ctrlID = FromHandle((HWND)(pNmHdr->idFrom))->GetDlgCtrlID() ;
		LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT) lParam;

		// DISPLAY THE TOOLTIP
		CString strToolTipText;

		strToolTipText = "Hello World!";
		//if (GetToolTip(ctrlID, strToolTipText)) // Your own function
		//{
		m_strToolTipText = strToolTipText;
		LPCTSTR tcpszText = m_strToolTipText;
		lpttt->lpszText = (LPTSTR )(tcpszText);
		//}

	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CLayerProps::OnBnClickedClearTexture()
{
	SAFE_CALL(theApp.m_Viz.ClearTextures())
}

void CLayerProps::OnBnClickedClearVerts()
{
	SAFE_CALL(theApp.m_Viz.ClearVertices())
}

void CLayerProps::OnBnClickedColorFg()
{
	CColorDialog dlg;
	
	if (dlg.DoModal() == IDOK)
	{
		SAFE_CALL(theApp.m_Viz.m_cFGColor = dlg.GetColor())
	}
}

void CLayerProps::OnBnClickedColorBg()
{
	CColorDialog dlg;
	
	if (dlg.DoModal() == IDOK)
	{
		SAFE_CALL(theApp.m_Viz.m_cBGColor = dlg.GetColor())
		SAFE_CALL(theApp.m_Viz.m_cBGColor.Normalize())
		//theApp.m_Viz.m_cBGColor.SetAlpha(1.0f);
	}
}

//////////////////////////////////////////////////////////////////////////

void CLayerProps::OnCbnSelchangeArgmodeXFreq()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeX.freq = m_ArgModeX_F)
}

void CLayerProps::OnCbnSelchangeArgmodeXBase()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeX.base = m_ArgModeX_B)
}

void CLayerProps::OnCbnSelchangeArgmodeXAmp()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeX.amp = m_ArgModeX_A)
}

void CLayerProps::OnCbnSelchangeArgmodeXPhase()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeX.phase = m_ArgModeX_P)
}

//////////////////////////////////////////////////////////////////////////

void CLayerProps::OnCbnSelchangeArgmodeYFreq()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeY.freq = m_ArgModeY_F)
}

void CLayerProps::OnCbnSelchangeArgmodeYBase()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeY.base = m_ArgModeY_B)
}

void CLayerProps::OnCbnSelchangeArgmodeYAmp()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeY.amp = m_ArgModeY_A)
}

void CLayerProps::OnCbnSelchangeArgmodeYPhase()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeY.phase = m_ArgModeY_P)
}

//////////////////////////////////////////////////////////////////////////

void CLayerProps::OnCbnSelchangeArgmodeRFreq()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeR.freq = m_ArgModeR_F)
}

void CLayerProps::OnCbnSelchangeArgmodeRBase()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeR.base = m_ArgModeR_B)
}

void CLayerProps::OnCbnSelchangeArgmodeRAmp()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeR.amp = m_ArgModeR_A)
}

void CLayerProps::OnCbnSelchangeArgmodeRPhase()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeR.phase = m_ArgModeR_P)
}

//////////////////////////////////////////////////////////////////////////

void CLayerProps::OnCbnSelchangeArgmodeAFreq()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeA.freq = m_ArgModeA_F)
}

void CLayerProps::OnCbnSelchangeArgmodeABase()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeA.base = m_ArgModeA_B)
}

void CLayerProps::OnCbnSelchangeArgmodeAAmp()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeA.amp = m_ArgModeA_A)
}

void CLayerProps::OnCbnSelchangeArgmodeAPhase()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.ArgModeA.phase = m_ArgModeA_P)
}

//////////////////////////////////////////////////////////////////////////

void CLayerProps::OnBnClickedUseSineX()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.UseSine[0] = m_bUseSineX)
}

void CLayerProps::OnBnClickedUseSineY()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.UseSine[1] = m_bUseSineY)
}

void CLayerProps::OnBnClickedUseSineR()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.UseSine[2] = m_bUseSineR)
}

void CLayerProps::OnBnClickedUseSineA()
{
	UpdateData();
	SAFE_CALL(theApp.m_Viz.UseSine[3] = m_bUseSineA)
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#define EDIT_VAL(str, arr)	if (IsANumber(str))\
							{\
								SAFE_CALL(theApp.m_Viz.arr = atof(str.c_str()))\
							}\
							else \
							{\
								if (str == "t")\
								{\
									SAFE_CALL(theApp.m_Viz.arr = theApp.m_Viz.m_tTime.Get())\
								}\
								else\
									SAFE_CALL(theApp.m_Viz.arr = 0)\
							}

//////////////////////////////////////////////////////////////////////////

void CLayerProps::OnEnUpdateArgmodeXFreqVal()
{
	UpdateData();

	String str = m_strArgModeX_F;

	//see above macro
	EDIT_VAL(str, VelArgsX.freq)
}

void CLayerProps::OnEnUpdateArgmodeXBaseVal()
{
	UpdateData();

	String str = m_strArgModeX_B;

	//see above macro
	EDIT_VAL(str, VelArgsX.base)
}

void CLayerProps::OnEnUpdateArgmodeXAmpVal()
{
	UpdateData();

	String str = m_strArgModeX_A;

	//see above macro
	EDIT_VAL(str, VelArgsX.amp)
}

void CLayerProps::OnEnUpdateArgmodeXPhaseVal()
{
	UpdateData();

	String str = m_strArgModeX_P;

	//see above macro
	EDIT_VAL(str, VelArgsX.phase)
}

//////////////////////////////////////////////////////////////////////////

void CLayerProps::OnEnUpdateArgmodeYFreqVal()
{
	UpdateData();

	String str = m_strArgModeY_F;

	//see above macro
	EDIT_VAL(str, VelArgsY.freq)
}

void CLayerProps::OnEnUpdateArgmodeYBaseVal()
{
	UpdateData();

	String str = m_strArgModeY_B;

	//see above macro
	EDIT_VAL(str, VelArgsY.base)
}

void CLayerProps::OnEnUpdateArgmodeYAmpVal()
{
	UpdateData();

	String str = m_strArgModeY_A;

	//see above macro
	EDIT_VAL(str, VelArgsY.amp)
}

void CLayerProps::OnEnUpdateArgmodeYPhaseVal()
{
	UpdateData();

	String str = m_strArgModeY_P;

	//see above macro
	EDIT_VAL(str, VelArgsY.phase)
}

//////////////////////////////////////////////////////////////////////////

void CLayerProps::OnEnUpdateArgmodeRFreqVal()
{
	UpdateData();

	String str = m_strArgModeR_F;

	//see above macro
	EDIT_VAL(str, VelArgsR.freq)
}

void CLayerProps::OnEnUpdateArgmodeRBaseVal()
{
	UpdateData();

	String str = m_strArgModeR_B;

	//see above macro
	EDIT_VAL(str, VelArgsR.base)
}

void CLayerProps::OnEnUpdateArgmodeRAmpVal()
{
	UpdateData();

	String str = m_strArgModeR_A;

	//see above macro
	EDIT_VAL(str, VelArgsR.amp)
}

void CLayerProps::OnEnUpdateArgmodeRPhaseVal()
{
	UpdateData();

	String str = m_strArgModeR_P;

	//see above macro
	EDIT_VAL(str, VelArgsR.phase)
}

//////////////////////////////////////////////////////////////////////////

void CLayerProps::OnEnUpdateArgmodeAFreqVal()
{
	UpdateData();

	String str = m_strArgModeA_F;

	//see above macro
	EDIT_VAL(str, VelArgsA.freq)
}

void CLayerProps::OnEnUpdateArgmodeABaseVal()
{
	UpdateData();

	String str = m_strArgModeA_B;

	//see above macro
	EDIT_VAL(str, VelArgsA.base)
}

void CLayerProps::OnEnUpdateArgmodeAAmpVal()
{
	UpdateData();

	String str = m_strArgModeA_A;

	//see above macro
	EDIT_VAL(str, VelArgsA.amp)
}

void CLayerProps::OnEnUpdateArgmodeAPhaseVal()
{
	UpdateData();

	String str = m_strArgModeA_P;

	//see above macro
	EDIT_VAL(str, VelArgsA.phase)
}
void CLayerProps::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	//CPropertyPage::OnOK();
}
