
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
 File        : DSO_Button.h
 Purpose     : DSO Button.
   ----------------------------------------------------------------------
 */

#include "DSO.h"
#include "WIDGET.h"
#include "BUTTON.h"
#include "EDIT.h"
#include "DSO_Private.h"
#include <stdlib.h>


  
// 绘制窗口最右边的按钮[]
BUTTON_Handle DSO_CreateRightButton(WM_HWIN hParent) {
	int i;
	BUTTON_Handle hThis;

	hThis = BUTTON_CreateAsChild(WM_GetWindowSizeX(hParent)-55, 0, 56, WM_GetWindowSizeY(hParent), \
		hParent,GUI_ID_INVALIDE, WM_CF_SHOW|WM_CF_DISABLED);
	
	for(i=0; i<8; i++) {
		BUTTON_Handle hThis1;
		hThis1 = BUTTON_CreateAsChild(3, 3+i*51, 50,50, hThis, _RightButton_BkPicInfo[i].Id,  WM_CF_SHOW);
		BUTTON_SetBitmapEx(hThis1,BUTTON_BI_UNPRESSED,_RightButton_BkPicInfo[i].pBitmap,5,5);
		BUTTON_SetBitmapEx(hThis1,BUTTON_BI_PRESSED,_RightButton_BkPicInfo[i].pBitmap,6,6);
	}

	return hThis;
}
