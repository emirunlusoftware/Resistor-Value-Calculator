#include "Resistor Value Calculator.h"



// TextOut functions wants integer data type, not size_t data type.
#define WCSLEN_INT(x) static_cast<int>(wcslen(x))

#define TEXT_OFFSET 1





void SMDCalculatorTexts(HDC hdc)
{
	SelectObject(hdc, mainTitleFont);
	TextOut(hdc,
		DPIScale(49), DPIScale(15),
		L"Enter Resistor Code", WCSLEN_INT(L"Enter Resistor Code"));
	SelectObject(hdc, globalFont);
}

void THTCalculatorBandTags(HDC hdc, int prevRadioState)
{
	SelectObject(hdc, thtComboboxFont);
	switch (prevRadioState)
	{
		case _4BANDSRADIOBUTTON:
		{
			TextOut(hdc,
				DPIScale(108) + TEXT_OFFSET, DPIScale(195),
				L"Band 1", WCSLEN_INT(L"Band 1"));
			TextOut(hdc,
				DPIScale(307) + TEXT_OFFSET, DPIScale(195),
				L"Band 2", WCSLEN_INT(L"Band 2"));
			TextOut(hdc,
				DPIScale(108) + TEXT_OFFSET, DPIScale(245),
				L"Multiplier", WCSLEN_INT(L"Multiplier"));
			TextOut(hdc,
				DPIScale(307) + TEXT_OFFSET, DPIScale(245),
				L"Tolerance", WCSLEN_INT(L"Tolerance"));

			break;
		}

		case _5BANDSRADIOBUTTON:
		case _6BANDSRADIOBUTTON:
		{
			TextOut(hdc,
				DPIScale(82) + TEXT_OFFSET, DPIScale(195),
				L"Band 1", WCSLEN_INT(L"Band 1"));
			TextOut(hdc,
				DPIScale(207) + TEXT_OFFSET, DPIScale(195),
				L"Band 2", WCSLEN_INT(L"Band 2"));
			TextOut(hdc,
				DPIScale(332) + TEXT_OFFSET, DPIScale(195),
				L"Band 3", WCSLEN_INT(L"Band 3"));
			
			if (prevRadioState == _5BANDSRADIOBUTTON)
			{
				TextOut(hdc,
					DPIScale(108) + TEXT_OFFSET, DPIScale(245),
					L"Multiplier", WCSLEN_INT(L"Multiplier"));
				TextOut(hdc,
					DPIScale(307) + TEXT_OFFSET, DPIScale(245),
					L"Tolerance", WCSLEN_INT(L"Tolerance"));
			}
			else
			{
				TextOut(hdc,
					DPIScale(82) + TEXT_OFFSET, DPIScale(245),
					L"Multiplier", WCSLEN_INT(L"Multiplier"));
				TextOut(hdc,
					DPIScale(207) + TEXT_OFFSET, DPIScale(245),
					L"Tolerance", WCSLEN_INT(L"Tolerance"));
				TextOut(hdc,
					DPIScale(332) + TEXT_OFFSET, DPIScale(245),
					L"Temp. Coefficient", WCSLEN_INT(L"Temp. Coefficient"));
			}

			break;
		}
	}
	SelectObject(hdc, globalFont);
}



void DrawTexts(HDC hdc, int page, int prevRadioState)
{
	switch (page)
	{
		case SMDCALCULATORPAGE:
			SMDCalculatorTexts(hdc);
			break;

		case THTCALCULATORPAGE:
			THTCalculatorBandTags(hdc, prevRadioState);
			break;

		default:
			break;
	}
}



const int mainWidth = 500;
void CalculationResultTexts(HDC hdc, LPCWSTR resultText, int resistorType)
{
	SelectObject(hdc, mainTitleFont);

	SIZE textSize = {0};
	GetTextExtentPoint32(hdc, resultText, WCSLEN_INT(resultText), &textSize);

	if (textSize.cx > DPIScale(mainWidth - 50))
	{
		SelectObject(hdc, thtLongResultFont);
		GetTextExtentPoint32(hdc, resultText, WCSLEN_INT(resultText), &textSize);
		TextOut(hdc,
			(DPIScale(mainWidth) - textSize.cx) / 2, DPIScale(300 + (textSize.cy)),
			resultText, WCSLEN_INT(resultText));
	}
	else
		TextOut(hdc,
			(DPIScale(mainWidth) - textSize.cx)/2, (resistorType == SMD) ? DPIScale(300) : DPIScale(320),
			resultText, WCSLEN_INT(resultText));

	SelectObject(hdc, globalFont);
}



WCHAR tooltipTexts[256] = {0};
void AddToolTip(HWND hWnd, HWND controlWindow)
{
	HWND tooltipWindow = CreateWindowEx(
		WS_EX_TOPMOST, TOOLTIPS_CLASS,
		NULL, TTS_NOPREFIX,
		0, 0, 0, 0,
		hWnd, NULL, NULL, NULL);

	TOOLINFO ti = {0};
	ti.cbSize = sizeof(TOOLINFO);
	ti.hinst = GetModuleHandle(NULL);
	ti.hwnd = controlWindow;
	ti.uFlags = TTF_SUBCLASS;
	ti.uId = (UINT_PTR)controlWindow;

	if (controlWindow == smdCodeEntry)
		wcscpy_s(tooltipTexts, 256, L"Enter the code written on your SMD resistance and press Calculate!");
	else if (controlWindow == thtResistorColor_1)
		wcscpy_s(tooltipTexts, 256, L"First color band. It can be between 0-9");
	else if (controlWindow == thtResistorColor_2)
		wcscpy_s(tooltipTexts, 256, L"Second color band. It can be between 0-9");
	else if (controlWindow == thtResistorColor_3)
		wcscpy_s(tooltipTexts, 256, L"Third color band. It can be between 0-9");
	else if (controlWindow == thtResistorMultiplier)
		wcscpy_s(tooltipTexts, 256, L"Multiplier of the resistance value, or demultiplier (e.g. Silver: x0.01)");
	else if (controlWindow == thtResistorTolerance)
		wcscpy_s(tooltipTexts, 256, L"It's the percentage shows how much the actual resistance value can vary from its labeled value.");
	else if (controlWindow == thtResistorTempCoef)
		wcscpy_s(tooltipTexts, 256, L"The temperature coefficient of a resistor indicates how much its resistance changes with temperature. It’s usually expressed in Parts Per Million per degree Celsius (ppm/°C).");
	SendMessage(tooltipWindow, TTM_SETMAXTIPWIDTH, 0, 275);
	ti.lpszText = tooltipTexts;

	GetClientRect(controlWindow, &ti.rect);
	SendMessage(tooltipWindow, TTM_ADDTOOL, 0, (LPARAM)&ti);
}