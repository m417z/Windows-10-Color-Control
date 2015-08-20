#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"
#include "WindowsThemeColorApi.h"

BOOL CMainDlg::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
	// Center the dialog on the screen
	CenterWindow();

	// Set icons
	HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(hIconSmall, FALSE);

	// Init API and controls
	InitWindowsThemeColorApi();
	GetSettings();

	return TRUE;
}

HBRUSH CMainDlg::OnCtlColorStatic(CDCHandle dc, CStatic wndStatic)
{
	switch(wndStatic.GetDlgCtrlID())
	{
	case IDC_DWM_COLOR:
		return m_dwmBrush;

	case IDC_ACCENT_COLOR:
		return m_accentBrush;
	}

	SetMsgHandled(FALSE);
	return NULL;
}

void CMainDlg::OnAppAbout(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
	dlg.DoModal();
}

void CMainDlg::OnOK(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	SetSettings();
}

void CMainDlg::OnCancel(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	EndDialog(nID);
}

void CMainDlg::OnDwmBtnClick(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	CColorDialog colorDlg(m_dwmColor, CC_FULLOPEN);
	if(colorDlg.DoModal() == IDOK)
	{
		m_dwmColor = colorDlg.GetColor();
		m_dwmBrush = CreateSolidBrush(m_dwmColor);
		CStatic(GetDlgItem(IDC_DWM_COLOR)).Invalidate();
		CButton(GetDlgItem(IDOK)).EnableWindow(TRUE);
	}
}

void CMainDlg::OnAccentBtnClick(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	CColorDialog colorDlg(m_accentColor, CC_FULLOPEN);
	if(colorDlg.DoModal() == IDOK)
	{
		m_accentColor = colorDlg.GetColor();
		m_accentBrush = CreateSolidBrush(m_accentColor);
		CStatic(GetDlgItem(IDC_ACCENT_COLOR)).Invalidate();
		CButton(GetDlgItem(IDOK)).EnableWindow(TRUE);
	}
}

void CMainDlg::OnAccentNewAlgoClick(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	m_newAccentAlgo = IsDlgButtonChecked(IDC_ACCENT_NO_NEW_ALGO) == BST_UNCHECKED;
	CButton(GetDlgItem(IDOK)).EnableWindow(TRUE);
}

void CMainDlg::GetSettings()
{
	m_dwmColor = GetDwmColorizationColor();
	m_dwmBrush = CreateSolidBrush(m_dwmColor);
	CStatic(GetDlgItem(IDC_DWM_COLOR)).Invalidate();

	m_lastNewAccentAlgo = IsNewAutoColorAccentAlgorithm();

	m_newAccentAlgo = m_lastNewAccentAlgo;
	CheckDlgButton(IDC_ACCENT_NO_NEW_ALGO, m_newAccentAlgo ? BST_UNCHECKED : BST_CHECKED);

	m_accentColor = GetAccentColor();
	m_accentBrush = CreateSolidBrush(m_accentColor);
	CStatic(GetDlgItem(IDC_ACCENT_COLOR)).Invalidate();

	CButton(GetDlgItem(IDOK)).EnableWindow(FALSE);
}

void CMainDlg::SetSettings()
{
	COLORREF similarToNewAccentColor = RGB(
		GetRValue(m_accentColor) + (GetRValue(m_accentColor) > 0x7F ? -1 : 1),
		GetGValue(m_accentColor), 
		GetBValue(m_accentColor));

	SetDwmColorizationColor(m_dwmColor);
	SetAutoColorAccentAlgorithm(m_newAccentAlgo);

	// This is necessary to apply the new accent algorithm.
	SetAccentColor(similarToNewAccentColor);
	Sleep(100);

	SetAccentColor(m_accentColor, !m_newAccentAlgo);
	GetSettings();
}
