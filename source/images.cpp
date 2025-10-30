#include "Resistor Value Calculator.h"





HICON smdResistorIcon, smdCodeEntryIcon, thtResistorIcon, thtEntryIcon;
void LoadImages()
{
	HICON* icons[] = {&smdResistorIcon, &smdCodeEntryIcon, &thtResistorIcon, &thtEntryIcon};
	int iconSize_px[] = {128, 256, 128, 384};
	for (int imageId = IDI_SMD_ICON, index = 0; imageId <= IDI_THTENTRY_ICON; imageId++, index++)
	{
		*icons[index] = (HICON)LoadImage(
			GetModuleHandle(NULL),
			MAKEINTRESOURCE(imageId),
			IMAGE_ICON,
			DPIScale(iconSize_px[index]), DPIScale(iconSize_px[index]),
			LR_CREATEDIBSECTION);
	}
}



void DrawImages(HDC hdc, int page)
{
	switch (page)
	{
		case MAINPAGE:
		{
			DrawIconEx(hdc,
				DPIScale(106), DPIScale(170),
				smdResistorIcon,
				0, 0, 0, NULL, DI_NORMAL);

			DrawIconEx(hdc,
				DPIScale(266), DPIScale(170),
				thtResistorIcon,
				0, 0, 0, NULL, DI_NORMAL);

			break;
		}

		case SMDCALCULATORPAGE:
		{
			DrawIconEx(hdc,
				DPIScale(122), DPIScale(50),
				smdCodeEntryIcon,
				0, 0, 0, NULL, DI_NORMAL);

			break;
		}

		case THTCALCULATORPAGE:
		{
			DrawIconEx(hdc,
				DPIScale(58), DPIScale(50),
				thtEntryIcon,
				0, 0, 0, NULL, DI_NORMAL);
			break;
		}

		default:
			break;
	}
}