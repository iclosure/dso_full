/*
 * ***************************************************
 *                  ���Z    �W �X�T�T�[ �i �X�T�T�Y��
 *                  ���^�T�T�a �`    �] �l �^�T�T�_��
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

OS_STK MainTaskSize[128];  /* �����ջ��С*/
OS_STK FSTaskSize[128];    /* �����ջ��С*/

void AppDSOMainTask(void *param) { 

	OSStatInit();  /* ����Ǳ���� */

	while (1) {

		WAVE_FreshWaveWin();
		MATH_SincInterp_test();
		
		/********************************/
		if (ActivateSK.Option == STATIC_OR_ACTIVATE_OR_SELMENUUP)
			MENU_DispActivate(*ActivateSK.pMenuUp);

		/********************************/
		//printf("Hello uCOS-II!\n");
		/* ��ʱ 1/200 �� */
		OSTimeDlyHMSM(0,0,0,5); /* 1 s = 10^3 ms�����룩 = 10^6 us ��΢�룩= 10^9 ns�����룩 = 10^12 ps��Ƥ�룩\
								  = 10^15 fs�����룩=10^18����=10^21����=10^43���ʿ˳��� */
	}
}

void AppDSOFreshScreen(void *param) {

	OSStatInit();  /* ����Ǳ���� */

	while(1) {

		/********************************/
		KEY_GetDecode();
		KEY_Response();
		/********************************/
		LCD_DispLCD();
		/* ��ʱ 1/200 �� */
		OSTimeDlyHMSM(0,0,0,5);
	}
}

int main(int argc, char **argv) {

	GUI_Init();
	DSO_InitWin();

	OSInit();   /* ����Ǳ���� */

	/* ���������� */
	OSTaskCreate(AppDSOMainTask, NULL,(OS_STK *)&FSTaskSize[127], 4);
	OSTaskCreate(AppDSOFreshScreen, NULL,(OS_STK *)&MainTaskSize[127], 5);

	OSStart();  /*��ʼ������� */

	return 0;
}

#endif  /* 0000 */ 

#endif /*WIN32*/