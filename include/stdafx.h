#pragma once

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// C RunTime Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


// TODO: reference additional headers your program requires here
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")