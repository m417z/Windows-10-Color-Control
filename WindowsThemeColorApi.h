#pragma once

struct DWMCOLORIZATIONPARAMS {
	DWORD dwColor;
	DWORD dwAfterglow;
	DWORD dwColorBalance;
	DWORD dwAfterglowBalance;
	DWORD dwBlurBalance;
	DWORD dwGlassReflectionIntensity;
	DWORD dwOpaqueBlend;
};

struct IMMERSIVE_COLOR_PREFERENCE {
	COLORREF color1;
	COLORREF color2;
};

void InitWindowsThemeColorApi();
COLORREF GetDwmColorizationColor();
void SetDwmColorizationColor(COLORREF color);
COLORREF GetAccentColor();
void SetAccentColor(COLORREF color, bool newAccentAlgorithmWorkaround = false);
bool IsNewAutoColorAccentAlgorithm();
void SetAutoColorAccentAlgorithm(bool bNewAlgorithm);
