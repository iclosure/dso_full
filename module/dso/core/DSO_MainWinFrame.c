
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
 File        : DSO_MaiWinFrame.C
 Purpose     : DSO's main windows frame.
   ----------------------------------------------------------------------
 */

#include "DSO.h"
#include "WM.h"
#include "DSO_Private.h"
#include "EDIT.h"
#include "MULTIPAGE.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "integer.h"
#include "MATH_.h"


extern void TEST(void);

#ifndef pi
#define pi  3.141592653
#endif /*pi*/


// 从外部RAM读取256点字节型数据[可能是A/D采样数据]
void DSO_TestFFT(void)
{
    int i;
    float t=0.0;
	int fftdata[1024];
	I16 drdata[600];
	float fs = 4000;
	//float f0 = 1000;
	
    for(i=0; i<1024; i++, t+=1.0/fs) {
		//for(i=0,t=0; i<1024; i++, t+=1.0/fs) {
        //fftdata[i] = 100.0 + 100.0*(6.0 + 3.0*cos(2.0*pi*fs*t+0.0*pi/180.0) + 4.5*cos(2.0*pi*200*rand()*t+0.0*pi/180.0)+ 0.5*cos(2.0*pi*1000*t+0.0*pi/180.0));
		//fftdata[i] = 100.0*(6.0 + 3.0*cos(2.0*pi*fs*t+0.0*pi/180.0) + 10*cos(rand()*100)+ 0.5*cos(2.0*pi*1000*t+0.0*pi/180.0));
        fftdata[i] = 128*(0.5 + 0.3*cos(2.*pi*50.*t) +0.2*cos(2.*pi*75.*t) + 0.8*cos(2.*pi*2000.*t) + 0.08*cos(rand()*100));  // 直流分量为 6.
		//fftdata[i] = 25 + 25*(6.0 + 3.0 * cos(2.0*pi*fs*t+0.0*pi/180.0) + 1.2*cos(rand()*100*t));
	}
	
	for(i=0; i<600; i++)
		drdata[i] = - fftdata[i]/2;
	GUI_SetColor(GUI_YELLOW);
	GUI_DrawGraph(drdata,600,0,150);

    MATH_FFT(fftdata,10,1);
	
	for(i=0; i<512; i++)
		drdata[i] = - fftdata[i]*5;
	GUI_SetColor(GUI_RED);
	GUI_DrawGraph(drdata,512,0,350);
	
	fftdata[1] = 10*fs;
	
	GUI_SetFont(&GUI_Font8x16);
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringAt("Amplitude: ",50,100);
	GUI_DispFloatMin(fftdata[2]/100, 4);
	GUI_DispString("mV");
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringAt("     Freq: ",50,116);
	GUI_DispFloatMin(fftdata[3], 4);
	GUI_DispString("Hz");
}

// 创建示波器整体框架和主菜单栏
static FRAMEWIN_Handle DSO_CreateMainWin(void) {
	int tSize;
	WM_HWIN hThis;

	tSize = FRAMEWIN_GetDefaultCaptionSize();
	FRAMEWIN_SetDefaultCaptionSize(1);
	hThis = FRAMEWIN_CreateEx(-1,-4,LCD_XSIZE,LCD_YSIZE+5, WM_HBKWIN, WM_CF_SHOW, \
		FRAMEWIN_CF_TITLEVIS, 0, NULL, &_cbMainMenu);
	FRAMEWIN_SetDefaultCaptionSize(tSize);
	FRAMEWIN_SetClientColor(hThis, 0x303030);
	
	DSO_MENU_CreateMenu(hThis);
	
	return hThis;
}

// 初始化示波器主界面
void DSO_InitGUI(void)
{
	WM_HWIN hTemp,hWaveArea;
	BUTTON_Handle hButton;

	//TEST();
	// 显示鼠标标志
	GUI_CURSOR_Select(&GUI_CursorArrowM);
	GUI_CURSOR_Show(); 
	WM_SetCreateFlags(WM_CF_MEMDEV);  // 防屏闪

	// 创建示波器整体框架和主菜单栏
	hTemp = WM_GetClientWindow(DSO_CreateMainWin());
	// 创建波形显示，数显示窗口
	hWaveArea = DSO_CreateWaveWin(hTemp);
	DSO_SetWaveWindowMode(DSO_WAVEWIN_LARGE);
	WM_SetCallback(hWaveArea, &_cbWaveWin);
	// 创建右边的按钮
	hButton = DSO_CreateRightButton(hTemp);

	while(1) {

		WM_Paint(hWaveArea);
		WM_Exec();
	}
}



