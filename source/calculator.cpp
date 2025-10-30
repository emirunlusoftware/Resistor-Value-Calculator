#include "Resistor Value Calculator.h"





typedef struct {
	const WCHAR letter;
	double multiplier;
} Letter;

Letter eia96Letters[12] = {
	{L'Z', 0.001}, {L'Y', 0.01}, {L'R', 0.01}, {L'X', 0.1}, {L'S', 0.1}, {L'A', 1.0},
	{L'B', 10.0}, {L'H', 10.0}, {L'C', 100.0}, {L'D', 1000.0}, {L'E', 10000.0}, {L'F', 100000.0}
};


typedef struct {
	LPCWSTR code;
	int value;
} Code;

Code eia96Codes[96] = {
	{L"01", 100}, {L"02", 102}, {L"03", 105}, {L"04", 107}, {L"05", 110}, {L"06", 113}, {L"07", 115}, {L"08", 118},
	{L"09", 121}, {L"10", 124}, {L"11", 127}, {L"12", 130}, {L"13", 133}, {L"14", 137}, {L"15", 140}, {L"16", 143},
	{L"17", 147}, {L"18", 150}, {L"19", 154}, {L"20", 158}, {L"21", 162}, {L"22", 165}, {L"23", 169}, {L"24", 174},
	{L"25", 178}, {L"26", 182}, {L"27", 187}, {L"28", 191}, {L"29", 196}, {L"30", 200}, {L"31", 205}, {L"32", 210},
	{L"33", 215}, {L"34", 221}, {L"35", 226}, {L"36", 232}, {L"37", 237}, {L"38", 243}, {L"39", 249}, {L"40", 255},
	{L"41", 261}, {L"42", 267}, {L"43", 274}, {L"44", 280}, {L"45", 287}, {L"46", 294}, {L"47", 301}, {L"48", 309},
	{L"49", 316}, {L"50", 324}, {L"51", 332}, {L"52", 340}, {L"53", 348}, {L"54", 357}, {L"55", 365}, {L"56", 374},
	{L"57", 383}, {L"58", 392}, {L"59", 402}, {L"60", 412}, {L"61", 422}, {L"62", 432}, {L"63", 442}, {L"64", 453},
	{L"65", 464}, {L"66", 475}, {L"67", 487}, {L"68", 499}, {L"69", 511}, {L"70", 523}, {L"71", 536}, {L"72", 549},
	{L"73", 562}, {L"74", 576}, {L"75", 590}, {L"76", 604}, {L"77", 619}, {L"78", 634}, {L"79", 649}, {L"80", 665},
	{L"81", 681}, {L"82", 698}, {L"83", 715}, {L"84", 732}, {L"85", 750}, {L"86", 768}, {L"87", 787}, {L"88", 806},
	{L"89", 825}, {L"90", 845}, {L"91", 866}, {L"92", 887}, {L"93", 909}, {L"94", 931}, {L"95", 953}, {L"96", 976}
};


#define SIZE_OF_EDITVALUE 5
static WCHAR editValueHandler[SIZE_OF_EDITVALUE], resultText[36];
LPCWSTR CalculateSMDResistance(HWND editWindow);
int SMDTypeFinder(LPCWSTR editValue);
LPCWSTR SMDResistanceCalculator(int resistorType, LPWSTR editValue);
inline double Exponention(int number);





LPCWSTR CalculateSMDResistance(HWND editWindow)
{
	memset(editValueHandler, 0, sizeof(editValueHandler));
	GetWindowText(editWindow, editValueHandler, 5);

	int resistorSMDType = SMDTypeFinder(editValueHandler);

	return SMDResistanceCalculator(resistorSMDType, editValueHandler);
}


int Rposition;
int SMDTypeFinder(LPCWSTR editValue)
{
	// ZERO
	if (editValue[0] == L'0')
	{
		for (int index = 1; index < SIZE_OF_EDITVALUE; index++)
		{
			switch (editValue[index])
			{
				case L'0':
					continue;

				case L'\0':
					return ZERO;
			}
			break;
		}
	}


	// Valid SMD codes must contain at least 3 characters (EXCEPT ZERO).
	if (editValue[2] != L'\0')
	{

		// 3DIGITS, EIA96, 4DIGITS
		if ((editValue[0] >= L'0' && editValue[0] <= L'9')
			&& (editValue[1] >= L'0' && editValue[1] <= L'9'))
		{
			if (editValue[3] == L'\0')
			{
				// 3DIGITS
				if (editValue[2] >= L'0' && editValue[2] <= L'9')
					return _3DIGITS;


				// EIA96
				// The numbers on EIA96 type SMD resistors must be between 01-96.
				if ((editValue[0] == L'0' && editValue[1] == L'0')
					|| (editValue[0] == L'9' && (editValue[1] >= L'7' && editValue[1] <= L'9')))
				{
					return WRONGTYPE;
				}
				else
				{
					for (int index = 0; index < sizeof(eia96Letters) / sizeof(eia96Letters[0]); index++)
					{
						if (editValue[2] == eia96Letters[index].letter)
							return EIA96;
					}
				}
			}


			// 4DIGITS
			else if ((editValue[2] >= L'0' && editValue[2] <= L'9')
				&& (editValue[3] >= L'0' && editValue[3] <= L'9'))
			{
				return _4DIGITS;
			}
		}


		// RDIGITS, DIGIT_R_DIGIT
		/*
			There must be one R letter only on SMD code
			and the R letter mustn't be at last place:
			• VALID: R91, 5R3, 35R3 etc.
			• INVALID: R3R, 4R5R, RR6R, 99R, 123R etc.
		*/
		if (((editValue[0] == L'R') + (editValue[1] == L'R') + (editValue[2] == L'R') == 1)
			&& (editValue[3] != L'R'))
		{
			Rposition = 0;
			for (int finderR = 0; editValue[finderR] != L'\0'; finderR++)
			{
				if (editValue[finderR] == L'R')
				{
					Rposition = finderR;
					continue;
				}

				if (editValue[finderR] < L'0' || (editValue[finderR] > L'9'))
					return WRONGTYPE;
			}
			return (Rposition == ATFIRSTDIGIT) ? RDIGITS : DIGITRDIGIT;
		}

	}

	// NONE OF THEM
	return WRONGTYPE;
}



LPCWSTR SMDResistanceCalculator(int resistorType, LPWSTR editValue)
{
	double resistanceValue = 0;
	div_t divide = { 0 };


	switch(resistorType)
	{
		case _3DIGITS:
		case _4DIGITS:
		{
			for (int i = 2; i < resistorType + 3; i++)
			{
				resistanceValue += (100.0 / Exponention(i - resistorType)) * (editValue[i - 2] - L'0');
			}

			if (resistanceValue == 0.0)
				return L"0 Ohms";

			divide = div((editValue[resistorType + 1] - L'0'), 3);
			resistanceValue *= Exponention(divide.rem);
			break;
		}

		case EIA96:
		{
			WCHAR firstTwoLetters[3];
			int eia96Value = 0;
			double eia96Multiplier = 0.0;

			_snwprintf_s(firstTwoLetters, sizeof(firstTwoLetters), L"%c%c", editValue[0], editValue[1]);

			for (int index = 0; index < sizeof(eia96Codes)/sizeof(eia96Codes[0]); index++)
			{
				if (wcscmp(firstTwoLetters, eia96Codes[index].code) == 0)
				{
					eia96Value = eia96Codes[index].value;
					break;
				}
			}

			for (int index = 0; index < sizeof(eia96Letters)/sizeof(eia96Letters[0]); index++)
			{
				if (editValue[2] == eia96Letters[index].letter)
				{
					eia96Multiplier = eia96Letters[index].multiplier;
					break;
				}
			}

			resistanceValue = eia96Value * eia96Multiplier;
			break;
		}

		case RDIGITS:
		{
			if (editValue[3] == L'\0')
			{
				resistanceValue = (10 * (editValue[1] - L'0')) + (editValue[2] - L'0');
				resistanceValue /= 100.f;
			}
			else
			{
				resistanceValue = (100 * (editValue[1] - L'0')) + (10 * (editValue[2] - L'0')) + (editValue[3] - L'0');
				resistanceValue /= 1000.f;
			}

			break;
		}

		case DIGITRDIGIT:
		{
			for (int digit = Rposition - 1, index = 0; digit >= 0; digit--, index++)
				resistanceValue += Exponention(digit) * (editValue[index] - L'0');

			for (int digit = Rposition + 1, pow = 1; editValue[digit] != L'\0'; digit++, pow++)
				resistanceValue += (editValue[digit] - L'0') / Exponention(pow);

			break;
		}

		case ZERO:
			return L"0 Ohms";

		case WRONGTYPE:
		default:
			return L"Wrong SMD Code!";
	}


	while (resistanceValue >= 1000.f)
	{
		resistanceValue /= 1000.f;
		divide.quot++;
	}



	memset(resultText, 0, sizeof(resultText));
	// k for Kilo Ohms, M for Mega Ohms, G for Giga Ohms
	LPCWSTR abbr[4] = { L"", L"k", L"M", L"G" };
	_snwprintf_s(resultText, sizeof(resultText), L"%g%ls Ohms", resistanceValue, abbr[divide.quot]);

	return resultText;
}



LPCWSTR CalculateTHTResistance(int prevRadioState)
{
	double resistanceValue = 0.0;
	div_t divide = { 0 };
	int bandColor1 = 0,
		bandColor2 = 0,
		bandColor3 = 0,
		bandMultiplier = 0,
		bandTolerance = 0,
		bandTempCoef = 0;

	int* bands[] = {
		&bandColor1, &bandColor2, &bandColor3,
		&bandMultiplier, &bandTolerance, &bandTempCoef
	};

	HWND* thtComboboxes[] = {
		&thtResistorColor_1, &thtResistorColor_2, &thtResistorColor_3,
		&thtResistorMultiplier, &thtResistorTolerance, &thtResistorTempCoef
	};


	for (int index = 0; index < sizeof(thtComboboxes) / sizeof(thtComboboxes[0]); index++)
		*bands[index] = SendMessage(*thtComboboxes[index], CB_GETCURSEL, 0, 0);


	if (prevRadioState == _4BANDSRADIOBUTTON)
		resistanceValue += (10.0 * bandColor1) + bandColor2;
	else if (prevRadioState == _5BANDSRADIOBUTTON || prevRadioState == _6BANDSRADIOBUTTON)
		resistanceValue += (100.0 * bandColor1) + (10.0 * bandColor2) + (bandColor3);


	if (bandMultiplier == 10 || bandMultiplier == 11)
		bandMultiplier = (-1 * bandMultiplier) + 9;

	divide = div(bandMultiplier, 3);
	resistanceValue *= Exponention(divide.rem);

	static const double valueTolerance[10] = {1.0, 2.0, 0.05, 0.02, 0.5, 0.25, 0.1, 0.01, 5.0, 10.0};
	static const int valueTempCoef[9] = {250, 100, 50, 15, 25, 20, 10, 5, 1};


	while (resistanceValue >= 1000.f)
	{
		resistanceValue /= 1000.f;
		divide.quot++;
	}



	memset(resultText, 0, sizeof(resultText));
	// k for Kilo Ohms, M for Mega Ohms, G for Giga Ohms
	LPCWSTR abbr[4] = {L"", L"k", L"M", L"G"};
	
	switch (prevRadioState)
	{
		case _4BANDSRADIOBUTTON:
		case _5BANDSRADIOBUTTON:
			_snwprintf_s(resultText, sizeof(resultText), L"%g%ls Ohms ±%g%%", resistanceValue, abbr[resistanceValue == 0.0 ? 0 : divide.quot], valueTolerance[bandTolerance]);
			break;
		case _6BANDSRADIOBUTTON:
			_snwprintf_s(resultText, sizeof(resultText), L"%g%ls Ohms ±%g%% %d ppm/°C", resistanceValue, abbr[resistanceValue == 0.0 ? 0 : divide.quot], valueTolerance[bandTolerance], valueTempCoef[bandTempCoef]);
			break;
	}

	return resultText;
}


// Calculates (10^number)
inline double Exponention(int number)
{
	double result = 1.0;
	if (number > 0)
	{
		for (int exp = 0; exp < number; exp++)
		{
			result *= 10.0;
			if (result >= 1000.0)
				result /= 1000.0;
		}
	}
	else if (number < 0)
	{
		for (int exp = 0; exp > number; exp--)
			result /= 10.0;
	}

	return result;
}