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
 File        : DSO_CallBack.c
 Purpose     : Some Call Back functions.
   ----------------------------------------------------------------------
 */

#include "DSO.h"
#include "GUI_Protected.h"
#include "DSO_Private.h"
#include "DSO_Protected.h"
#include "TEXT.h"
#include "EDIT.h"
#include "SLIDER.h"
#include "LISTBOX.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#pragma warning (disable : 4010)  // warning C4010: single-line comment contains line-continuation character
#endif 

void DSO_TestFFT(void);

/*********************************************************
 *********************************************************
 *
 *                 主窗口的二级回调函数
 */

/*******************************************************************
 *
 *       _cbBox_AboutInfiniium
 */
static char *_aAboutStr = ""
	"Copyright(C) 2010-2013\n "
	 "UNIC\n "
	 "www.unic.com\n "
	 "Programmed by unic";

static void _cbBox_AboutInfiniium(WM_MESSAGE* pMsg) {
	WM_HWIN hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_PAINT: {
		//char acText[16] = "V";

		//strcat(acText, GUI_GetVersionString());
		GUI_SetColor(GUI_BLACK);
		GUI_SetFont(&GUI_Font10_1);
		GUI_SetTextMode(GUI_TM_TRANS);
		GUI_DrawBitmap(&bmbutton_logo, 30, 4);
		GUI_DispStringHCenterAt("DSO V1.0", 49, 48);
		GUI_DispStringHCenterAt("礐/GUI", 138, 38);
		//GUI_DispStringHCenterAt(acText,  138, 48);
		GUI_DispStringHCenterAt("Compiled " __DATE__ " "__TIME__, 88, 68);
		GUI_DispStringHCenterAt(_aAboutStr, 88, 84);
		break; }
	case WM_NOTIFY_PARENT:
		if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
			GUI_EndDialog(hWin, 1);
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

/*********************************************************************
*
*              Initializers for listbox
*/
GUI_ConstString _apListBox[] = {
	"English", "Deutsch", "Fran鏰is", "Japanese", "Italiano", NULL
};

static void _cbBox_Math_FFT(WM_MESSAGE* pMsg) {
	int NCode, Id;
	WM_HWIN hEdit0, hEdit1, hEdit2, hEdit3, hListBox, hDropd0, hDropd1;
	WM_HWIN hWin = pMsg->hWin;

	switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
      /* Get window handles for all widgets */
      hEdit0   = WM_GetDialogItem(hWin, GUI_ID_EDIT0);
      hEdit1   = WM_GetDialogItem(hWin, GUI_ID_EDIT1);
      hEdit2   = WM_GetDialogItem(hWin, GUI_ID_EDIT2);
      hEdit3   = WM_GetDialogItem(hWin, GUI_ID_EDIT3);
      hListBox = WM_GetDialogItem(hWin, GUI_ID_LISTBOX0);
      hDropd0  = WM_GetDialogItem(hWin, GUI_ID_DROPDOWN0);
      hDropd1  = WM_GetDialogItem(hWin, GUI_ID_DROPDOWN1);
      /* Initialize all widgets */
      EDIT_SetText(hEdit0, "EDIT widget 0");
      EDIT_SetText(hEdit1, "EDIT widget 1");
      EDIT_SetTextAlign(hEdit1, GUI_TA_LEFT);
      EDIT_SetHexMode(hEdit2, 0x1234, 0, 0xffffff);
      EDIT_SetBinMode(hEdit3, 0x1234, 0, 0xffff);
      LISTBOX_SetText(hListBox, _apListBox);
      WM_DisableWindow (WM_GetDialogItem(hWin, GUI_ID_CHECK1));
      CHECKBOX_Check(  WM_GetDialogItem(hWin, GUI_ID_CHECK0));
      CHECKBOX_Check(  WM_GetDialogItem(hWin, GUI_ID_CHECK1));
      SLIDER_SetWidth( WM_GetDialogItem(hWin, GUI_ID_SLIDER0), 5);
      SLIDER_SetValue( WM_GetDialogItem(hWin, GUI_ID_SLIDER1), 50);
      SCROLLBAR_CreateAttached(hListBox, SCROLLBAR_CF_VERTICAL);
      DROPDOWN_AddString(hDropd0, "Item 0");
      DROPDOWN_AddString(hDropd0, "Item 1");
      DROPDOWN_AddString(hDropd0, "Item 2");
      DROPDOWN_AddString(hDropd1, "Item 0");
      DROPDOWN_AddString(hDropd1, "Item 1");
      DROPDOWN_AddString(hDropd1, "Item 2");
      DROPDOWN_AddString(hDropd1, "Item 3");
      DROPDOWN_AddString(hDropd1, "Item 4");
      break;
	case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
		NCode = pMsg->Data.v;               /* Notification code */
		switch (NCode) {
		case WM_NOTIFICATION_RELEASED:    /* React only if released */
			if (Id == GUI_ID_OK) {          /* OK Button */
				GUI_EndDialog(hWin, 0);
			}
			if (Id == GUI_ID_CANCEL) {      /* Cancel Button */
				GUI_EndDialog(hWin, 1);
			}
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
  }
}
/*********************************************************
 *********************************************************
 *           
 *                 主窗口回调函数的中间子函数
 */

/*********************************************************
 *
 *            _ShowBox_Math_FFT
 */
static void _ShowBox_Math_FFT(void) {
	WM_HWIN hDialog;
	/* Create framewin */
	//hDialog = FRAMEWIN_CreateEx(LCD_XSIZE_CENTER2-180/2, LCD_YSIZE_CENTER2-160/2, 180, 160, WM_HBKWIN, WM_CF_SHOW, FRAMEWIN_CF_MOVEABLE,
		//0, "Dialog", &_cbBox_Math_FFT);

	hDialog = GUI_ExecDialogBox(_aDialogCreate,GUI_COUNTOF(_aDialogCreate), &_cbBox_Math_FFT,WM_HBKWIN,\
		LCD_XSIZE_CENTER2-180/2, LCD_YSIZE_CENTER2-160/2);
	/* Exec modal dialog */
	WM_SetFocus(hDialog);
	WM_MakeModal(hDialog);
}
/*********************************************************
 *
 *            _ShowBox_AboutInfiniium
 */

static void _ShowBox_AboutInfiniium(void) {
	WM_HWIN hFrame, hItem;
	/* Create framewin */
	hFrame = FRAMEWIN_CreateEx(LCD_XSIZE_CENTER2-180/2, LCD_YSIZE_CENTER2-160/2, 180, 160, WM_HBKWIN, WM_CF_SHOW, FRAMEWIN_CF_MOVEABLE, \
		0, "About Infiniium", &_cbBox_AboutInfiniium);
	/* Create dialog items */
	hItem = BUTTON_CreateEx(111, 7, 55, 18, WM_GetClientWindow(hFrame), WM_CF_SHOW, 0, GUI_ID_OK);
	BUTTON_SetText(hItem, "Ok");
	/* Exec modal dialog */
	WM_SetFocus(hFrame);
	WM_MakeModal(hFrame);
}

static void _OnMenu2(WM_MESSAGE* pMsg) {
	MENU_MSG_DATA *pData = (MENU_MSG_DATA*)pMsg->Data.p;
	//MENU_Handle   *phMenu = pMsg->hWin;
	switch (pData->MsgType) {
	case MENU_ON_INITMENU:
		break;
	case MENU_ON_ITEMSELECT:
		switch (pData->ItemId) {

		case MENU_ID_MATH1:
			_ShowBox_Math_FFT();
			break;
		case MENU_ID_FILE3:
			GUI_MessageBox("MENU_ID_FILE3","Dialog",WM_CF_SHOW);
			break;
		case GUI_ID_CANCEL:
			WM_DeleteWindow(pMsg->hWinSrc);
			break;
		case MENU_ID_HELP1:
			
			break;
		case MENU_ID_HELP2:
			_ShowBox_AboutInfiniium();
			break;
		}
    break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

/*********************************************************
 *
 *            主菜单回调函数
 */

void _cbMainMenu(WM_MESSAGE* pMsg) {
	switch(pMsg->MsgId)
	{
	case WM_CREATE:
		
		break;
	case WM_MENU:
		_OnMenu2(pMsg);
		break;
	case WM_PAINT:
		
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

/*********************************************************
 *           
 *                 主窗口右边的按钮的回调函数
 */

void _cbButton_amplitude(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_area(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_downshoot(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_dutycycle(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_freq(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_logo(WM_MESSAGE *pMsg)
{
}

void _cbButton_maximum(WM_MESSAGE *pMsg) {
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_mean(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_minimum(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_negwidth(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_period(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_poswidth(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_topvalue(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_trifall(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_tririse(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_upshoot(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

void _cbButton_vpp(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_CREATE:

			break;
		case WM_PAINT:

			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

/*********************************************************
 *
 *            波形窗口回调函数
 */

void _cbWaveWin(WM_MESSAGE* pMsg) {
	switch(pMsg->MsgId)
	{
	case WM_PAINT:
		DSO_CreateWaveWindow();
		//GUI_DrawBitmap(&bmwavewin_large,0,0);
		//GUI_GIF_Draw(acwavewin_large_gif, sizeof(acwavewin_large_gif),0,0);
		DSO_TestFFT();
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

// 波形窗口的相关参数、图标设置的回调函数
void _cbWaveWinPara(WM_MESSAGE* pMsg) {
	WM_HWIN hWaveWin;
	switch(pMsg->MsgId)
	{
	case WM_CREATE:
		DSO_CreateWaveWinPara(pMsg->hWin);
		break;
	case WM_PAINT:
		hWaveWin = DSO_GetWaveWinHandle();
		GUI_DrawBitmap(&bmMark_HLeftIcon,2,6);
		GUI_DrawBitmap(&bmMark_HRightIcon,WM_GetWinSizeX(hWaveWin)+10,WM_GetWinSizeY(hWaveWin)-401+6);
		GUI_DrawBitmap(&bmMark_VDownIcon,100,2);
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

