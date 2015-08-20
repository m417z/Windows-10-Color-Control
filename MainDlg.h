// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CMainDlg : public CDialogImpl<CMainDlg>
{
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CTLCOLORSTATIC(OnCtlColorStatic)
		COMMAND_ID_HANDLER_EX(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER_EX(IDOK, OnOK)
		COMMAND_ID_HANDLER_EX(IDCANCEL, OnCancel)
		COMMAND_ID_HANDLER_EX(IDC_DWM_BTN, OnDwmBtnClick)
		COMMAND_ID_HANDLER_EX(IDC_ACCENT_BTN, OnAccentBtnClick)
		COMMAND_HANDLER_EX(IDC_ACCENT_NO_NEW_ALGO, BN_CLICKED, OnAccentNewAlgoClick)
	END_MSG_MAP()

	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
	HBRUSH OnCtlColorStatic(CDCHandle dc, CStatic wndStatic);
	LRESULT OnDwmColorizationColorChanged(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnAppAbout(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnOK(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnCancel(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnDwmBtnClick(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnAccentBtnClick(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnAccentNewAlgoClick(UINT uNotifyCode, int nID, CWindow wndCtl);

private:
	COLORREF m_dwmColor, m_accentColor;
	CBrush m_dwmBrush, m_accentBrush;
	bool m_lastNewAccentAlgo;
	bool m_newAccentAlgo;

	void GetSettings();
	void SetSettings();
};
