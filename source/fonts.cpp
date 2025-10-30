#include "Resistor Value Calculator.h"





HFONT globalFont, mainTitleFont, smdCodeFont, thtComboboxFont, thtLongResultFont;
void LoadFonts(HWND hWnd)
{
	// My custom font specifications are initialized here
	LOGFONTW lf =
	{
		0,                   // cHeight
		0,                   // cWidth
		0,                   // cEscapement
		0,                   // cOrientation
		FW_MEDIUM,           // cWeight
		0,                   // bItalic
		0,                   // bUnderline
		0,                   // bStrikeOut
		DEFAULT_CHARSET,     // iCharSet
		OUT_DEFAULT_PRECIS,  // iOutputPrecision
		CLIP_DEFAULT_PRECIS, // iClipPrecision
		DEFAULT_QUALITY,     // iQuality
		DEFAULT_PITCH,       // iPitchAndFamily
		L"Tahoma"            // lpszFaceName
	};


	// Create globalFont
	lf.lfHeight = DPIScale(-20);
	lf.lfWidth = DPIScale(-9);
	lf.lfWeight = FW_SEMIBOLD;
	wcscpy_s(lf.lfFaceName, L"Tahoma");
	globalFont = CreateFontIndirectW(&lf);


	// Create mainTitleFont with some changed values
	lf.lfHeight = DPIScale(-44);
	lf.lfWidth = DPIScale(-20);
	mainTitleFont = CreateFontIndirectW(&lf);


	// Create smdEntryFont with some changed values
	lf.lfHeight = DPIScale(-88);
	lf.lfWidth = DPIScale(-44);
	lf.lfWeight = FW_NORMAL;
	lf.lfCharSet = ANSI_CHARSET;
	wcscpy_s(lf.lfFaceName, L"Courier");
	smdCodeFont = CreateFontIndirectW(&lf);


	// Create thtComboboxFont with different values
	lf.lfHeight = DPIScale(-11);
	lf.lfWidth = DPIScale(-5);
	lf.lfCharSet = DEFAULT_CHARSET;
	wcscpy_s(lf.lfFaceName, L"Tahoma");
	thtComboboxFont = CreateFontIndirectW(&lf);


	// Create thtLongResultFont 
	lf.lfHeight = DPIScale(-26);
	lf.lfWidth = DPIScale(-12);
	lf.lfWeight = FW_SEMIBOLD;
	thtLongResultFont = CreateFontIndirectW(&lf);



	// Apply globalFont to all child controls (buttons, combo boxes, etc.)
	HWND hWndChild = GetWindow(hWnd, GW_CHILD);
	while (hWndChild)
	{
		SendMessage(hWndChild, WM_SETFONT, (WPARAM)globalFont, TRUE);
		hWndChild = GetWindow(hWndChild, GW_HWNDNEXT);
	}
}