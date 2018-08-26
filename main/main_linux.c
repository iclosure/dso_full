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
#include <malloc.h>
//// linux header
#include <unistd.h>   
#include <sys/time.h>
// thread header
#include <pthread.h>



void AppDSOMainTask(void *param) { 

	while (1) {

		WAVE_FreshWaveWin();
		MATH_SincInterp_test();
		
		/********************************/
		if (ActivateSK.Option == STATIC_OR_ACTIVATE_OR_SELMENUUP)
			MENU_DispActivate(*ActivateSK.pMenuUp);

		/********************************/
		//printf("Hello uCOS-II!\n");
		/* 延时 ? 秒 */
		usleep(100);
	}
}

void AppDSOFreshScreen(void *param) {

	while(1) {

		/********************************/
		KEY_GetDecode();
		KEY_Response();
		/********************************/
		LCD_DispLCD();
		/* 延时 ? 秒 */
		usleep(100);
	}
}

int main(int argc, char **argv) {

	GUI_Init();
	DSO_InitWin();

	{
		pthread_t *pthreadId;
		pthreadId = (pthread_t *)malloc(2*sizeof(pthread_t));
		/* 创建多任务 */
		pthread_create(pthreadId+0, NULL, (void *)AppDSOMainTask,	 pthreadId+0);
		pthread_create(pthreadId+1, NULL, (void *)AppDSOFreshScreen, pthreadId+1);

	}

	while(1) {

	}

	return 0;
}

 

#endif /* 0000 */