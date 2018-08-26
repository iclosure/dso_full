
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
 File        : DSOType.h
 Purpose     : DSO types define
   ----------------------------------------------------------------------
 */

#ifndef DSOTYPE_H_
#define DSOTYPE_H_


#include "GUIType.h"
#include "BUTTON.h"
#include "WM.h"

#if GUI_WINSUPPORT

/**************************************************************
 * 
 *          BUTTON_BkPicInfo 按钮型框架背景图标类型定义
 * 
 */

typedef struct __BUTTON_BkPicInfo {
	BUTTON_Handle hButton;
	const GUI_BITMAP GUI_UNI_PTR *pBitmap;
	int Id;
} BUTTON_BkPicInfo, *pBUTTON_BkPicInfo;


#endif



#endif /*DSOTYPE_H_*/
