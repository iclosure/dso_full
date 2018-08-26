/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              礐/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI_X_Linux.C
Purpose     : COnfig / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#ifndef WIN32

#include "GUIConf.h"
#if GUI_LINUX    /* if it's Linux system */


//include "uCOS_Types.h"
//include "uCOS_II.h"
#include "GUI.H"
#include "GUI_X.H"
#include <stdio.h>
#include <string.h>

/* for linux framebuffer */
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <pthread.h> 


/*********************************************************************
*
*       Global data
*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


/*********************************************************************
*
*      Timing:
*                 GUI_X_GetTime
*                 GUI_X_Delay

  Some timing dependent routines of emWin require a GetTime
  and delay funtion. Default time unit (tick), normally is
  1 ms.
*/

int GUI_X_GetTime(void) {

    //return OSTimeGet();
	struct timeval tv;
	int tm;
	
	gettimeofday(&tv, NULL);
	//tm = tv.tv_sec*1024 + tv.tv_usec/1024;
	tm = tv.tv_sec*1024 + tv.tv_usec/1024;
	
	return tm;
}

void GUI_X_Delay(int Period) {
    //OSTimeDly(Period);
	//while(Period--) usleep(1);
}

/*********************************************************************
*
*       GUI_X_ExecIdle()
*/
void GUI_X_ExecIdle(void) {
    //OSTimeDly(1);       /* 调用uCOS-II的延时程序 */
	//usleep(1);
}

/*********************************************************************
*
*      Multitasking:
*
*                 GUI_X_InitOS()
*                 GUI_X_GetTaskId()
*                 GUI_X_Lock()
*                 GUI_X_Unlock()

Note:
  The following routines are required only if emWin is used in a
  true multi task environment, which means you have more than one
  thread using the emWin API.
  In this case the
                      #define GUI_OS 1
  needs to be in GUIConf.h
*/

//static OS_EVENT * DispSem;

U32  GUI_X_GetTaskId(void) { 
	//((U32)(OSTCBCur->OSTCBPrio)); 
	return ((U32)pthread_self());
}

void GUI_X_InitOS(void)    { 
	//DispSem = OSSemCreate(1); 
#if GUI_SUPPORT_CURSOR
	GUI_MOUSE_DRIVER_PS2_Init();   /* create read mouse thread for linux */
#endif /* #if GUI_SUPPORT_CURSOR */
}

void GUI_X_Unlock(void)    { 
	//OSSemPost(DispSem); 
	pthread_mutex_unlock(&mutex);
}

void GUI_X_Lock(void) {
    //INT8U err;
    //OSSemPend(DispSem, 0, &err);
	pthread_mutex_lock(&mutex); 
}


/*********************************************************************
*
*       GUI_X_Init()
*
* Note:
*     GUI_X_Init() is called from GUI_Init is a possibility to init
*     some hardware which needs to be up and running before the GUI.
*     If not required, leave this routine blank.
*/

void GUI_X_Init(void) { }




void GUI_X_Log     (const char *s) { /*GUI_USE_PARA(s);*/ }

void GUI_X_Warn    (const char *s) { /*GUI_USE_PARA(s);*/ }

void GUI_X_ErrorOut(const char *s) { /*GUI_USE_PARA(s);*/ }


#endif /* #if GUI_LINUX */
#endif /* #ifndef WIN32 */




