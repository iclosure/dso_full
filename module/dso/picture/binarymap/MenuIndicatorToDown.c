
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
 File        : MenuIndicatorToDown.c
 Purpose     : DSO : 菜单向下翻页指示器
   ----------------------------------------------------------------------
 */


#include "GUI.h"

 /*   Palette
 The following are the entries of the palette table.
 Every entry is a 32-bit value (of which 24 bits are actually used)
 the lower   8 bits represent the Red component,
 the middle  8 bits represent the Green component,
 the highest 8 bits (of the 24 bits used) represent the Blue component
 as follows:   0xBBGGRR
*/

const GUI_COLOR ColorsMenuIndicatorToDown[] = {
	0x0000,C24TO565RGB(0xE1E1E1)
};

const GUI_LOGPALETTE PalMenuIndicatorToDown = {
	2,	/* number of entries */
	1, 	/* No transparency */
	&ColorsMenuIndicatorToDown[0]
};
// Logo : UNIC
static GUI_CONST_STORAGE unsigned char acMenuIndicatorToDown[] = {
	_____XXX,XX______,
	_____XXX,XX______,
	_____XXX,XX______,
	XXXXXXXX,XXXXXXX_,
	_XXXXXXX,XXXXXX__,
	__XXXXXX,XXXXX___,
	___XXXXX,XXXX____,
	____XXXX,XXX_____,
	_____XXX,XX______,
	______XX,X_______,
	_______X,________
};

const GUI_BITMAP bmMenuIndicatorToDown = {
	15, /* XSize */
	11, /* YSize */
	2, /* BytesPerLine */
	1, /* BitsPerPixel */
	acMenuIndicatorToDown,  /* Pointer to picture data (indices) */
	&PalMenuIndicatorToDown  /* Pointer to palette */
};
