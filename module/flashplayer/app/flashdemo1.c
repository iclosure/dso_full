/*------------------------------------------------------
  File : 2DGL_FlashPlay.c Purpose : Example for Flash Play files 
  ---------------------------------------------------------------------- */ 
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "GUI.h" 
/******************************************************************* 
* 
*					Static functions 
* 
******************************************************************** 
*/

extern void GUI_ReleasFlash(); 
extern void GUI_FlashPlay(int x0,int y0); 
extern int GUI_FLASH_Draw(int x0, int y0); 
extern void GUI_LoadFlash(char *filename); 

/******************************************************************* 
 * 
 * _ShowJPG 
 * 
 * Shows the contents of a JPEG file */ 

static void _ShowFLASH(char*filename) 
{ 
	int count=200; 

	GUI_ClearRect(50, 60, 550, 360);

	GUI_LoadFlash(filename); 
	do{ 
		GUI_FlashPlay(50,60);
		GUI_Exec(); 
		GUI_Delay(10);
	} while(count--);
	GUI_ReleasFlash(); 
	//free(pFile);
} 

/******************************************************************* 
*
* _DrawWindowsDirectoryBitmaps 
* 
* Iterates over all 
*.jpg-files of the windows directory 
*/ 

void GUI_SetAlpha(int a) {} // 本函数还未定义


static void _DrawWindowsDirectoryFLASHs(void) 
{ 
	char acPath[_MAX_PATH]; 
	char acMask[_MAX_PATH]; 
	char acFile[_MAX_PATH]; 
	WIN32_FIND_DATA Context; 
	HANDLE hFind; 
	GUI_SetAlpha(0); 
	GUI_SetBkColor(GUI_BLACK); 
	GUI_Clear(); 
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_Font24_ASCII);
	GUI_DispStringHCenterAt("DrawFLASH - Sample", 160, 5);
	GUI_SetFont(&GUI_Font8x16); 
	//GetWindowsDirectory(acPath, sizeof(acPath)); 
	sprintf(acPath,"%s","c:\\flashdemo\\"); 
	sprintf(acMask, "%s*.swf", acPath); 
	hFind = FindFirstFile(acMask, &Context);
	if (hFind != INVALID_HANDLE_VALUE) 
	{ 
		do { 
			sprintf(acFile, "%s%s", acPath, Context.cFileName);
			GUI_DispStringAtCEOL(acFile, 5, 40);
			_ShowFLASH(acFile);
		} while (FindNextFile(hFind, &Context));
	} 
}

/******************************************************************* 
 *
 * MainTask 
 * 
 ******************************************************************** 
 */ 

void MainTask_flash(void) 
{ 
	GUI_Init(); 
	// _ShowFLASH();
	while(1)
	{ 
		_DrawWindowsDirectoryFLASHs();
	} 
} 
