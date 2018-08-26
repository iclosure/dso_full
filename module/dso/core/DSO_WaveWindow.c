
/*
 * ***************************************************
 *                  │╖  ╓ ╔══╗ ╥ ╔══╕│
 *                  │╚══╝ ╜  ╙ ╨ ╚══╛│
 *                          DSO
 *     Universal graphic software for embedded applications
 *
 *     (c) Copyright 2011, Unic Inc., China, Sc
 *     (c) Copyright 2011, SEGGER Microcontroller Systeme GmbH
 *  DSO is protected by international copyright laws. Knowledge of the
 *  source code may not be used to write a similar product. This file may
 *  only be used in accordance with a license and should not be redistributed
 *  in any way. We appreciate your understanding and fairness.
 * 
 *  Project : DSC--C-sources
 *  Aurthor : L.K.H.
 *  Version : V1.0 
 *  Data    : 09/20/2011
 * ---------------------------------------------------------------------
 File        : DSO_NetGrid.c
 Purpose     : DSO net drid.
   ----------------------------------------------------------------------
 */

#include "DSO.h"
#include "DSO_ConfDefaults.h"
#include "DSO_Private.h"
#include <stdlib.h>



#define WAVE_SMALL_HGRID    (25)
#define WAVE_SMALL_VGRID    (WAVE_SMALL_HGRID*2)

#define WAVE_LARGE_HGRID    (50)
#define WAVE_LARGE_VGRID    (WAVE_LARGE_HGRID)


static int WaveWindowMode = DSO_WAVEWIN_SMALL;   // 波形显示窗口默认为小模式

// 波形显示窗口句柄
static WM_HWIN hWaveWin;

// 波形显示窗口的显示模式设置
void DSO_SetWaveWindowMode(int mode) {
	WaveWindowMode = mode;
}


void DSO_CreateSmallWaveWindow(void) {
	int x,y;
	GUI_SetColor(DSO_WAVEWIN_BKCOLOR);
	GUI_FillRect(0,0,601,201);
	GUI_SetColor(DSO_WAVEWIN_GRIDCOLOR);
	GUI_DrawRect(0,0,600,200);
	for(y=25; y<240; y+=25)
		for(x=0;x<600; x+=2)
			GUI_DrawPixel(x,y);
	for(x=50; x<600; x+=50)
		for(y=0; y<240; y+=2)
			GUI_DrawPixel(x,y);
}

void DSO_CreateLargeWaveWindow(void) {
	int x,y;
	GUI_SetColor(DSO_WAVEWIN_BKCOLOR);
	GUI_FillRect(0,0,601,401);
	GUI_SetColor(DSO_WAVEWIN_GRIDCOLOR);
	GUI_DrawRect(0,0,600,400);
	for(y=50; y<400; y+=50)
		for(x=0;x<600; x+=2)
			GUI_DrawPixel(x,y);
	for(x=50; x<600; x+=50)
		for(y=0; y<400; y+=2)
			GUI_DrawPixel(x,y);
}

void DSO_CreateWaveWindow(void) {
	switch(WaveWindowMode) {
		case DSO_WAVEWIN_SMALL : DSO_CreateSmallWaveWindow(); break;
		case DSO_WAVEWIN_LARGE : DSO_CreateLargeWaveWindow(); break;
		default                : DSO_CreateSmallWaveWindow(); break;
	}
}

// 创建波形显示，数显示窗口
void DSO_CreateWaveWinPara(WM_HWIN hWin) {

	//WM_CreateWindowAsChild(5,3,20,20,hWin,WM_CF_SHOW,&_cbWaveWinPara,0);
	//GUI_SetColor(GUI_YELLOW);
	//GUI_DrawEllipse(50,0,10,5);
	GUI_DrawBitmap(&bmMark_HRightIcon,4,0);

}

// 创建波形显示，数显示窗口
FRAMEWIN_Handle DSO_CreateWaveWin(WM_HWIN hWin) {
	int tSize;
	
	tSize = FRAMEWIN_GetDefaultCaptionSize();
	FRAMEWIN_SetDefaultCaptionSize(36);
	hWin = FRAMEWIN_CreateAsChild(-3,0,627,WM_GetWindowSizeY(hWin)+2, \
		hWin,NULL,&_cbWaveWinPara,WM_CF_SHOW);
	FRAMEWIN_SetBarColor(hWin,0,FRAMEWIN_FRAMECOLOR_DEFAULT);
	FRAMEWIN_SetBarColor(hWin,1,FRAMEWIN_FRAMECOLOR_DEFAULT);
	FRAMEWIN_SetDefaultCaptionSize(tSize);
	FRAMEWIN_SetClientColor(hWin,GUI_BLACK);
	hWaveWin = WM_CreateWindowAsChild(10, 10, 601, 401, WM_GetClientWindow(hWin), \
		WM_CF_SHOW,NULL,0);
	return hWaveWin;
}

// 获取波形显示窗口句柄
WM_HWIN DSO_GetWaveWinHandle(void) {
	return hWaveWin;
}