/*
 * ***************************************************
 *                  │╖    ╓ ╔══╗ ╥ ╔══╕│
 *                  │╚══╝ ╜    ╙ ╨ ╚══╛│
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
 File        : main.h
 Purpose     : main file.
   ----------------------------------------------------------------------
 */ 

#ifdef WIN32

#if  0000

#include "GUI.h"
#include "DSO.h"
#include "MENU.h"
#include "WAVE.h"
#include "SysVar.h"
#include "KEY.h"
#include "target.h"
#include "BMP.h"
#include <stdio.h>
#include <stdlib.h>
// uCOS-II_Demo ->
#include "SystemConfig.h"

OS_STK MainTaskSize[128];  /* 定义堆栈大小*/
OS_STK FSTaskSize[128];    /* 定义堆栈大小*/

void AppDSOMainTask(void *param) { 

	OSStatInit();  /* 这个是必须的 */

	while (1) {

		WAVE_FreshWaveWin();
		MATH_SincInterp_test();
		
		/********************************/
		if (ActivateSK.Option == STATIC_OR_ACTIVATE_OR_SELMENUUP)
			MENU_DispActivate(*ActivateSK.pMenuUp);

		/********************************/
		//printf("Hello uCOS-II!\n");
		/* 延时 1/200 秒 */
		OSTimeDlyHMSM(0,0,0,5); /* 1 s = 10^3 ms（毫秒） = 10^6 us （微秒）= 10^9 ns（纳秒） = 10^12 ps（皮秒）\
								  = 10^15 fs（飞秒）=10^18阿秒=10^21渺秒=10^43普朗克常数 */
	}
}

void AppDSOFreshScreen(void *param) {

	OSStatInit();  /* 这个是必须的 */

	while(1) {

		/********************************/
		KEY_GetDecode();
		KEY_Response();
		/********************************/
		LCD_DispLCD();
		/* 延时 1/200 秒 */
		OSTimeDlyHMSM(0,0,0,5);
	}
}

int main(int argc, char **argv) {

	GUI_Init();
	DSO_InitWin();

	OSInit();   /* 这个是必须的 */

	/* 创建多任务 */
	OSTaskCreate(AppDSOMainTask, NULL,(OS_STK *)&FSTaskSize[127], 4);
	OSTaskCreate(AppDSOFreshScreen, NULL,(OS_STK *)&MainTaskSize[127], 5);

	OSStart();  /*开始任务调度 */

	return 0;
}

#endif  /* 0000 */ 

#endif /*WIN32*/