#include "Resistor Value Calculator.h"





// Window Handles
HWND
// Main Menu
smdEnterButton,
thtEnterButton,
activatePCBTheme,
selectResistorFrame,
smdFrame,
thtFrame,

// SMD Calculator Page
calculateButton,

// THT Calculator Page
_4BandsRadioButton,
_5BandsRadioButton,
_6BandsRadioButton,

// Miscellaneous
backToMainButton;



void MainMenuButtons(HWND hWnd, HINSTANCE hInstance)
{
	smdEnterButton = CreateWindow(
		L"BUTTON", L"Start",
		BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
		DPIScale(106), DPIScale(303),
		DPIScale(128), DPIScale(44),
		hWnd, (HMENU)SMDENTERBUTTON, hInstance, NULL
	);

	thtEnterButton = CreateWindow(
		L"BUTTON", L"Start",
		BS_PUSHBUTTON | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
		DPIScale(266), DPIScale(303),
		DPIScale(128), DPIScale(44),
		hWnd, (HMENU)THTENTERBUTTON, hInstance, NULL
	);

	activatePCBTheme = CreateWindow(
		L"BUTTON", L"PCB Theme",
		BS_AUTOCHECKBOX | WS_VISIBLE | WS_TABSTOP | WS_CHILD,
		DPIScale(183), DPIScale(410),
		DPIScale(15 * wcslen(L"PCB Theme")), DPIScale(22),
		hWnd,
		(HMENU)PCBTHEMEBUTTON, hInstance, NULL
	);
}



void MainMenuFrames(HWND hWnd, HINSTANCE hInstance)
{
	selectResistorFrame = CreateWindow(
		L"BUTTON", L"Select Resistor",
		WS_VISIBLE | WS_CHILD | BS_GROUPBOX | BS_CENTER,
		DPIScale(90), DPIScale(40),
		DPIScale(320), DPIScale(339),
		hWnd, (HMENU)FRAMES, hInstance, NULL
	);

	smdFrame = CreateWindow(
		L"BUTTON", L"SMD",
		WS_VISIBLE | WS_CHILD | BS_GROUPBOX | BS_CENTER,
		DPIScale(90), DPIScale(140),
		DPIScale(160), DPIScale(239),
		hWnd, (HMENU)FRAMES, hInstance, NULL
	);

	thtFrame = CreateWindow(
		L"BUTTON", L"THT",
		WS_VISIBLE | WS_CHILD | BS_GROUPBOX | BS_CENTER,
		DPIScale(250), DPIScale(140),
		DPIScale(160), DPIScale(239),
		hWnd, (HMENU)FRAMES, hInstance, NULL
	);
}



void CalculatorButtons(HWND hWnd, HINSTANCE hInstance)
{
	calculateButton = CreateWindow(
		L"BUTTON", L"Calculate",
		BS_PUSHBUTTON | WS_TABSTOP | WS_CHILD,
		DPIScale(186), DPIScale(400),
		DPIScale(128), DPIScale(44),
		hWnd, (HMENU)SMDCALCULATEBUTTON, hInstance, NULL
	);


	_4BandsRadioButton = CreateWindow(
		L"BUTTON", L"4 Bands",
		WS_GROUP | BS_AUTORADIOBUTTON | WS_TABSTOP | WS_CHILD,
		DPIScale(50), DPIScale(10),
		DPIScale(100), DPIScale(24),
		hWnd, (HMENU)_4BANDSRADIOBUTTON, hInstance, NULL);

	_5BandsRadioButton = CreateWindow(
		L"BUTTON", L"5 Bands",
		BS_AUTORADIOBUTTON | WS_TABSTOP | WS_CHILD,
		DPIScale(200), DPIScale(10),
		DPIScale(100), DPIScale(24),
		hWnd, (HMENU)_5BANDSRADIOBUTTON, hInstance, NULL);

	_6BandsRadioButton = CreateWindow(
		L"BUTTON", L"6 Bands",
		BS_AUTORADIOBUTTON | WS_TABSTOP | WS_CHILD,
		DPIScale(350), DPIScale(10),
		DPIScale(100), DPIScale(24),
		hWnd, (HMENU)_6BANDSRADIOBUTTON, hInstance, NULL);

	SendMessage(_4BandsRadioButton, BM_SETCHECK, BST_CHECKED, 0);
}

void MiscButtons(HWND hWnd, HINSTANCE hInstance)
{
	backToMainButton = CreateWindow(
		L"BUTTON", L"Back",
		BS_PUSHBUTTON | WS_TABSTOP | WS_CHILD,
		DPIScale(5), DPIScale(397),
		DPIScale(64), DPIScale(44),
		hWnd, (HMENU)BACKTOMAINBUTTON, hInstance, NULL
	);
}



void LoadButtons(HWND hWnd, HINSTANCE hInstance)
{
	MainMenuButtons(hWnd, hInstance);
	MainMenuFrames(hWnd, hInstance);
	CalculatorButtons(hWnd, hInstance);
	MiscButtons(hWnd, hInstance);
}