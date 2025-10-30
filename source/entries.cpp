#include "Resistor Value Calculator.h"





HWND
smdCodeEntry,
thtResistorColor_1,
thtResistorColor_2,
thtResistorColor_3,
thtResistorMultiplier,
thtResistorTolerance,
thtResistorTempCoef;



void SMDEntry(HWND hWnd, HINSTANCE hInstance)
{
	smdCodeEntry = CreateWindow(
		L"EDIT", L"",
		WS_TABSTOP | WS_CHILD | ES_CENTER | ES_AUTOHSCROLL,
		DPIScale(150), DPIScale(132),
		DPIScale(200), DPIScale(96),
		hWnd, (HMENU)SMDCODEENTRY, hInstance, NULL
	);
	SendMessage(smdCodeEntry, EM_SETLIMITTEXT, 4, 0);
	AddToolTip(hWnd, smdCodeEntry);

	SetWindowLongPtr(smdCodeEntry, GWLP_USERDATA, (LONG_PTR)GetWindowLongPtr(smdCodeEntry, GWLP_WNDPROC));
	SetWindowLongPtr(smdCodeEntry, GWLP_WNDPROC, (LONG_PTR)EditProc);
}



void THTComboboxes(HWND hWnd, HINSTANCE hInstance)
{
	HWND* thtComboboxes[] = {
		&thtResistorColor_1, &thtResistorColor_2, &thtResistorColor_3,
		&thtResistorMultiplier, &thtResistorTolerance, &thtResistorTempCoef
	};
	int coord[][4] = {
		{108, 210, 85, (10 * 30)}, {307, 210, 85, (10 * 30)},
		{332, 210, 85, (10 * 30)}, {108, 260, 85, (12 * 30)},
		{307, 260, 85, (10 * 30)}, {332, 260, 85, (9 * 30)}
	};

	for (int id = THT_COLOR1, index = 0; id <= THT_TCR; id++, index++)
	{
		*thtComboboxes[index] = CreateWindow(
			L"COMBOBOX", NULL,
			WS_TABSTOP | WS_CHILD | CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS | WS_VSCROLL,
			DPIScale(coord[index][0]), DPIScale(coord[index][1]),
			DPIScale(coord[index][2]), DPIScale(coord[index][3]),
			hWnd, (HMENU)id, hInstance, NULL
		);

		AddToolTip(hWnd, *thtComboboxes[index]);
	}



	// Digit 1-2-3 bands
	for (int index = 0; index < (sizeof(thtNumberColors) / sizeof(thtNumberColors[0])); index++)
	{
		SendMessage(thtResistorColor_1, CB_ADDSTRING, 0, (LPARAM)thtNumberColors[index]);
		SendMessage(thtResistorColor_2, CB_ADDSTRING, 0, (LPARAM)thtNumberColors[index]);
		SendMessage(thtResistorColor_3, CB_ADDSTRING, 0, (LPARAM)thtNumberColors[index]);

		SendMessage(thtResistorColor_1, CB_SETITEMDATA, index, (LPARAM)thtNumberColorPalettes[index]);
		SendMessage(thtResistorColor_2, CB_SETITEMDATA, index, (LPARAM)thtNumberColorPalettes[index]);
		SendMessage(thtResistorColor_3, CB_SETITEMDATA, index, (LPARAM)thtNumberColorPalettes[index]);
	}

	// Multiplier band
	for (int index = 0; index < (sizeof(thtMultiplierColors) / sizeof(thtMultiplierColors[0])); index++)
	{
		SendMessage(thtResistorMultiplier, CB_ADDSTRING, 0, (LPARAM)thtMultiplierColors[index]);
		SendMessage(thtResistorMultiplier, CB_SETITEMDATA, index, (LPARAM)thtMultiplierColorPalettes[index]);
	}

	// Tolerance band (± n%)
	for (int index = 0; index < (sizeof(thtToleranceColors) / sizeof(thtToleranceColors[0])); index++)
	{
		SendMessage(thtResistorTolerance, CB_ADDSTRING, 0, (LPARAM)thtToleranceColors[index]);
		SendMessage(thtResistorTolerance, CB_SETITEMDATA, index, (LPARAM)thtToleranceColorPalettes[index]);
	}

	// Temperature Coefficient (ppm/°C)
	for (int index = 0; index < sizeof(thtTempCoefColorPalettes)/sizeof(thtTempCoefColorPalettes[0]); index++)
	{
		SendMessage(thtResistorTempCoef, CB_ADDSTRING, 0, (LPARAM)thtNumberColors[index]);
		SendMessage(thtResistorTempCoef, CB_SETITEMDATA, index, (LPARAM)thtTempCoefColorPalettes[index]);
	}


	for (int index = 0; index < (sizeof(thtComboboxes)/sizeof(thtComboboxes[0])); index++)
		SendMessage(*thtComboboxes[index], CB_SETCURSEL, index, 0);
}



void LoadEntries(HWND hWnd, HINSTANCE hInstance)
{
	SMDEntry(hWnd, hInstance);
	THTComboboxes(hWnd, hInstance);
}



void SetTHTComboboxes(int numberOfBands)
{
	switch (numberOfBands)
	{
		case _4BANDSRADIOBUTTON:
			ShowWindow(thtResistorColor_3, SW_HIDE);
			ShowWindow(thtResistorTempCoef, SW_HIDE);
			SetWindowPos(thtResistorColor_1, NULL, DPIScale(108), DPIScale(210), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			SetWindowPos(thtResistorColor_2, NULL, DPIScale(307), DPIScale(210), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			SetWindowPos(thtResistorMultiplier, NULL, DPIScale(108), DPIScale(260), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			SetWindowPos(thtResistorTolerance, NULL, DPIScale(307), DPIScale(260), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			break;

		case _5BANDSRADIOBUTTON:
		case _6BANDSRADIOBUTTON:
		{
			SetWindowPos(thtResistorColor_1, NULL, DPIScale(82), DPIScale(210), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			SetWindowPos(thtResistorColor_2, NULL, DPIScale(207), DPIScale(210), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			if (numberOfBands == _5BANDSRADIOBUTTON)
			{
				ShowWindow(thtResistorTempCoef, SW_HIDE);
				SetWindowPos(thtResistorMultiplier, NULL, DPIScale(108), DPIScale(260), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
				SetWindowPos(thtResistorTolerance, NULL, DPIScale(307), DPIScale(260), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			}
			else
			{
				ShowWindow(thtResistorTempCoef, SW_SHOW);
				SetWindowPos(thtResistorMultiplier, NULL, DPIScale(82), DPIScale(260), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
				SetWindowPos(thtResistorTolerance, NULL, DPIScale(207), DPIScale(260), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			}
			ShowWindow(thtResistorColor_3, SW_SHOW);
			break;
		}
	}
}