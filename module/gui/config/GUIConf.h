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
File        : GUIConf.h
Purpose     : Configures abilities, fonts etc.
----------------------------------------------------------------------
*/


#ifndef GUICONF_H
#define GUICONF_H

#define GUI_OS                    (1)  /* Compile with multitasking support */
#define GUI_LINUX                 (1)  /*  */
#define GUI_SUPPORT_CURSOR        (1)  /* for linux mouse */
#define GUI_SUPPORT_TOUCH         (1)  /* Support a touch screen (req. win-manager) */
#define GUI_SUPPORT_UNICODE       (1)  /* Support mixed ASCII/UNICODE strings */

#define GUI_DEFAULT_FONT          &GUI_Font6x8
//#define GUI_ALLOC_SIZE            (125000)  /* Size of dynamic memory ... For WM and memory devices*/
#define GUI_ALLOC_SIZE            (10240*1024)  /* Size of dynamic memory ... For WM and memory devices*/

/*********************************************************************
*
*         Configuration of available packages
*/

#define GUI_WINSUPPORT            (1) /* Window manager package available */
//or #define GUI_SUPPORT_DEVICES  (1)  /* Window manager package available */
#define GUI_SUPPORT_MEMDEV        (1) /* Memory devices available */
#define GUI_SUPPORT_AA            (1) /* Anti aliasing available */


#define FRAMEWIN_FRAMECOLOR_DEFAULT    (0xECE9D8)

/*********************************************************************
*
*         Multiplayer task
*/

//#define GUI_MT                (1)    // 为1时启动多任务支持
//#define GUI_MAX_TASK          (5)    // 能调用ucGUI的任务的最大数量






#endif  /* Avoid multiple inclusion */



