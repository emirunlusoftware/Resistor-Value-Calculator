#pragma once
#ifndef RESISTOR_VALUE_CALCULATOR_H
#define RESISTOR_VALUE_CALCULATOR_H

#include "stdafx.h"
#include "resource.h"





/*___bandcolors.h___*/
extern LPCWSTR
thtNumberColors[10],
thtMultiplierColors[12],
thtToleranceColors[10];

extern COLORREF
thtNumberColorPalettes[10],
thtMultiplierColorPalettes[12],
thtToleranceColorPalettes[10],
thtTempCoefColorPalettes[9];

void DrawColorBands(HDC hdc, int prevRadioState);
/*--------------------------*/



/*___buttons.h___*/
#define SMDENTERBUTTON     900
#define THTENTERBUTTON     901
#define PCBTHEMEBUTTON     902
#define SMDCALCULATEBUTTON 910
#define _4BANDSRADIOBUTTON 920
#define _5BANDSRADIOBUTTON 921
#define _6BANDSRADIOBUTTON 922
#define BACKTOMAINBUTTON   950
#define FRAMES             990

extern HWND
smdEnterButton,
thtEnterButton,
activatePCBTheme,
selectResistorFrame,
smdFrame,
thtFrame,
calculateButton,
_4BandsRadioButton,
_5BandsRadioButton,
_6BandsRadioButton,
backToMainButton;

void LoadButtons(HWND hWnd, HINSTANCE hInstance);
/*---------------------------------------------*/



/*___calculator.h___*/
#define WRONGTYPE  -1
#define ZERO        0
#define _3DIGITS    1
#define _4DIGITS    2
#define EIA96       3
#define RDIGITS     4
#define DIGITRDIGIT 5

#define ATFIRSTDIGIT  0
#define ATSECONDDIGIT 1
#define ATTHIRDDIGIT  2
#define ATFOURTHDIGIT 3

LPCWSTR CalculateSMDResistance(HWND editWindow);
LPCWSTR CalculateTHTResistance(int prevRadioState);
/*----------------------------------------------------------*/



/*___entries.h___*/
#define SMDCODEENTRY   903
#define THT_COLOR1     923
#define THT_COLOR2     924
#define THT_COLOR3     925
#define THT_MULTIPLIER 926
#define THT_TOLERANCE  927
#define THT_TCR        928

extern HWND
smdCodeEntry,
thtResistorColor_1,
thtResistorColor_2,
thtResistorColor_3,
thtResistorMultiplier,
thtResistorTolerance,
thtResistorTempCoef;

void SetTHTComboboxes(int numberOfBands);
void LoadEntries(HWND hWnd, HINSTANCE hInstance);
/*---------------------------------------------*/



/*___fonts.h___*/
extern HFONT
globalFont,
mainTitleFont,
smdCodeFont,
thtComboboxFont,
thtLongResultFont;

void LoadFonts(HWND hWnd);
/*-----------------------*/



/*___images.h___*/
void LoadImages();
void DrawImages(HDC hdc, int page);
/*-------------------------------*/



/*___main.h___*/
LRESULT CALLBACK EditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
/*-------------------------------------------------------------------------*/



/*___misc.h___*/

// This function allows the program
// to scale window dimemsions (width and height) automatically
// according to the current DPI factor.
inline int DPIScale(int value)
{
	static int dpi = 0;
	if (dpi == 0)
	{
		HDC hdc = GetDC(NULL);
		//	If hdc exists:
		//		Get DPI value.
		//		If DPI value is zero or negative, make DPI value 96 (standard value).
		//	Else hdc not exists:
		//		Make DPI value 96 (standard value).
		if (hdc)
		{
			dpi = GetDeviceCaps(hdc, LOGPIXELSX);
			ReleaseDC(NULL, hdc);
			if (dpi <= 0)
				dpi = 96;
		}
		else
			dpi = 96;
	}

	return (int)(value * (dpi / 96.0f));
}

inline void ApplyPCBTheme(HWND hWnd, HDC hdc, HBRUSH pcbBrush)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	FillRect(hdc, &rect, pcbBrush);
}
/*----------------------------------------------------------*/



/*___pages.h___*/
#define HIDE 0
#define SHOW 1

#define MAINPAGE          0
#define SMDCALCULATORPAGE 1
#define THTCALCULATORPAGE 2

void ShowPage(int page, int prevRadioState);
/*--------------------------------------------*/



/*___texts.h___*/
#define SMD 0
#define THT 1

void CalculationResultTexts(HDC hdc, LPCWSTR resultText, int resistorType);
void DrawTexts(HDC hdc, int page, int prevRadioState);
void AddToolTip(HWND hWnd, HWND controlWindow);
/*-----------------------------------------------------------------------*/



#endif