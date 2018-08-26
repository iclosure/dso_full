
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
 *  Project : DSC--H-sources
 *  Aurthor : L.K.H.
 *  Version : V1.0 
 *  Data    : 09/20/2011
 * ---------------------------------------------------------------------
 File        : DSO_Private.h
 Purpose     : DSO internal declarations.
   ----------------------------------------------------------------------
 */

#ifndef DSO_PRIVATE_H_
#define DSO_PRIVATE_H_


#include "FRAMEWIN.h"
#include "BUTTON.h"
#include "DSOType.h"
#include "MENU.h"



/**************************************************************
 * 
 *  DSO : User's Some Datas
 * 
 */

extern BUTTON_BkPicInfo _RightButton_BkPicInfo[17];
extern const GUI_WIDGET_CREATE_INFO _aDialogCreate[18];
extern const GUI_WIDGET_CREATE_INFO _aButtonCreate[10];
extern GUI_ConstString _apListBox[];
extern const GUI_WIDGET_CREATE_INFO _aMenuCreateTitle[9];

/**************************************************************
 * 
 *  DSO : Main Menu Info
 * 
 */
///////////////////////////////////////////////////////////
extern MENU_ITEM_DATA _MainMenu_Main[9];

///////////////////////////////////////////////////////////
extern MENU_ITEM_DATA _MainMenu_File[10];

///////////////////////////////////////////////////////////
extern MENU_ITEM_DATA _MainMenu_Control[4];

///////////////////////////////////////////////////////////
extern MENU_ITEM_DATA _MainMenu_Setup[10];

///////////////////////////////////////////////////////////
extern MENU_ITEM_DATA _MainMenu_Trigger[8];

///////////////////////////////////////////////////////////
extern MENU_ITEM_DATA _MainMenu_Measure[13];

///////////////////////////////////////////////////////////
extern MENU_ITEM_DATA _MainMenu_Math[6];

///////////////////////////////////////////////////////////
extern MENU_ITEM_DATA _MainMenu_Analyze[6];
extern MENU_ITEM_DATA _MainMenu_Analyze_AutoTest[3];

///////////////////////////////////////////////////////////
extern MENU_ITEM_DATA _MainMenu_Utilties[10];

///////////////////////////////////////////////////////////
extern MENU_ITEM_DATA _MainMenu_Help[2];

///////////////////////////////////////////////////////////

/*******************************************************************
*
*                     回调函数
*/

void _cbMainMenu(WM_MESSAGE *pMsg);  // 主菜单回调函数
void _cbButton_amplitude(WM_MESSAGE *pMsg);
void _cbButton_downshoot(WM_MESSAGE *pMsg);
void _cbButton_dutycycle(WM_MESSAGE *pMsg);
void _cbButton_freq(WM_MESSAGE *pMsg);
void _cbButton_logo(WM_MESSAGE *pMsg);
void _cbButton_maximum(WM_MESSAGE *pMsg);
void _cbButton_mean(WM_MESSAGE *pMsg);
void _cbButton_minimum(WM_MESSAGE *pMsg);
void _cbButton_negwidth(WM_MESSAGE *pMsg);
void _cbButton_poswidth(WM_MESSAGE *pMsg);
void _cbButton_topvalue(WM_MESSAGE *pMsg);
void _cbButton_trifall(WM_MESSAGE *pMsg);
void _cbButton_tririse(WM_MESSAGE *pMsg);
void _cbButton_upshoot(WM_MESSAGE *pMsg);
void _cbButton_vpp(WM_MESSAGE *pMsg);

void _cbWaveWin(WM_MESSAGE *pMsg);   // 波形窗口回调函数
void _cbWaveWinPara(WM_MESSAGE* pMsg); //

/*******************************************************************
*
*                     菜单显示控制函数
*/

void DSO_MENU_AddItem(MENU_Handle hObj, const char* pText, U16 Id, U16 Flags, MENU_Handle hSubmenu); // 
void DSO_MENU_CreateMenu(WM_HWIN hWin); // 

/*******************************************************************
*
*                     波形显示区的网络线绘制函数
*/

void DSO_SetWaveWindowMode(int mode);
void DSO_CreateSmallWaveWindow(void);
void DSO_CreateLargeWaveWindow(void);
void DSO_CreateWaveWinPara(WM_HWIN hWin);
void DSO_CreateWaveWindow(void);
WM_HWIN DSO_GetWaveWinHandle(void); // 获取波形显示窗口句柄
/*******************************************************************
*
*                     绘制窗口最右边的按钮[]
*/

BUTTON_Handle DSO_CreateRightButton(WM_HWIN hParent);
/*******************************************************************
*
*                   创建波形显示，数显示窗口
*/

FRAMEWIN_Handle DSO_CreateWaveWin(WM_HWIN hWin);






#endif /*DSO_PRIVATE_H_*/
