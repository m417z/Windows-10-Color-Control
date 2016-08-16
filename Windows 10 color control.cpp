// Windows 10 color control.cpp : main source file for Windows 10 color control.exe
//

#include "stdafx.h"
#include "resource.h"
#include "WindowsThemeColorApi.h"
#include "MainDlg.h"

CAppModule _Module;

namespace
{
	bool GetColorParam(const WCHAR *pParam, COLORREF *pColor);
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(0);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	InitWindowsThemeColorApi();

	int nRet = 0;

	COLORREF dwmColor;
	bool dwmColorValid = GetColorParam(L"-dwm_color", &dwmColor);
	COLORREF accentColor;
	bool accentColorValid = GetColorParam(L"-accent_color", &accentColor);

	if(dwmColorValid || accentColorValid)
	{
		if(accentColorValid)
		{
			SetAccentColor(accentColor);
		}

		if(dwmColorValid)
		{
			SetDwmColorizationColor(dwmColor);
		}
	}
	else // BLOCK: Run application
	{
		CMainDlg dlgMain;
		nRet = dlgMain.DoModal();
	}

	_Module.Term();
	::CoUninitialize();

	return nRet;
}

namespace
{
	bool GetColorParam(const WCHAR *pParam, COLORREF *pColor)
	{
		for(int i = 1; i < __argc - 1; i++)
		{
			if(_wcsicmp(__wargv[i], pParam) == 0)
			{
				DWORD dwParamValue = wcstoul(__wargv[i + 1], NULL, 16);
				COLORREF retReversed = dwParamValue & 0x00FFFFFF;
				*pColor = RGB(GetBValue(retReversed), GetGValue(retReversed), GetRValue(retReversed));
				return true;
			}
		}

		return false;
	}
}
