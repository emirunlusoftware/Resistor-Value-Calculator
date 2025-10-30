#include "Resistor Value Calculator.h"





HWND* mainPageControls[] =
{ &smdEnterButton, &thtEnterButton, &activatePCBTheme, &selectResistorFrame, &smdFrame, &thtFrame };

HWND* smdCalculatorPageControls[] =
{ &smdCodeEntry, &calculateButton, &backToMainButton };

HWND* thtCalculatorPageControls[] =
{ &_4BandsRadioButton, &_5BandsRadioButton, &_6BandsRadioButton, &thtResistorColor_1, &thtResistorColor_2, &thtResistorMultiplier,
&thtResistorTolerance, &backToMainButton, &thtResistorColor_3, &thtResistorTempCoef };

HWND** allControls[] =
{ mainPageControls, smdCalculatorPageControls, thtCalculatorPageControls };


size_t arrayLengths[] =
{
	sizeof(mainPageControls) / sizeof(mainPageControls[0]),
	sizeof(smdCalculatorPageControls) / sizeof(smdCalculatorPageControls[0]),
	sizeof(thtCalculatorPageControls) / sizeof(thtCalculatorPageControls[0]),
};



UINT prevPageHandler = MAINPAGE;
void ShowPage(int page, int prevRadioState)
{
	// Hide
	for (size_t controlIter = 0; controlIter < arrayLengths[prevPageHandler]; controlIter++)
		ShowWindow(*allControls[prevPageHandler][controlIter], HIDE);

	// Show
	if (page == THTCALCULATORPAGE)
	{
		for (size_t controlIter = 0; controlIter < arrayLengths[page] - (_6BANDSRADIOBUTTON - prevRadioState); controlIter++)
			ShowWindow(*allControls[page][controlIter], SHOW);
	}
	else
		for (size_t controlIter = 0; controlIter < arrayLengths[page]; controlIter++)
			ShowWindow(*allControls[page][controlIter], SHOW);

	prevPageHandler = page;
}