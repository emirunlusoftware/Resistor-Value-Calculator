#include "Resistor Value Calculator.h"





#define BLACK   RGB(10,11,13)
#define BROWN   RGB(129,44,19)
#define RED     RGB(205,3,25)
#define ORANGE  RGB(252,102,15)
#define YELLOW  RGB(237,193,23)
#define GREEN   RGB(31,124,42)
#define BLUE    RGB(5,106,167)
#define VIOLET  RGB(183,103,164)
#define GREY    RGB(114,120,119)
#define WHITE   RGB(240,240,240)
#define GOLD    RGB(173,139,24)
#define SILVER  RGB(196,196,196)


LPCWSTR
thtNumberColors[10] = { L"Black", L"Brown", L"Red", L"Orange", L"Yellow", L"Green", L"Blue", L"Violet", L"Gray", L"White" },
thtMultiplierColors[12] = { L"Black", L"Brown", L"Red", L"Orange", L"Yellow", L"Green", L"Blue", L"Violet", L"Gray", L"White", L"Gold", L"Silver" },
thtToleranceColors[10] = { L"Brown", L"Red", L"Orange", L"Yellow", L"Green", L"Blue", L"Violet", L"Gray", L"Gold", L"Silver" };

COLORREF
thtNumberColorPalettes[10] = { BLACK, BROWN, RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, GREY, WHITE },
thtMultiplierColorPalettes[12] = { BLACK, BROWN, RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, GREY, WHITE, GOLD, SILVER },
thtToleranceColorPalettes[10] = { BROWN, RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, GREY, GOLD, SILVER },
thtTempCoefColorPalettes[9] = { BLACK, BROWN, RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, GREY };



HPEN hPen, hSafePen;
void DrawColorBands(HDC hdc, int prevRadioState)
{
	hPen = CreatePen(PS_SOLID, DPIScale(15), thtNumberColorPalettes[SendMessage(thtResistorColor_1, CB_GETCURSEL, 0, 0)]);
	hSafePen = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, DPIScale(125), DPIScale(58), DPIScale(140), DPIScale(151));

	hPen = CreatePen(PS_SOLID, DPIScale(10), thtNumberColorPalettes[SendMessage(thtResistorColor_2, CB_GETCURSEL, 0, 0)]);
	SelectObject(hdc, hPen);
	Rectangle(hdc, DPIScale(195), DPIScale(63), DPIScale(205), DPIScale(147));

	switch (prevRadioState)
	{
		case _4BANDSRADIOBUTTON:
		{
			hPen = CreatePen(PS_SOLID, DPIScale(10), thtMultiplierColorPalettes[SendMessage(thtResistorMultiplier, CB_GETCURSEL, 0, 0)]);
			SelectObject(hdc, hPen);
			Rectangle(hdc, DPIScale(230), DPIScale(63), DPIScale(240), DPIScale(147));

			hPen = CreatePen(PS_SOLID, DPIScale(15), thtToleranceColorPalettes[SendMessage(thtResistorTolerance, CB_GETCURSEL, 0, 0)]);
			SelectObject(hdc, hPen);
			Rectangle(hdc, DPIScale(360), DPIScale(58), DPIScale(370), DPIScale(151));

			break;
		}

		case _5BANDSRADIOBUTTON:
		case _6BANDSRADIOBUTTON:
		{
			hPen = CreatePen(PS_SOLID, DPIScale(10), thtNumberColorPalettes[SendMessage(thtResistorColor_3, CB_GETCURSEL, 0, 0)]);
			SelectObject(hdc, hPen);
			Rectangle(hdc, DPIScale(230), DPIScale(63), DPIScale(240), DPIScale(147));

			hPen = CreatePen(PS_SOLID, DPIScale(10), thtMultiplierColorPalettes[SendMessage(thtResistorMultiplier, CB_GETCURSEL, 0, 0)]);
			SelectObject(hdc, hPen);
			Rectangle(hdc, DPIScale(265), DPIScale(63), DPIScale(275), DPIScale(147));

			if (prevRadioState == _5BANDSRADIOBUTTON)
			{
				hPen = CreatePen(PS_SOLID, DPIScale(15), thtToleranceColorPalettes[SendMessage(thtResistorTolerance, CB_GETCURSEL, 0, 0)]);
				SelectObject(hdc, hPen);
				Rectangle(hdc, DPIScale(360), DPIScale(58), DPIScale(370), DPIScale(151));
			}
			else
			{
				hPen = CreatePen(PS_SOLID, DPIScale(10), thtToleranceColorPalettes[SendMessage(thtResistorTolerance, CB_GETCURSEL, 0, 0)]);
				SelectObject(hdc, hPen);
				Rectangle(hdc, DPIScale(300), DPIScale(63), DPIScale(310), DPIScale(147));

				hPen = CreatePen(PS_SOLID, DPIScale(15), thtTempCoefColorPalettes[SendMessage(thtResistorTempCoef, CB_GETCURSEL, 0, 0)]);
				SelectObject(hdc, hPen);
				Rectangle(hdc, DPIScale(360), DPIScale(58), DPIScale(370), DPIScale(151));
			}
			break;
		}

	}

	/*
		1- SelectObject(hSafePen) to disable hPen
		2- DeleteObject(hPen) to delete hPen safely
	*/

	SelectObject(hdc, hSafePen);
	DeleteObject(hPen);
}