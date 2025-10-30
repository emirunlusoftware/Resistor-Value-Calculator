#include "Resistor Value Calculator.h"



const wchar_t szTitle[] = L"Resistor Value Calculator";
const wchar_t szWindowClass[] = L"RVCWindowClass";

PAINTSTRUCT ps;
HDC hdc;
HINSTANCE hInst;
bool calculatingSmd = false, calculatingTht = false, pcbTheme = false;
static LPCWSTR calcuationResult = L"";

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HWND*, HINSTANCE, int);
LRESULT CALLBACK    EditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);





int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	HWND hWnd;
	MSG msg;

	MyRegisterClass(hInstance);

	if (!InitInstance(&hWnd, hInstance, nShowCmd))
	{
		MessageBox(NULL, L"The program was terminated:\nInitialization process failed to create the main window.", L"Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!IsDialogMessage(hWnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex = {0};

	wcex.cbSize        = sizeof(WNDCLASSEX);
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WndProc;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = hInstance;
	wcex.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
	wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH) (COLOR_BTNSHADOW);
	wcex.lpszMenuName  = NULL;
	wcex.lpszClassName = szWindowClass;

	return RegisterClassEx(&wcex);
}



BOOL InitInstance(HWND* hWnd, HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX), ICC_WIN95_CLASSES };
	InitCommonControlsEx(&icc);


	// Coord. Point 1 (X1, Y1)
	// Coord. Point 2 (X2, Y2)
	RECT WindowDimensions =
	{
		0, 0, // (X1, Y1)
		DPIScale(500), DPIScale(450) // (X2, Y2)
	};
	AdjustWindowRect(&WindowDimensions, WS_OVERLAPPEDWINDOW &~ (WS_MAXIMIZEBOX | WS_THICKFRAME), FALSE);


	// Center the application window
	int screenWidth = GetSystemMetrics(SM_CXSCREEN),
		screenHeight = GetSystemMetrics(SM_CYSCREEN),
		posX = (screenWidth - (WindowDimensions.right - WindowDimensions.left)) / 2,
		posY = (screenHeight - (WindowDimensions.bottom - WindowDimensions.top)) / 2;


	*hWnd = CreateWindow(
		szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW &~ (WS_MAXIMIZEBOX | WS_THICKFRAME),
		posX, posY,
		WindowDimensions.right - WindowDimensions.left,
		WindowDimensions.bottom - WindowDimensions.top,
		NULL, NULL, hInstance, NULL);

	if (*hWnd == NULL)
		return FALSE;


	ShowWindow(*hWnd, nCmdShow);
	UpdateWindow(*hWnd);

	return TRUE;
}



// Specific processing for smdCodeEntry (only allows to type alphanumeric chars)
LRESULT CALLBACK EditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_CHAR)
	{
		// Capitalize lowercase letters you typed
		if (wParam >= 'a' && wParam <= 'z')
			wParam -= 0x20;

		// Allows alphanumeric chars only
		if ((wParam >= '0' && wParam <= '9') ||
			(wParam >= 'A' && wParam <= 'Z') ||
			wParam == VK_BACK)
		{
			return CallWindowProc((WNDPROC)GetWindowLongPtr(hWnd, GWLP_USERDATA), hWnd, msg, wParam, lParam);
		}
		else return 0;
	}
	else if (msg == WM_KEYDOWN)
	{
		// Catch Ctrl + A combination
		if ((GetKeyState(VK_CONTROL) & 0x8000) && (wParam == 'A'))
		{
			// Then, select all texts
			SendMessage(hWnd, EM_SETSEL, 0, -1);
			return 0;
		}
	}
	return CallWindowProc((WNDPROC)GetWindowLongPtr(hWnd, GWLP_USERDATA), hWnd, msg, wParam, lParam);
}



HBRUSH editBrush = CreateSolidBrush(RGB(0, 0, 0)), pcbBrush = CreateSolidBrush(RGB(16, 146, 64));
HFONT hSafeFont = NULL;
static UINT previousRadioState = _4BANDSRADIOBUTTON;
static UINT currentPage = MAINPAGE;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
		{
			LoadEntries(hWnd, hInst);
			LoadButtons(hWnd, hInst);
			LoadFonts(hWnd);
			hSafeFont = (HFONT)SelectObject(hdc, globalFont);
			LoadImages();
			break;
		}



		case WM_CTLCOLORSTATIC:
		{
			if (pcbTheme)
			{
				HDC wcexStatic = (HDC)wParam;
				SetBkMode(wcexStatic, TRANSPARENT);
				return (LRESULT)pcbBrush;
			}
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		case WM_CTLCOLOREDIT:
		{
			if ((HWND)lParam == smdCodeEntry)
			{
				SetTextColor((HDC)wParam, RGB(240, 240, 240));
				SetBkMode((HDC)wParam, OPAQUE);
				SetBkColor((HDC)wParam, RGB(0, 0, 0));
				return (LRESULT)editBrush;
			}
			return DefWindowProc(hWnd, message, wParam, lParam);
		}


		
		case WM_MEASUREITEM:
		{
			LPMEASUREITEMSTRUCT mis = (LPMEASUREITEMSTRUCT)lParam;
			if (mis->CtlType == ODT_COMBOBOX)
			{
				// Set comboboxes' height.
				// If the value is not high enough, the comboboxes look slightly clipped.
				mis->itemHeight = DPIScale(20);
				return TRUE;
			}
			break;
		}

		case WM_DRAWITEM:
		{
			#define COLOR_SQUARE_SIZE DPIScale(14)
			#define MARGIN_LEFT       DPIScale(4)

			LPDRAWITEMSTRUCT dis = (LPDRAWITEMSTRUCT)lParam;
			if (dis->CtlType == ODT_COMBOBOX)
			{
				HDC hdcDrawItem = dis->hDC;
				RECT rc = dis->rcItem;


				// 1. Paint combobox selection background
				HBRUSH hbrBack = GetSysColorBrush((dis->itemState & ODS_SELECTED) ? COLOR_HIGHLIGHT : COLOR_WINDOW);
				FillRect(hdcDrawItem, &rc, hbrBack);



				// 2a. Get color data from comboboxes
				COLORREF clr = (COLORREF)SendMessage(dis->hwndItem, CB_GETITEMDATA, dis->itemID, 0);

				// 2b. Measure the colored squares' dimensions
				RECT rcColor = {0};
				rcColor.left = rc.left + MARGIN_LEFT;
				rcColor.top = rc.top + ((rc.bottom - rc.top - COLOR_SQUARE_SIZE) / 2);
				rcColor.right = rcColor.left + COLOR_SQUARE_SIZE;
				rcColor.bottom = rcColor.top + COLOR_SQUARE_SIZE;

				// 2c. Draw & paint the squares
				HBRUSH hbrClr = CreateSolidBrush(clr);
				FillRect(hdcDrawItem, &rcColor, hbrClr);
				FrameRect(hdcDrawItem, &rcColor, GetSysColorBrush(COLOR_WINDOWTEXT));
				DeleteObject(hbrClr);




				// 3a. Get string data from comboboxes 
				WCHAR text[24] = {NULL};
				SendMessage(dis->hwndItem, CB_GETLBTEXT, dis->itemID, (LPARAM)text);

				// 3b. Set the text's background transparent and its color which is visible
				// (the effects become noticeable when selecting a color in a combobox)
				SetBkMode(hdcDrawItem, TRANSPARENT);
				SetTextColor(hdcDrawItem,
					(dis->itemState & ODS_SELECTED) ? GetSysColor(COLOR_HIGHLIGHTTEXT)
					: GetSysColor(COLOR_WINDOWTEXT));

				// 3c. Measure the texts' dimensions and draw
				RECT rcText = rc;
				rcText.left = rcColor.right + MARGIN_LEFT;
				DrawText(hdcDrawItem, text, -1, &rcText, DT_SINGLELINE | DT_VCENTER | DT_LEFT);


				return TRUE;
			}

			break;
		}



		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			if (pcbTheme)
				ApplyPCBTheme(hWnd, hdc, pcbBrush);

			SelectObject(hdc, globalFont);
			SetBkMode(hdc, TRANSPARENT);


			switch (currentPage)
			{
				case MAINPAGE:
				{
					SendMessage(selectResistorFrame, WM_SETFONT, (WPARAM)mainTitleFont, TRUE);
					break;
				}

				case SMDCALCULATORPAGE:
				{
					SendMessage(smdCodeEntry, WM_SETFONT, (WPARAM)smdCodeFont, TRUE);
					if (calculatingSmd)
						CalculationResultTexts(hdc, CalculateSMDResistance(smdCodeEntry), SMD);

					break;
				}

				case THTCALCULATORPAGE:
				{
					for (int comboboxId = THT_COLOR1; comboboxId <= THT_TCR; comboboxId++)
					{
						HWND thtComboboxes = GetDlgItem(hWnd, comboboxId);
						if (thtComboboxes != NULL)
							SendMessage(thtComboboxes, WM_SETFONT, (WPARAM)thtComboboxFont, TRUE);
					}

					if (calculatingTht)
						CalculationResultTexts(hdc, CalculateTHTResistance(previousRadioState), THT);

					break;
				}

				default:
					return 0;
			}
			DrawTexts(hdc, currentPage, previousRadioState);
			DrawImages(hdc, currentPage);

			if (currentPage == THTCALCULATORPAGE)
				DrawColorBands(hdc, previousRadioState);

			// Restore previous font
			SelectObject(hdc, hSafeFont);
			EndPaint(hWnd, &ps);
			break;
		}

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case SMDENTERBUTTON:
					currentPage = SMDCALCULATORPAGE;
					ShowPage(currentPage, previousRadioState);
					InvalidateRect(hWnd, NULL, TRUE);
					SetFocus(smdCodeEntry);
					break;

				case THTENTERBUTTON:
					currentPage = THTCALCULATORPAGE;
					ShowPage(currentPage, previousRadioState);
					InvalidateRect(hWnd, NULL, TRUE);
					break;

				case PCBTHEMEBUTTON:
					pcbTheme = !pcbTheme;
					InvalidateRect(hWnd, NULL, TRUE);
					break;



				case SMDCALCULATEBUTTON:
					calculatingSmd = true;
					InvalidateRect(hWnd, NULL, TRUE);
					break;



				case _4BANDSRADIOBUTTON:
				case _5BANDSRADIOBUTTON:
				case _6BANDSRADIOBUTTON:
				{
					if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) != previousRadioState)
					{
						SetTHTComboboxes(LOWORD(wParam));
						calculatingTht = true;
						previousRadioState = LOWORD(wParam);
						InvalidateRect(hWnd, NULL, TRUE);
					}
					break;
				}

				case THT_COLOR1:
				case THT_COLOR2:
				case THT_COLOR3:
				case THT_MULTIPLIER:
				case THT_TOLERANCE:
				case THT_TCR:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE && SendMessage(GetDlgItem(hWnd, LOWORD(wParam)), CB_GETCURSEL, 0, 0) != CB_ERR)
					{
						calculatingTht = true;
						InvalidateRect(hWnd, NULL, TRUE);
					}
					break;
				}

				case BACKTOMAINBUTTON:
					currentPage = MAINPAGE;
					ShowPage(currentPage, previousRadioState);
					InvalidateRect(hWnd, NULL, TRUE);
					break;
			}
			break;
		}



		case WM_CLOSE:
			DestroyWindow(hWnd);

		case WM_DESTROY:
		{
			if (editBrush)
				DeleteObject(editBrush);
			if (pcbBrush)
				DeleteObject(pcbBrush);

			HFONT* nonsystemFontsToDelete[] = {
				&globalFont, &mainTitleFont, &smdCodeFont, &thtComboboxFont, &thtLongResultFont
			};
			for (int index = 0; index < sizeof(nonsystemFontsToDelete) / sizeof(nonsystemFontsToDelete[0]); index++)
				DeleteObject(nonsystemFontsToDelete[index]);

			PostQuitMessage(0);
			break;
		}

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}