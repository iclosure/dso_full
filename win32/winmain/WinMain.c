﻿/*
*********************************************************************************************************
*                                             uC/GUI V3.98
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
File        : SIM_X.c
Purpose     : Windows Simulator externals
              The init routine in this file can be used to set up the
              simulator
---------------------------END-OF-HEADER------------------------------
*/

#include "Win.h"
#include "GUI.h"
#include "LCDConf.h"
#include "LCDSIM.h"

#if 0000

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD.h"		          /* interface definitions */
#include "LCD_Private.h"      /* private modul definitions & config */
// LCD_GetNumLayers.c
int LCD_GetNumLayers(void) {return 1;}
// LCD_GetEx.c
int LCD_GetXSizeEx(int LayerIndex)  { return LCD_XSIZE;  }
int LCD_GetYSizeEx(int LayerIndex)  { return LCD_YSIZE;  }
int LCD_GetVXSizeEx(int LayerIndex) { return LCD_VXSIZE; }
int LCD_GetVYSizeEx(int LayerIndex) { return LCD_VYSIZE; }
int LCD_GetBitsPerPixelEx(int LayerIndex) { return LCD_BITSPERPIXEL; }
int LCD_GetBitsPerPixel_L0Ex(int LayerIndex) { return LCD_BITSPERPIXEL_L0; }
U32 LCD_GetNumColorsEx(int LayerIndex) { return LCD_NUM_COLORS; }
int LCD_GetYMagEx(int LayerIndex) { return LCD_YMAG; }
int LCD_GetXMagEx(int LayerIndex) { return LCD_XMAG; }
I32 LCD_GetFixedPaletteEx(int LayerIndex) { return LCD_FIXEDPALETTE; }
int LCD_GetMirrorXEx(int LayerIndex) { return LCD_MIRROR_X; }
int LCD_GetMirrorYEx(int LayerIndex) { return LCD_MIRROR_Y; }
int LCD_GetSwapXYEx(int LayerIndex)  { return LCD_SWAP_XY;  }
int LCD_GetSwapRBEx(int LayerIndex)  { return LCD_SWAP_RB;  }
int LCD_GetDeltaModeEx(int LayerIndex) { return LCD_DELTA_MODE; }
unsigned int LCD_Index2ColorEx(int index) { return index;}

// lib
int GUI_Delay(void) { return 0; }
#endif /* 0000 */


#include "Win.h"


void SIM_GUI_X_Init(void) {
	if (((LCD_GetDevCap(LCD_DEVCAP_XSIZE) * LCD_GetXMag()) == LCD_XSIZE) && 
		((LCD_GetDevCap(LCD_DEVCAP_YSIZE) * LCD_GetYMag()) == LCD_YSIZE))
	{
		SIM_SetLCDPos(30,30);                 // Define the position of the LCD in the bitmap
		SIM_SetTransColor(C24TO565RGB(0xFFFF00));          // Define the transparent color
	}
}


/*******************************************************************
*
*       MainTask
*
*       Demonstrates the use of a memory device
*
********************************************************************
*/

extern int main(void);

void MainTask(void) {;
	
	main();  // 进入用户的主函数 [ WIN32 -- system:windows/*consle*/ ]
}


#include "GUI.h"
#include "Win.h"
#include "FRAMEWIN.h"
#include "LISTBOX.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GUI.h"
#include "FRAMEWIN.h"
#include "MULTIPAGE.h"

static void _cbWinAlert(WM_MESSAGE* pMsg);

typedef void SERIAL_Callback(const char* pStr, int v1, int v2);

/*********************************************************************
*
*       defines and statics for serial interface
*       (defined for target hardware only)
*
**********************************************************************
*/
#ifndef WIN32
  #include "RTOS.h"

  /*********************************************************************
  *
  *       defines
  */
  #define EOL            13   /* sign marking end of line */
  #define BUFFER_SIZE   512   /* size of receive buffer */
  #define STRING_SIZE    32   /* size of string buffer */

  /*********************************************************************
  *
  *       structures
  */
  typedef struct {
    OS_U8* pDataEnd;
    OS_U8* pWrite;
    OS_U8* pRead;
    U16    Size;
  } BUFFER;

  /*********************************************************************
  *
  *       static data
  */
  static SERIAL_Callback* _pfcbReceiveCommand;

  /* buffer to hold string */
  static char   _acString[STRING_SIZE + 2];
  static char*  _pString = _acString;

  /* buffer for receiving */
  static OS_U8  _Buffer[BUFFER_SIZE];
  static BUFFER _RxBuffer = {_Buffer + BUFFER_SIZE, _Buffer, _Buffer, BUFFER_SIZE};
#endif  /* #ifndef WIN32 */

/*********************************************************************
*
*       defines
*
**********************************************************************
*/

#define PI2 6.2831853f

#define RPM  10
#define UPS 100

#define ARRAY(aItems) aItems, GUI_COUNTOF(aItems)

/*********************************************************************
*
*       structures
*
**********************************************************************
*/

typedef struct {
  I16 ActV;
  I16 NewV;
  const GUI_RECT Rect;
} OBJECT;

typedef struct {
  OBJECT Light;
  I16 Elevator;
} LEVEL;

typedef struct {
  OBJECT Itself;
  OBJECT Door;
  I16 NumToDo;
  I16 ToDo[6];
  I16 Move;
  I16 Pause;
  I16 Level;
  I16 LastLevel;
  int Time;
  WM_HWIN Handle;
} ELEVATOR;

/*********************************************************************
*
*       static data
*
**********************************************************************
*/

static SCROLLBAR_Handle _hScroll;
static WM_HWIN          _hAlert[2];
static WM_HWIN          _hDialogLight;
static WM_HWIN          _hWinHouse;
static WM_HWIN          _hWinControl;
static WM_HWIN          _hWinMap;

static const char _acAlertText[2][12] = {"Fire", "Burglary"};
static int        _AlertCnt[2];

static int    _SlidePrevTime;
static int    _ScrollPrevTime;

static int    _InitDialog;
static int    _ExecuteCommands;

static int    _LogoRPM      = RPM;
static int    _LogoWaitTime = 1000 / UPS;
static int    _LogoPrevTime;
static int    _LogoPrevMulX;
static int    _LogoMulX;
static float  _LogoDivisor;
static float  _LogoAngle;

static LEVEL _Level[6] = {
  {{0, 0, { 35, 650, 164, 780}}, 0},
  {{0, 0, { 35, 520, 164, 650}}, 0},
  {{0, 0, { 35, 390, 164, 520}}, 0},
  {{0, 0, { 35, 260, 164, 390}}, 0},
  {{0, 0, { 35, 130, 164, 260}}, 0},
  {{0, 0, { 35,   0, 164, 130}}, 0},
};

static ELEVATOR _Elevator = {
  {0, 0, { 57, 130,  83, 780}}, // the elevator itself
  {0, 0, { 57,  82,  83, 125}}, // the elevator door
  0, {0, 0, 0, 0, 0}, 0, 0, 0, 0, 0, 0
};

static OBJECT _Garage         = {0, 0, { 40, 732,  90, 776}};
static OBJECT _Jalousie1      = {0, 0, {165, 400, 167, 493}};
static OBJECT _Jalousie2      = {0, 0, { 32, 140,  34, 233}};
static OBJECT _Marquee1       = {0, 0, {165, 549, 196, 566}};
static OBJECT _Marquee2       = {0, 0, {  3, 289,  34, 306}};
static OBJECT _Scroll         = {0, 0, {  0,   0, 199, 780}};
static OBJECT _LogoArrow      = {0, 0, { 58,  69, 139, 100}};
static OBJECT _Logo           = {0, 0, { 58,  46, 139,  69}};

static OBJECT _LogoSmall      = {0, 0, {  7,   8,  47,  19}};
static OBJECT _GarageSmall    = {0, 0, { 10, 220,  24, 232}};
static OBJECT _Jalousie1Small = {0, 0, { 48, 120,  49, 147}};
static OBJECT _Jalousie2Small = {0, 0, {  6,  42,   7,  69}};
static OBJECT _Marquee1Small  = {0, 0, { 48, 166,  55, 170}};
static OBJECT _Marquee2Small  = {0, 0, {  0,  88,   7,  92}};
static OBJECT _ElevatorSmall  = {0, 0, { 14,  40,  23, 233}};

static OBJECT _LightSmall[6] = {
  {0, 0, { 8, 195, 48, 234}},
  {0, 0, { 8, 156, 48, 195}},
  {0, 0, { 8, 117, 48, 156}},
  {0, 0, { 8,  78, 48, 117}},
  {0, 0, { 8,  39, 48,  78}},
  {0, 0, { 8,   0, 48,  39}},
};

/*********************************************************************
*
*       static data, dialog resource
*
**********************************************************************
*/
/*********************************************************************
*
*       DialogLight
*/
static const GUI_WIDGET_CREATE_INFO _aDialogLight[] = {
  { WINDOW_CreateIndirect, "",           0,             0,   0, 113, 140, WM_CF_SHOW },
  { TEXT_CreateIndirect,     "5.Floor:", 0,             5,   8,  40,  23, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "4.Floor:", 0,             5,  33,  40,  23, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "3.Floor:", 0,             5,  58,  40,  23, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "2.Floor:", 0,             5,  83,  40,  23, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "1.Floor:", 0,             5, 108,  40,  23, TEXT_CF_LEFT },
  { SLIDER_CreateIndirect,   NULL,    GUI_ID_SLIDER4,  45,   4,  64,  23 },
  { SLIDER_CreateIndirect,   NULL,    GUI_ID_SLIDER3,  45,  29,  64,  23 },
  { SLIDER_CreateIndirect,   NULL,    GUI_ID_SLIDER2,  45,  54,  64,  23 },
  { SLIDER_CreateIndirect,   NULL,    GUI_ID_SLIDER1,  45,  79,  64,  23 },
  { SLIDER_CreateIndirect,   NULL,    GUI_ID_SLIDER0,  45, 104,  64,  23 }
};

/*********************************************************************
*
*       DialogMisc
*/
static const GUI_WIDGET_CREATE_INFO _aDialogMisc[] = {
  { WINDOW_CreateIndirect, "",           0,               0,   0, 113, 140, WM_CF_SHOW },
  { BUTTON_CreateIndirect, "Jalousie 1", GUI_ID_BUTTON0,  5,   3, 103,  19, TEXT_CF_HCENTER },
  { BUTTON_CreateIndirect, "Jalousie 2", GUI_ID_BUTTON1,  5,  24, 103,  19, TEXT_CF_HCENTER },
  { BUTTON_CreateIndirect, "Marquee 1",  GUI_ID_BUTTON2,  5,  45, 103,  19, TEXT_CF_HCENTER },
  { BUTTON_CreateIndirect, "Marquee 2",  GUI_ID_BUTTON3,  5,  66, 103,  19, TEXT_CF_HCENTER },
  { BUTTON_CreateIndirect, "Garage",     GUI_ID_BUTTON4,  5,  87, 103,  19, TEXT_CF_HCENTER },
  { BUTTON_CreateIndirect, "<",          GUI_ID_BUTTON5,  5, 108,  20,  19, TEXT_CF_HCENTER },
  { BUTTON_CreateIndirect, "LogoStop",   GUI_ID_BUTTON6, 27, 108,  59,  19, TEXT_CF_HCENTER },
  { BUTTON_CreateIndirect, ">",          GUI_ID_BUTTON7, 88, 108,  20,  19, TEXT_CF_HCENTER }
};

/*********************************************************************
*
*       DialogElev
*/
static const GUI_WIDGET_CREATE_INFO _aDialogElev[] = {
  { WINDOW_CreateIndirect, "",      0,                9,   8, 113, 140, WM_CF_SHOW },
  { BUTTON_CreateIndirect, "",      GUI_ID_BUTTON4,  16,  21,  16,  16, TEXT_CF_HCENTER},
  { BUTTON_CreateIndirect, "",      GUI_ID_BUTTON3,  16,  39,  16,  16, TEXT_CF_HCENTER},
  { BUTTON_CreateIndirect, "",      GUI_ID_BUTTON2,  16,  57,  16,  16, TEXT_CF_HCENTER},
  { BUTTON_CreateIndirect, "",      GUI_ID_BUTTON1,  16,  75,  16,  16, TEXT_CF_HCENTER},
  { BUTTON_CreateIndirect, "",      GUI_ID_BUTTON0,  16,  93,  16,  16, TEXT_CF_HCENTER},
  { BUTTON_CreateIndirect, "Door",  GUI_ID_BUTTON5,  42,  21,  53,  16, TEXT_CF_HCENTER},
  { BUTTON_CreateIndirect, "Pause", GUI_ID_BUTTON6,  42,  39,  53,  16, TEXT_CF_HCENTER}
};

/*********************************************************************
*
*       static data, polygons
*
**********************************************************************
*/
/*********************************************************************
*
*       Arrows
*/
static const GUI_POINT _aArrowUp[] = {
  {1, 0}, {4, 3}, { 1, 3}, {1, 8}, 
  {0, 8}, {0, 3}, {-3, 3}, {0, 0}
};

static const GUI_POINT _aArrowDown[] = {
  {1, 8}, {4, 5}, { 1, 5}, {1, 0},
  {0, 0}, {0, 5}, {-3, 5}, {0, 8}
};

static GUI_POINT _aArrowRight[] = {
  {0, 0}, {5, 0}, { 5,-3}, {8, 0},
  {8, 1}, {5, 4}, { 5, 1}, {0, 1}
};

static GUI_POINT _aArrowLeft[] = {
  {0, 0}, {3,-3}, { 3, 0}, {8, 0},
  {8, 1}, {3, 1}, { 3, 4}, {0, 1}
};

/*********************************************************************
*
*       Roof
*/
static GUI_POINT _aRoof[] = {
  {0, 0}, {75, 60}, {-75, 60}
};

static GUI_POINT _aRoofMini[] = {
  {0, 0}, {119, 90}, {-119, 90}
};

/*********************************************************************
*
*       static data, bitmaps
*
**********************************************************************
*/
/*********************************************************************
*
*       NEC_Logo
*/
static const GUI_COLOR _ColorsNEC_Logo[] = {
     0x000000,0x960000,0xA10000,0x9B0000
    ,0xA90000,0xB00000,0xB80000,0xBD0000
    ,0xCC2323,0xC21919,0xB50000,0xAC0000
    ,0xC92020,0xBA0000,0xC70000,0xA40000
};

static const GUI_LOGPALETTE _PalNEC_Logo = {
  16,	/* number of entries */
  1, 	/* No transparency */
  &_ColorsNEC_Logo[0]
};

static const unsigned char _acNEC_Logo[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x22, 0x22, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x21, 0x00, 0x32, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x01, 0x24, 0x56, 0x77, 0x88, 0x88, 0x97, 0x76, 0xAB, 0x30,
  0x02, 0xCC, 0xCC, 0xCC, 0xC8, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xC7, 0x00, 0x00, 0x00, 0x2A, 0x9C, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x50,
  0x02, 0xCC, 0xCC, 0xCC, 0xCC, 0xCD, 0x10, 0x00, 0x00, 0x00, 0x00, 0x08, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xC7, 0x00, 0x00, 0x27, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xE8, 0x8E, 0xCC, 0xCC, 0x50,
  0x02, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x08, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0x87, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x7A, 0x00, 0x0F, 0xCC, 0xCC, 0xCC, 0xCC, 0xCE, 0xA4, 0x30, 0x00, 0x00, 0x03, 0x24, 0x20,
  0x02, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x08, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0xCC, 0xCC, 0xCC, 0xCC, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x50, 0x00, 0x00, 0x00, 0x08, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0xC5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCB, 0x00, 0x00, 0x00, 0x08, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xCC, 0xCC, 0xCC, 0xCC, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0xCC, 0xC6, 0x6C, 0xCC, 0xCC, 0xCC, 0xCC, 0xF0, 0x00, 0x00, 0x08, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xCC, 0xCC, 0xCC, 0xCC, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0xCC, 0xCA, 0x17, 0xCC, 0xCC, 0xCC, 0xCC, 0xC2, 0x00, 0x00, 0x08, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0x74, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x30, 0x06, 0xCC, 0xCC, 0xCC, 0xCC, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0xCC, 0xCA, 0x01, 0x9C, 0xCC, 0xCC, 0xCC, 0xCE, 0x30, 0x00, 0x08, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x40, 0x07, 0xCC, 0xCC, 0xCC, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0xCC, 0xCA, 0x00, 0xF8, 0xCC, 0xCC, 0xCC, 0xCC, 0x83, 0x00, 0x08, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x40, 0x08, 0xCC, 0xCC, 0xCC, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0xCC, 0xCA, 0x00, 0x03, 0xEC, 0xCC, 0xCC, 0xCC, 0xC9, 0xF0, 0x08, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0x95, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x30, 0x09, 0xCC, 0xCC, 0xCC, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0xCC, 0xCA, 0x00, 0x00, 0x2C, 0xCC, 0xCC, 0xCC, 0xCC, 0x71, 0x08, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xCC, 0xCC, 0xCC, 0xCC, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0xCC, 0xCA, 0x00, 0x00, 0x0F, 0xCC, 0xCC, 0xCC, 0xCC, 0xCD, 0x08, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0xCC, 0xCC, 0xCC, 0xCC, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0xCC, 0xCA, 0x00, 0x00, 0x00, 0xBC, 0xCC, 0xCC, 0xCC, 0xCC, 0x68, 0xCC, 0xC3, 0x00, 0x7C, 0xCC, 0xCC, 0xCC, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xCC, 0xCC, 0xCC, 0xCC, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0xCC, 0xCA, 0x00, 0x00, 0x00, 0x05, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xC3, 0x00, 0xDC, 0xCC, 0xCC, 0xCC, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xEC, 0xCC, 0xCC, 0xCC, 0xC5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0xCC, 0xCA, 0x00, 0x00, 0x00, 0x00, 0xAC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xC3, 0x00, 0xAC, 0xCC, 0xCC, 0xCC, 0xC2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBC, 0xCC, 0xCC, 0xCC, 0xCC, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0xCC, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xC3, 0x00, 0x4C, 0xCC, 0xCC, 0xCC, 0xCC, 0x65, 0xB4, 0x44, 0x44, 0x44, 0x44, 0x4B, 0x00, 0x07, 0xCC, 0xCC, 0xCC, 0xCC, 0xC8, 0x52, 0x10, 0x00, 0x00, 0x03, 0x24, 0x40,
  0x02, 0xCC, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7C, 0xCC, 0xCC, 0xCC, 0xCC, 0xC3, 0x00, 0x19, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x00, 0x01, 0xAC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCE, 0x88, 0x8E, 0xCC, 0xCC, 0x70,
  0x02, 0xCC, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0xCC, 0xCC, 0xCC, 0xCC, 0xC3, 0x00, 0x03, 0x7C, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x00, 0x00, 0x03, 0xAE, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x70,
  0x03, 0xAA, 0xA4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0xAA, 0xAA, 0xAA, 0xA1, 0x00, 0x00, 0x02, 0xB6, 0x77, 0x79, 0x88, 0x88, 0x88, 0x88, 0x77, 0x77, 0x6A, 0x00, 0x00, 0x00, 0x01, 0xF5, 0x78, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xC8, 0xA0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x32, 0x22, 0x22, 0x22, 0x33, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const GUI_BITMAP _NEC_Logo = {
 82, /* XSize */
 26, /* YSize */
 41, /* BytesPerLine */
  4, /* BitsPerPixel */
 _acNEC_Logo,   /* Pointer to picture data (indices) */
 &_PalNEC_Logo  /* Pointer to palette */
};

/*********************************************************************
*
*       TouchCursor
*/
static const GUI_COLOR _ColorsTouchCursor[] = {
     0x0000FF,0x000000,0xFFFFFF
};

static const GUI_LOGPALETTE _PalTouchCursor = {
  3,	/* number of entries */
  1, 	/* Has transparency */
  &_ColorsTouchCursor[0]
};

static const unsigned char _acTouchCursor[] = {
  0x00, 0x00, 0x00, 0x01, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x05, 0x94, 0x00, 0x00, 0x00, 0x00, 0x55, 0x55, 0x55, 0x56, 0xA5, 0x55, 0x55, 0x55, 0x40,
  0x6A, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x40, 0x55, 0x55, 0x55, 0x56, 0xA5, 0x55, 0x55, 0x55, 0x40,
  0x00, 0x00, 0x00, 0x05, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x50, 0x00, 0x00, 0x00, 0x00
};

static const GUI_BITMAP _bmTouchCursor = {
 33, /* XSize */
 17, /* YSize */
 9, /* BytesPerLine */
 2, /* BitsPerPixel */
  _acTouchCursor,  /* Pointer to picture data (indices) */
 &_PalTouchCursor  /* Pointer to palette */
};

static const GUI_CURSOR _TouchCursor = {
  &_bmTouchCursor, 15, 7
};

/*********************************************************************
*
*       static code, serial interface
*       (defined for target hardware only)
*
**********************************************************************
*/
#ifndef WIN32
  /*********************************************************************
  *
  *       _cbReceiveData
  */
  static void _cbReceiveData(OS_U8 Data) {
    *(_RxBuffer.pWrite)++ = Data;
    if (_RxBuffer.pWrite == _RxBuffer.pDataEnd) {
      _RxBuffer.pWrite -= _RxBuffer.Size;
    }
  }

  /*********************************************************************
  *
  *       _SendString
  */
  static void _SendString(const char* pStr) {
    OS_SendString(pStr);
  }

  /*********************************************************************
  *
  *       _ConvIntToStr
  */
  static char* _ConvIntToStr(char* pStr, int Value) {
    char* Ptr = pStr + 4;
    int v = Value;
    *Ptr = 0;
    do {
      *(--Ptr) = (v % 10) + '0';
      v /= 10;
    } while (v && (Ptr != pStr));
    strcpy(pStr, Ptr);
    return pStr;
  }

  /*********************************************************************
  *
  *       _ConvStrToInt
  */
  static int _ConvStrToInt(char* pStr) {
    char* Ptr = pStr;
    int r = 0;
    while (*Ptr) {
      r *= 10;
      r += *(Ptr++) - '0';
    }
    return r;
  }

  /*********************************************************************
  *
  *       _ReceivedString
  */
  static void _ReceivedString(const char* pStr) {
    int v1 = -1, v2 = -1;
    char* Ptr;
    Ptr = strrchr(pStr, ' ');
    if (Ptr != NULL) {
      v1 = _ConvStrToInt(Ptr + 1);
      *Ptr = 0;
    }
    Ptr = strrchr(pStr, ' ');
    if (Ptr != NULL) {
      v2 = v1;
      v1 = _ConvStrToInt(Ptr + 1);
      *Ptr = 0;
    }
    if (_pfcbReceiveCommand) {
      (*_pfcbReceiveCommand)(pStr, v1, v2);
    }
  }

  /*********************************************************************
  *
  *       _ReceivedChar
  */
  static void _ReceivedChar(char c) {
    if (c == EOL) {
      _pString = _acString;
      _ReceivedString(_acString);
    } else {
      if (_pString < (_acString + STRING_SIZE)) {
        if (c >= 'a' && c <= 'z') {
          c -= 'a' - 'A';
        }
        *_pString++     = c;
        *(_pString + 1) = 0;
      }
    }
  }
#endif  /* #ifndef WIN32 */

/*********************************************************************
*
*       static code, serial interface
*
**********************************************************************
*/
/*********************************************************************
*
*       _SerialSendCommand
*/
static void _SerialSendCommand(const char* pStr, int v1, int v2) {
  #ifndef WIN32
    char Str1[STRING_SIZE + 2];
    char Str2[5];
    int Len, i, v;
    Str1[STRING_SIZE] = 0;
    strncpy(Str1, pStr, STRING_SIZE);
    for (i = 0; i < 2; i++) {
      v = (i == 0) ? v1 : v2;
      if (v >= 0 && v <= 999) {
        _ConvIntToStr(Str2, v);
        if ((strlen(Str1) + strlen(Str2) + 1) <= STRING_SIZE) {
          strcat(Str1, " ");
          strcat(Str1, Str2);
        }
      }
    }
    Len = strlen(Str1);
    Str1[Len]   = EOL;
    Str1[Len+1] = 0;
    _SendString(Str1);
  #endif
}

/*********************************************************************
*
*       _SerialExec
*/
static void _SerialExec(void) {
  #ifndef WIN32
    OS_U8 Data;
    while (_RxBuffer.pRead != _RxBuffer.pWrite) {
      Data = *(_RxBuffer.pRead)++;
      if (_RxBuffer.pRead == _RxBuffer.pDataEnd) {
        _RxBuffer.pRead -= _RxBuffer.Size;
      }
      _ReceivedChar((char)Data);
    }
  #endif
}

/*********************************************************************
*
*       _SerialInit
*/
static void _SerialInit(SERIAL_Callback* cb) {
  #ifndef WIN32
    OS_SetRxCallback(&_cbReceiveData);
    _pfcbReceiveCommand = cb;
  #endif
}

/*********************************************************************
*
*       static code, helper functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _SetSliderValue
*/
static void _SetSliderValue(WM_HWIN hWin, int Id, int Min, int Max, int Value) {
  WM_HWIN hItem;
  hItem = WM_GetDialogItem(hWin, Id);
  SLIDER_SetRange(hItem, Min, Max);
  SLIDER_SetValue(hItem, Value);
}

/*********************************************************************
*
*       _GetSliderValue
*/
static int _GetSliderValue(WM_HWIN hDlg, int Id) {
  return SLIDER_GetValue(WM_GetDialogItem(hDlg, Id));
}

/*********************************************************************
*
*       _AddDialog
*/
static WM_HWIN _AddDialog(const char* pText, const GUI_WIDGET_CREATE_INFO* pDialog, int NumItems,
                          WM_CALLBACK* cb, WM_HWIN hMultiPage) {
  WM_HWIN hWin;
  hWin = GUI_CreateDialogBox(pDialog, NumItems, cb, WM_GetClientWindow(hMultiPage), 0, 0);
  MULTIPAGE_AddPage(hMultiPage, 0, pText);
  return hWin;
}

/*********************************************************************
*
*       _SetDialogLight
*/
static void _SetDialogLight(void) {
  if (_hDialogLight) {
    _InitDialog = 1;
    _SetSliderValue(_hDialogLight, GUI_ID_SLIDER0, 0, 100, _Level[0].Light.ActV);
    _SetSliderValue(_hDialogLight, GUI_ID_SLIDER1, 0, 100, _Level[1].Light.ActV);
    _SetSliderValue(_hDialogLight, GUI_ID_SLIDER2, 0, 100, _Level[2].Light.ActV);
    _SetSliderValue(_hDialogLight, GUI_ID_SLIDER3, 0, 100, _Level[3].Light.ActV);
    _SetSliderValue(_hDialogLight, GUI_ID_SLIDER4, 0, 100, _Level[4].Light.ActV);
    _InitDialog = 0;
  }
}

/*********************************************************************
*
*       _InvalidateObject
*/
static void _InvalidateObject(WM_HWIN hWin, GUI_RECT r) {
  r.y0 -= _Scroll.ActV;
  r.y1 -= _Scroll.ActV;
  WM_InvalidateRect(hWin, &r);
}

/*********************************************************************
*
*       _InvalidateObject2
*/
static void _InvalidateObject2(WM_HWIN hWin, GUI_RECT r) {
  WM_InvalidateRect(hWin, &r);
}

/*********************************************************************
*
*       _InvalidateRect
*/
static void _InvalidateRect(WM_HWIN hWin, GUI_RECT r, int xOff, int yOff) {
  r.x0 += xOff;
  r.x1 += xOff;
  r.y0 += yOff;
  r.y1 += yOff;
  WM_InvalidateRect(hWin, &r);
}

/*********************************************************************
*
*       _AlertOn
*/
static void _AlertOn(int Index) {
  if (_hAlert[Index] == 0) {
    BUTTON_Handle hBut;
    WM_HWIN hClient;
    int Off = Index * 10;
    _hAlert[Index] = FRAMEWIN_Create(_acAlertText[Index], 0, WM_CF_SHOW, 100 + Off, 85 + Off, 110, 60);
    FRAMEWIN_SetMoveable(_hAlert[Index], 1);
    FRAMEWIN_SetActive(_hAlert[Index], 1);
    FRAMEWIN_SetBarColor(_hAlert[Index], 0, Index ? GUI_BLUE : GUI_RED);
    hClient = WM_GetClientWindow(_hAlert[Index]);
    WM_SetCallback(hClient, &_cbWinAlert);
    hBut = BUTTON_CreateAsChild(20, 10, 65, 20, hClient, 1, WM_CF_SHOW);
    BUTTON_SetText(hBut, "OK");
    _AlertCnt[Index] = 250;
  }
}

/*********************************************************************
*
*       _AlertOff
*/
static void _AlertOff(int Index) {
  if (_hAlert[Index]) {
    WM_DeleteWindow(_hAlert[Index]);
    _hAlert[Index]   = 0;
    _AlertCnt[Index] = 0;
  }
}

/*********************************************************************
*
*       _SlideValue
*/
static int _SlideValue(OBJECT* pObj, int Step) {
  int DiffY = pObj->NewV - pObj->ActV;
  if (DiffY != 0) {
    if (DiffY < 0) {
      pObj->ActV -= Step;
      DiffY = -DiffY;
    } else {
      pObj->ActV += Step;
    }
    if ((DiffY - Step) < 0) {
      pObj->ActV = pObj->NewV;
    }
    return 1;
  }
  return 0;
}

/*********************************************************************
*
*       _SlideStatus
*/
static void _SlideStatus() {
  int Step = ((GUI_GetTime() - _SlidePrevTime) * 5) >> 7;
  if (Step != 0) {
    _SlidePrevTime = GUI_GetTime();
    if (_SlideValue(&_Garage, Step << 1)) {
      _InvalidateObject(_hWinHouse, _Garage.Rect);
      _InvalidateObject2(_hWinMap, _GarageSmall.Rect);
    }
    if (_SlideValue(&_Jalousie1, Step)) {
      _InvalidateObject(_hWinHouse, _Jalousie1.Rect);
      _InvalidateObject2(_hWinMap, _Jalousie1Small.Rect);
    }
    if (_SlideValue(&_Jalousie2, Step)) {
      _InvalidateObject(_hWinHouse, _Jalousie2.Rect);
      _InvalidateObject2(_hWinMap, _Jalousie2Small.Rect);
    }
    if (_SlideValue(&_Marquee1, Step)) {
      _InvalidateObject(_hWinHouse, _Marquee1.Rect);
      _InvalidateObject2(_hWinMap, _Marquee1Small.Rect);
    }
    if (_SlideValue(&_Marquee2, Step)) {
      _InvalidateObject(_hWinHouse, _Marquee2.Rect);
      _InvalidateObject2(_hWinMap, _Marquee2Small.Rect);
    }
    if (_SlideValue(&_Elevator.Itself, Step)) {
      _InvalidateObject(_hWinHouse, _Elevator.Itself.Rect);
      _InvalidateObject2(_hWinMap, _ElevatorSmall.Rect);
    }
    if (_SlideValue(&_Elevator.Door, Step << 1)) {
      _InvalidateRect(_hWinHouse, _Elevator.Door.Rect, 0, _Elevator.Itself.ActV - _Scroll.ActV);
    }
    if (_AlertCnt[0]) {
      _AlertCnt[0] -= Step;
      if (_AlertCnt[0] <= 0) _AlertOff(0);
    }
    if (_AlertCnt[1]) {
      _AlertCnt[1] -= Step;
      if (_AlertCnt[1] <= 0) _AlertOff(1);
    }
  }
  Step = GUI_GetTime() - _ScrollPrevTime;
  if (Step != 0) {
    _ScrollPrevTime = GUI_GetTime();
    if (_SlideValue(&_Scroll, Step << 1)) {
      SCROLLBAR_SetValue(_hScroll, _Scroll.ActV);
      _InvalidateObject(_hWinHouse, _Scroll.Rect);
    }
  }
}

/*********************************************************************
*
*       _Clip
*/
static int _Clip(int Value) {
  Value = (Value < 100) ? Value : 100;
  Value = (Value >   0) ? Value :   0;
  return Value;
}

/*********************************************************************
*
*       static code, drawing functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawRect
*/
static void _DrawRect(int x0, int y0, int x1, int y1, int PenSize) {
  GUI_SetPenSize(PenSize);
  GUI_DrawRect(x0, y0, x1, y1 + PenSize - 1);
}

/*********************************************************************
*
*       _DrawElevator2
*/
static void _DrawElevator2(int x,  int y,  int w,  int h,
                           int x0, int y0, int x1, int y1,
                           int Index, GUI_COLOR Color) {
  if (y0 <= y1 && x0 <= x1) {
    GUI_RECT ClipRect;
    const GUI_RECT* OldClipRect;
    int Door = (w - 2) * (100 - _Elevator.Door.ActV) / 100;
    ClipRect.x0 = x + x0;
    ClipRect.y0 = y + y0;
    ClipRect.x1 = x + x1;
    ClipRect.y1 = y + y1;
    OldClipRect = WM_SetUserClipRect(&ClipRect);
    /* Draw elevator car */
    GUI_SetColor(LCD_MixColors256(Color, GUI_GRAY, Index ? 150 : 0));
    GUI_FillRect(x, y, x + w, y + h);
    /* Draw door frame (inside) */
    GUI_SetColor(LCD_MixColors256(Color, GUI_WHITE, Index ? 150 : 0));
    _DrawRect(x, y, x + w, y + h, 1);
    /* Draw elevator door (inside) */
    GUI_SetColor(LCD_MixColors256(Color, GUI_LIGHTGRAY, Index ? 150 : 0));
    GUI_FillRect(x + 1, y + 1, x + 1 + Door, y + h - 1);
    WM_SetUserClipRect(OldClipRect);
  }
}

/*********************************************************************
*
*       _DrawElevator
*/
static void _DrawElevator(int x, int y, int w, int h, int Level) {
  GUI_COLOR Color1, Color2;
  int yPos, yStart, yEnd, y0, y1;
  int Light = _Level[Level].Light.ActV;
  /* Draw elevator shaft */
  Color1  = (0x8F * Light / 100 + 0x60) << 16;
  Color1 += (0x7F * Light / 100 + 0x0) << 8;
  Color1 += (0x6F * Light / 100 + 0x20);
  GUI_SetColor(Color1);
  GUI_FillRect(x, y, x + w, y + h);
  /* Draw elevator door (outside) */
  Color2 = 0x5F * Light / 100 + 0xA0;
  Color2 = (Color2 << 16 | Color2 << 8 | Color2);
  GUI_SetColor(Color2);
  GUI_FillRect(x + 2, y + 80, x + w - 2, y + h - 2);
  /* Draw elevator car */
  yPos   = _Elevator.Itself.ActV - (5 - Level) * 130 + 80;
  yStart = (yPos < 0) ? -yPos : 0;
  yEnd   = (yPos > 82) ? 125 - yPos : 43;
  if (yPos != 80) {
    y0 = (yPos > 80) ? yStart + 44 - (yPos - 80) : yStart;
    y1 = (yPos > 80) ? yEnd : 79 - yPos;
    _DrawElevator2(x + 2, y + yPos, w - 4, 43, 0, y0, w - 4, y1, 1, Color1);
  }
  y0 = (yPos < 80) ? yStart + (80 - yPos) : yStart;
  y1 = (yPos > 80) ? 43 - (yPos - 80) : 43;
  if (_Elevator.Move) {
    GUI_SetColor(Color2);
    GUI_FillRect(x + 2, y + 80, x + w - 2, y + h - 2);
    _DrawElevator2(x + 2, y + yPos, w - 4, 43, 0, y0, w - 4, y1, 1, Color2);
  } else {
    int Door = (w - 4) * (100 - _Elevator.Door.ActV) / 100;
    _DrawElevator2(x + 2, y + yPos, w - 4, 43, 0, y0, Door, y1, 1, Color2);
    _DrawElevator2(x + 2, y + yPos, w - 4, 43, Door + 1, y0, w - 4, y1, 0, Color2);
  }
  /* Draw door frame (outside) */
  Color2 = 0x7F * Light / 100 + 0x50;
  GUI_SetColor(Color2 << 16);
  _DrawRect(x + 1, y + 79, x + w - 1, y + h - 1, 1);
  /* Draw level number */
  if (_Elevator.Itself.ActV == _Elevator.Itself.NewV &&
      _Elevator.Itself.ActV == ((5 - Level) * 130)) {
    GUI_SetColor(0x00FF40);
  } else {
    Color2 = 0x3F * Light / 100 + 0xC0;
    GUI_SetColor(Color2 << 8 | Color2);
  }
  GUI_SetFont(&GUI_Font8x8);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_DispCharAt(Level + 1 + '0', x + (w / 2) - 3, y + 70);
}

/*********************************************************************
*
*       _DrawWindow
*/
static void _DrawWindow(int x, int y, int w, int h, int dy, int Light) {
  GUI_COLOR Color;
  int i;
  Color = 0x80 * Light / 100 + 0x7F;
  GUI_SetColor(Color << 16);
  GUI_FillRect(x, y, x + w, y + h);
  Color = 0x60 * Light / 100 + 0x9F;
  GUI_SetColor(Color << 16 | Color << 8 | Color);
  GUI_DrawVLine(x, y, y + h);
  GUI_DrawVLine(x + w / 2, y, y + h);
  GUI_DrawVLine(x + w, y, y + h);
  for (i = 0; i < h; i += dy) {
    GUI_DrawHLine(y + i, x, x + w);
  }
  GUI_DrawHLine(y + h, x, x + w);
}

/*********************************************************************
*
*       _DrawFrame
*/
static void _DrawFrame(int x, int y, int w, int h, int Light) {
  GUI_COLOR Color;
  Color = 0x88 * Light / 100 + 0x48;
  GUI_SetColor(Color << 16 | Color << 8 | Color);
  GUI_FillRect(x, y, x + w - 1, y + h - 1);
  GUI_SetColor(GUI_WHITE);
  _DrawRect(x, y, x + w - 1, y + h - 1, 2);
  Color = 0xA0 * Light / 100 + 0x5F;
  GUI_SetColor(Color << 16 | Color << 8 | Color);
  GUI_SetPenSize(1);
  GUI_DrawLine(x + 2, y + 2, x + w - 2, y + h - 2);
  GUI_DrawLine(x + w - 2, y + 2, x + 2, y + h - 2);
}

/*********************************************************************
*
*       _DrawMarquee
*/
static void _DrawMarquee(int x, int y, int w, int h, int d, int Status) {
  GUI_RECT ClipRect;
  const GUI_RECT* OldClipRect;
  ClipRect.x0 = (d < 0) ? (x - w - 2) : (x + 1);
  ClipRect.y0 = y - 1;
  ClipRect.x1 = (d < 0) ? (x - 1) : (x + w + 2);
  ClipRect.y1 = y + 61;
  OldClipRect = WM_SetUserClipRect(&ClipRect);
  GUI_AA_SetFactor(4);
  GUI_AA_EnableHiRes();
  x <<= 2;
  y <<= 2;
  w = (w - 2) * (100 - Status) / 25 + 12;
  w = (d > 0) ? w : -w;
  h = h * (100 - Status) / 25 + 4;
  GUI_SetPenSize(3);
  GUI_SetPenShape(GUI_PS_ROUND);
  GUI_SetColor(0xA08080);
  GUI_AA_DrawLine(x + (60 * d), y + 240, x, y + 240); 
  GUI_SetPenShape(GUI_PS_FLAT);
  GUI_SetColor(0x00C0FF);
  GUI_AA_DrawLine(x + w, y + h, x, y);
  GUI_AA_DrawLine(x + w - (3 * d), y + h, x + w - (3 * d), y + h + 20);
  GUI_AA_DisableHiRes();
  WM_SetUserClipRect(OldClipRect);
}

/*********************************************************************
*
*       _DrawJalousie
*/
static void _DrawJalousie(int x, int y, int h, int Status) {
  GUI_SetColor(0x0C0FF);
  GUI_SetPenSize(3);
  GUI_SetPenShape(GUI_PS_ROUND);
  GUI_DrawLine(x, y, x, y + (h * Status / 100) + 2);
}

/*********************************************************************
*
*       _DrawRoof
*/
static void _DrawRoof(int x, int y) {
  GUI_SetBkColor(GUI_BLACK);
  GUI_ClearRect(35, y - 70, 164, y + 59);
  GUI_SetColor(0xD82000);
  GUI_AA_SetFactor(3);
  GUI_AA_FillPolygon(_aRoof, 3, x, y);
  GUI_SetColor(0x0066FF);
  if (_LogoRPM < 0) {
    GUI_FillPolygon(_aArrowLeft,  8, x - 4, y + 9);
  }
  if (_LogoRPM > 0) {
    GUI_FillPolygon(_aArrowRight, 8, x - 4, y + 9);
  }
  GUI_DrawBitmapEx(&_NEC_Logo, x - 1, y - 13, 40, 12, _LogoMulX, 1000);
}

/*********************************************************************
*
*       _DrawDoor
*/
static void _DrawDoor(int x, int y, int w, int h) {
  GUI_SetColor(GUI_BLUE);
  GUI_FillRect(x, y, x + w, y + h);
  GUI_SetColor(GUI_BLACK);
  _DrawRect(x, y, x + w, y + h, 1);
  GUI_DrawHLine(y + h/2, x + 4, x + 8);
  GUI_DrawVLine(x + 4, y + h/2 - 1, y + h/2 + 3);
}

/*********************************************************************
*
*       _DrawGarage
*/
static void _DrawGarage(int x, int y, int w, int h, int Status) {
  GUI_SetColor(GUI_YELLOW);
  GUI_FillRect(x, y + 1, x + w, y + ((h - 2) * (100 - Status) / 100) + 1);
  GUI_SetColor(GUI_BLACK);
  _DrawRect(x, y, x + w, y + h, 1);
}

/*********************************************************************
*
*       _DrawSmallLevel
*/
static void _DrawSmallLevel(int Level, int x0, int y0, int Light) {
  GUI_COLOR Color;
  int i;
  y0 += (4 - Level) * 39;
  /* Draw frame of levels (background) */
  Color = 0x78 * Light / 100 + 0x58;
  GUI_SetColor(Color << 16 | Color << 8 | Color);
  GUI_FillRect(x0 + 9, y0 + 40, x0 + 46, y0 + 78);
  /* Draw frame of levels (rear bracing)*/
  Color = 0xA0 * Light / 100 + 0x5F;
  GUI_SetColor(Color << 16 | Color << 8 | Color);
  GUI_DrawLine(x0 + 9, y0 +  40, x0 + 46, y0 +  77);
  GUI_DrawLine(x0 + 9, y0 +  77, x0 + 46, y0 +  40);
  /* Draw windows */
  Color = 0x80 * Light / 100 + 0x7F;
  GUI_SetColor(Color << 16);
  GUI_FillRect(x0 + 32, y0 +  42, x0 + 40, y0 +  75);
  Color = 0x60 * Light / 100 + 0x9F;
  GUI_SetColor(Color << 16 | Color << 8 | Color);
  GUI_DrawVLine(x0 + 31, y0 + 41, y0 + 76);
  GUI_DrawVLine(x0 + 36, y0 + 41, y0 + 76);
  GUI_DrawVLine(x0 + 41, y0 + 41, y0 + 76);
  for (i = 0; i < ((Level) ? 8 : 5); i++) {
    GUI_DrawHLine(y0 + (i * 5) + 41, x0 + 31, x0 + 40);
  }
  /* Draw elevator shaft*/
  Color  = (0x8F * Light / 100 + 0x60) << 16;
  Color += (0x7F * Light / 100 + 0x0) << 8;
  Color += (0x6F * Light / 100 + 0x20);
  GUI_SetColor(Color);
  GUI_FillRect(x0 + 14, y0 +  40, x0 + 23, y0 +  77);
  Color = 0x5F * Light / 100 + 0xA0;
  GUI_SetColor(Color << 16 | Color << 8 | Color);
  GUI_FillRect(x0 + 15, y0 +  64, x0 + 22, y0 +  76);
}

/*********************************************************************
*
*       _DrawSmallElevatorDoor
*/
static void _DrawSmallElevatorDoor(int Level, int x0, int y0, int Light) {
  GUI_COLOR Color;
  y0 += (4 - Level) * 39;
  Color = 0x7F * Light / 100 + 0x50;
  GUI_SetColor(Color << 16);
  _DrawRect(x0 + 14, y0 + 63, x0 + 23, y0 +  77, 1);

  if (_Elevator.Itself.ActV == _Elevator.Itself.NewV &&
      _Elevator.Itself.ActV == ((5 - Level) * 130)) {
    GUI_SetColor(0x00FF60);
    //GUI_SetColor(0x00FF40);
  } else {
    Color = 0x2F * Light / 100 + 0xD0;
    GUI_SetColor(Color << 8 | Color);
  }
  GUI_DrawHLine(y0 + 61, x0 + 18, x0 + 19);
}

/*********************************************************************
*
*       _DrawRotateLogo
*/
static int _DrawRotateLogo(void) {
  if (_LogoRPM != 0) {
    if ((GUI_GetTime() - _LogoPrevTime) >= _LogoWaitTime) {
      _LogoDivisor  = 60000 / _LogoRPM / PI2;
      _LogoAngle   += (GUI_GetTime() - _LogoPrevTime) / _LogoDivisor;
      _LogoPrevTime = GUI_GetTime();
      _LogoMulX     = cos(_LogoAngle) * 1000;
      if (_LogoMulX != _LogoPrevMulX) {
        _LogoPrevMulX = _LogoMulX;
        return 1;
      }
    }
  }
  return 0;
}

/*********************************************************************
*
*       _DrawLevel
*/
static void _DrawLevel(int n, int y) {
  if (n != 5) {
    _DrawFrame(35, y, 129, 129, _Level[n].Light.ActV);
    _DrawElevator(55, y + 2, 30, 125, n);
    if (n != 0) {
      _DrawWindow(115, y + 5, 30, 119, 17, _Level[n].Light.ActV);
    }
  }
  switch (n) {
  case 0:
    _DrawWindow(115, y + 5, 30, 76, 17, _Level[0].Light.ActV);
    _DrawDoor(115, y + 82, 30, 45);
    _DrawGarage(40, y + 82, 50, 45, _Garage.ActV);
    break;
  case 1:
    _DrawMarquee(164, y + 30, 30, 10, 1, _Marquee1.ActV);
    break;
  case 2:
    _DrawJalousie(166, y + 10, 90, _Jalousie1.ActV);
    break;
  case 3:
    _DrawMarquee(35, y + 30, 30, 10, -1, _Marquee2.ActV);
    break;
  case 4:
    _DrawJalousie(33, y + 10, 90, _Jalousie2.ActV);
    break;
  case 5:
    _DrawRoof(99, y + 70);
  }
}

/*********************************************************************
*
*       _DrawHouseMap
*/
static void _DrawHouseMap(int x0, int y0) {
  int i, ElevatorY, Status;
  /* Draw roof of house */
  GUI_AA_SetFactor(5);
  GUI_AA_EnableHiRes();
  GUI_SetColor(0xD82000);
  GUI_AA_FillPolygon(_aRoofMini, 3, (x0 * 5) + 138, (y0 * 5) + 105);
  GUI_AA_DisableHiRes();
  GUI_DrawBitmapEx(&_NEC_Logo, x0 + 27, y0 + 13, 40, 12, _LogoMulX >> 1, 500);
  /* Draw levels*/
  for (i = 0; i < 5; i++) {
    _DrawSmallLevel(i, x0, y0, _Level[i].Light.ActV);
  }
  /* Draw elevator car */
  GUI_SetColor(0xD0D0D0);
  ElevatorY = y0 + (_Elevator.Itself.ActV / (10. / 3.)) + 25;
  GUI_FillRect(x0 + 15, ElevatorY, x0 + 22, ElevatorY + 12);
  /* Draw elevator doors */
  for (i = 0; i < 5; i++) {
    _DrawSmallElevatorDoor(i, x0, y0, _Level[i].Light.ActV);
  }
  /* Draw door */
  GUI_SetColor(GUI_BLUE);
  GUI_FillRect(x0 + 32, y0 + 220, x0 + 40, y0 + 232);
  GUI_SetColor(GUI_BLACK);
  _DrawRect(x0 + 31, y0 + 219, x0 + 41, y0 + 233, 1);
  GUI_SetColor(0x707070);
  GUI_DrawHLine(y0 + 219, x0 + 31, x0 + 41);
  /* Draw Garage */
  Status = ((100 - _Garage.ActV) * 12 / 100);
  GUI_SetColor(GUI_YELLOW);
  GUI_FillRect(x0 + 10, y0 + 220, x0 + 24, y0 + 220 + Status);
  GUI_SetColor(GUI_BLACK);
  _DrawRect(x0 + 9, y0 + 219, x0 + 25, y0 + 233, 1);
  /* Draw Jalousie 1 */
  Status = (_Jalousie1.ActV * 23 / 100);
  GUI_SetColor(0x00C0FF);
  GUI_DrawVLine(x0 + 48, y0 + 120, y0 + 124 + Status);
  GUI_SetColor(0x006C90);
  GUI_DrawVLine(x0 + 49, y0 + 120, y0 + 124 + Status);
  /* Draw Jalousie 2 */
  Status = (_Jalousie2.ActV * 23 / 100);
  GUI_SetColor(0x00C0FF);
  GUI_DrawVLine(x0 + 7, y0 + 42, y0 + 46 + Status);
  GUI_SetColor(0x006C90);
  GUI_DrawVLine(x0 + 6, y0 + 42, y0 + 46 + Status);
  /* Draw Marquee 1*/
  GUI_AA_SetFactor(5);
  GUI_AA_EnableHiRes();
  GUI_SetPenSize(2);
  Status = ((100 - _Marquee1.ActV) * 28 / 100) + 5;
  GUI_SetColor(0x0C0FF);
  GUI_AA_DrawLine(240, 835, 240 + Status, 835 + Status/2.5);
  GUI_SetColor(0xA08080);
  GUI_DrawHLine(183, 47, 51);
  GUI_DrawHLine(184, 47, 51);
  /* Draw Marquee 2*/
  Status = ((100 - _Marquee2.ActV) * 28 / 100) + 5;
  GUI_SetColor(0x0C0FF);
  GUI_AA_DrawLine(40, 445, 40 - Status, 445 + Status/2.5);
  GUI_SetColor(0xA08080);
  GUI_DrawHLine(105, 4, 8);
  GUI_DrawHLine(106, 4, 8);
  GUI_SetPenSize(1);
  GUI_AA_DisableHiRes();
  /* Draw frame of levels (front bracing)*/
  GUI_SetColor(0xFFFFFF);
  GUI_DrawVLine(x0 +  8, y0 + 39, y0 + 234);
  GUI_DrawVLine(x0 + 47, y0 + 39, y0 + 234);
  GUI_DrawHLine(y0 +  39, x0 + 9, x0 + 46);
  GUI_DrawHLine(y0 +  78, x0 + 9, x0 + 46);
  GUI_DrawHLine(y0 + 117, x0 + 9, x0 + 46);
  GUI_DrawHLine(y0 + 156, x0 + 9, x0 + 46);
  GUI_DrawHLine(y0 + 195, x0 + 9, x0 + 46);
  GUI_DrawHLine(y0 + 234, x0 + 9, x0 + 46);
}

/*********************************************************************
*
*       static code, elevator functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _ElevatorOpenDoor
*/
static void _ElevatorOpenDoor(void) {
  _Elevator.Door.NewV = 100;
  _Elevator.Time = GUI_GetTime() + 4000;
  _SerialSendCommand("LIFT_OPEN", -1, -1);
}

/*********************************************************************
*
*       _ElevatorCloseDoor
*/
static void _ElevatorCloseDoor(void) {
  _Elevator.Door.NewV = 0;
  _Elevator.Time = GUI_GetTime() + 2000;
  _SerialSendCommand("LIFT_CLOSE", -1, -1);
}

/*********************************************************************
*
*       _ElevatorMoveTo
*/
static void _ElevatorMoveTo(int Level) {
  if (Level < 5) {
    _Elevator.Itself.NewV = (5 - Level) * 130;
    _Elevator.Move = (_Elevator.Itself.ActV > _Elevator.Itself.NewV) ? 1 : -1;
    WM_InvalidateWindow(_Elevator.Handle);
    _SerialSendCommand("LIFT", Level, -1);
  }
}

/*********************************************************************
*
*       _ElevatorStop
*/
static void _ElevatorStop(void) {
  _Elevator.Move = 0;
  _Elevator.Itself.NewV = _Elevator.Itself.ActV;
  WM_InvalidateWindow(_Elevator.Handle);
}

/*********************************************************************
*
*       _ElevatorAddLevel
*/
static void _ElevatorAddLevel(int Level) {
  if (_Level[Level].Elevator == 0 && Level < 5) {
    _Level[Level].Elevator = 1;
    _Elevator.ToDo[_Elevator.NumToDo++] = Level;
    WM_InvalidateWindow(_Elevator.Handle);
  }
}

/*********************************************************************
*
*       _ElevatorDelLevel
*/
static void _ElevatorDelLevel(int Level) {
  int i;
  if (_Level[Level].Elevator != 0 && Level < 5) {
    _Level[Level].Elevator = 0;
    for (i = 0; i < _Elevator.NumToDo; i++) {
      if (_Elevator.ToDo[i] == Level) break;
    }
    for (; i < (_Elevator.NumToDo - 1); i++) {
      _Elevator.ToDo[i] = _Elevator.ToDo[i + 1];
    }
    _Elevator.NumToDo--;
  }
}

/*********************************************************************
*
*       _ElevatorGetLevel
*/
static void _ElevatorGetLevel(void) {
  _Elevator.Level = 5 - ((_Elevator.Itself.ActV + 65) / 130);
  if (_Elevator.Level != _Elevator.LastLevel) {
    WM_InvalidateWindow(_Elevator.Handle);
    _Elevator.LastLevel = _Elevator.Level;
  }
}

/*********************************************************************
*
*       _ElevatorOptimize
*/
static void _ElevatorOptimize(void) {
  int EndLevel = 5 - (_Elevator.Itself.NewV / 130);
  int Diff, i, Level;
  if (_Elevator.Itself.ActV < _Elevator.Itself.NewV) {
    Level = (5 - ((_Elevator.Itself.ActV + 130) / 130));
  } else {
    Level = (5 - ((_Elevator.Itself.ActV - 1) / 130));
  }
  Diff = (Level < EndLevel) ? 1 : -1;
  for (i = Level; i != EndLevel; i += Diff) {
    if (_Level[i].Elevator) {
      _ElevatorMoveTo(i);
      break;
    }
  }
}

/*********************************************************************
*
*       _ElevatorPause
*/
static void _ElevatorPause(void) {
  _Elevator.Pause = ~_Elevator.Pause;
  if (_Elevator.Pause) {
    _Elevator.Itself.NewV = _Elevator.Itself.ActV;
    _SerialSendCommand("LIFT_STOP", -1 , -1);
  } else {
    if (_Elevator.Door.ActV == 0) {
      if (_Elevator.NumToDo > 0) {
        _ElevatorMoveTo(_Elevator.ToDo[0]);
      }
    }
  }
  WM_InvalidateWindow(_Elevator.Handle);
}

/*********************************************************************
*
*       _ElevatorMove
*/
static void _ElevatorMove(int Level) {
  int yPos;
  if (_Level[Level].Elevator == 0) {
    yPos = (5 - Level) * 130;
    if (yPos != _Elevator.Itself.ActV || _Elevator.Itself.ActV != _Elevator.Itself.NewV) {
      _ElevatorAddLevel(Level);
    } else {
      _ElevatorOpenDoor();
    }
  }
}

/*********************************************************************
*
*       _ElevatorExec
*/
static void _ElevatorExec(void) {
  if (GUI_GetTime() < _Elevator.Time) return;
  if (_Elevator.Door.ActV == _Elevator.Door.NewV) {
    if (_Elevator.Door.ActV == 100) {
      _ElevatorCloseDoor();
    } else {
      if (!_Elevator.Pause) {
        if (_Elevator.Move) {
          if (_Elevator.Itself.ActV == _Elevator.Itself.NewV) {
            _ElevatorDelLevel(_Elevator.Level);
            _ElevatorStop();
            _ElevatorOpenDoor();
          } else {
            _ElevatorOptimize();
            _ElevatorGetLevel();
          }
        } else {
          if (_Elevator.NumToDo > 0) {
            _ElevatorMoveTo(_Elevator.ToDo[0]);
          } else {
            _Elevator.Time = GUI_GetTime() + 250;
          }
        }
      }
    }
  }
}

/*********************************************************************
*
*       static code, callbacks
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbReceiveCommand
*/
static void _cbReceiveCommand(const char* pStr, int v1, int v2) {
  if (_ExecuteCommands) {
    if (strcmp(pStr, "LIGHT") == 0) {
      if (v1 >= 0 && v1 <= 4) {
        _Level[v1].Light.ActV = _Clip(v2);
        _InvalidateObject(_hWinHouse, _Level[v1].Light.Rect);
        _InvalidateObject2(_hWinMap, _LightSmall[v1].Rect);
        _SetDialogLight();
      }
      return;
    }
    if (strcmp(pStr, "JALOUSIE") == 0) {
      if (v1) {
        _Jalousie1.NewV = _Clip(v2);
      } else {
        _Jalousie2.NewV = _Clip(v2);
      }
      return;
    }
    if (strcmp(pStr, "MARQUEE") == 0) {
      if (v1) {
        _Marquee1.NewV = _Clip(v2);
      } else {
        _Marquee2.NewV = _Clip(v2);
      }
      return;
    }
    if (strcmp(pStr, "GARAGE") == 0) {
      _Garage.NewV = _Clip(v1);
      return;
    }
    if (strcmp(pStr, "LOGO") == 0) {
      switch (v1) {
      case 0:
        _LogoRPM  = 0;
        _LogoMulX = 1000;
        _InvalidateObject(_hWinHouse, _Logo.Rect);
        _InvalidateObject2(_hWinMap, _LogoSmall.Rect);
        break;
      case 1:
        _LogoRPM = -RPM;
        break;
      case 2:
        _LogoRPM =  RPM;
      }
      _InvalidateObject(_hWinHouse, _LogoArrow.Rect);
      return;
    }
    if (strcmp(pStr, "LIFT") == 0) {
      _ElevatorMove(v1);
      return;
    }
    if (strcmp(pStr, "LIFT_OPEN") == 0) {
      _ElevatorOpenDoor();
      return;
    }
    if (strcmp(pStr, "LIFT_STOP") == 0) {
      _ElevatorPause();
      return;
    }
    if (strcmp(pStr, "SHOW") == 0) {
      if (v1 >= 0 && v1 <= 5) {
        _Scroll.NewV = 650 - v1 * 130;
        _ScrollPrevTime = GUI_GetTime();
      }
      return;
    }
    if (strcmp(pStr, "BURGLARY") == 0) {
      if (v1 & 0x1) {
        _AlertOn(0);
      }
      if (v1 & 0x2) {
        _AlertOn(1);
      }
      return;
    }
  }
}

/*********************************************************************
*
*       static code, window callbacks
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbBkWindow
*/
static void _cbBkWindow(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_BLACK);
    GUI_Clear();
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbWinControl
*/
static void _cbWinControl(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case WM_TOUCH:
    WM_BringToTop(WM_GetParent(pMsg->hWin));
    break;
  case WM_PAINT:
    GUI_SetBkColor(GUI_GRAY);
    GUI_Clear();
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbWinHouse
*/
static void _cbWinHouse(WM_MESSAGE* pMsg) {
  WM_SCROLL_STATE ScrollState;
  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    if (pMsg->Data.v == WM_NOTIFICATION_VALUE_CHANGED) {
      if (WM_GetId(pMsg->hWinSrc) == GUI_ID_VSCROLL) {
        WM_GetScrollState(pMsg->hWinSrc, &ScrollState);
        if (ScrollState.v != _Scroll.ActV) {
          _Scroll.NewV = ScrollState.v;
          _Scroll.ActV = _Scroll.NewV;
          _InvalidateObject(_hWinHouse, _Scroll.Rect);
          WM_BringToTop(WM_GetParent(pMsg->hWin));
        }
      }
    }
    break;
  case WM_TOUCH:
    WM_BringToTop(WM_GetParent(pMsg->hWin));
    break;
  case WM_PAINT:
    GUI_SetBkColor(GUI_BLACK);
    GUI_ClearRect(0, 0, 34, 129);
    GUI_ClearRect(165, 0, 199, 129);
    if (_Scroll.ActV < 130) {
      _DrawLevel(5,   0 - _Scroll.ActV);
    }
    if (_Scroll.ActV != 0 && _Scroll.ActV < 260) {
      _DrawLevel(4, 130 - _Scroll.ActV);
    }
    if (_Scroll.ActV > 130 && _Scroll.ActV < 390) {
      _DrawLevel(3, 260 - _Scroll.ActV);
    }
    if (_Scroll.ActV > 260 && _Scroll.ActV < 520) {
      _DrawLevel(2, 390 - _Scroll.ActV);
    }
    if (_Scroll.ActV > 390 && _Scroll.ActV < 650) {
      _DrawLevel(1, 520 - _Scroll.ActV);
    }
    if (_Scroll.ActV > 520) {
      _DrawLevel(0, 650 - _Scroll.ActV);
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbWinMap
*/
static void _cbWinMap(WM_MESSAGE* pMsg) {
  GUI_PID_STATE TouchState;
  switch (pMsg->MsgId) {
  case WM_TOUCH:
    GUI_TOUCH_GetState(&TouchState);
    if (TouchState.Pressed) {
      int x = TouchState.x - WM_GetWindowOrgX(pMsg->hWin);
      int y = TouchState.y - WM_GetWindowOrgY(pMsg->hWin);
      if (x >= 0 && x <= 50 && y >= 0 && y <= 233) {
        _Scroll.NewV = 650 - 130 * (5 - (y / 39));
        _ScrollPrevTime = GUI_GetTime();
      }
    }
    break;
  case WM_PAINT:
    GUI_SetBkColor(GUI_BLACK);
    GUI_Clear();
    _DrawHouseMap(0, 0);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbWinAlert
*/
static void _cbWinAlert(WM_MESSAGE* pMsg) {
  WM_HWIN hParent;
  int Index;
  hParent = WM_GetParent(pMsg->hWin);
  for (Index = 0; Index < 2; Index++) {
    if (hParent == _hAlert[Index]) break;
  }
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    break;
  case WM_NOTIFY_PARENT:
    if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
      _AlertOff(Index);
    }
  case WM_TOUCH:
    WM_BringToTop(_hAlert[Index]);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       static code, dialog callbacks
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbDialogLight
*/
static void _cbDialogLight(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    _hDialogLight = pMsg->hWin;
    _SetDialogLight();
    break;
  case WM_NOTIFY_PARENT:
    if (_InitDialog) break;
    if (pMsg->Data.v == WM_NOTIFICATION_VALUE_CHANGED) {
      int Id = WM_GetId(pMsg->hWinSrc);
      if (Id >= GUI_ID_SLIDER0 && Id <= GUI_ID_SLIDER4) {
        int i = Id - GUI_ID_SLIDER0;
        _Level[i].Light.ActV = _GetSliderValue(pMsg->hWin, Id);
        _InvalidateObject(_hWinHouse, _Level[i].Light.Rect);
        _InvalidateObject2(_hWinMap, _LightSmall[i].Rect);
        _SerialSendCommand("LIGHT", i, _Level[i].Light.ActV);
      }
    }
  case WM_TOUCH:
    WM_BringToTop(WM_GetParent(_hWinControl));
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbDialogMisc
*/
static void _cbDialogMisc(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    if (_InitDialog) break;
    if (pMsg->Data.v == WM_NOTIFICATION_CLICKED) {
      int Id = WM_GetId(pMsg->hWinSrc);
      if (Id >= GUI_ID_BUTTON0 && Id <= GUI_ID_BUTTON7) {
        switch (Id) {
        case GUI_ID_BUTTON0:
          _Jalousie2.NewV = 100 - _Jalousie2.NewV;
          _SerialSendCommand("JALOUSIE", 0, _Jalousie2.NewV);
          break;
        case GUI_ID_BUTTON1:
          _Jalousie1.NewV = 100 - _Jalousie1.NewV;
          _SerialSendCommand("JALOUSIE", 1, _Jalousie1.NewV);
          break;
        case GUI_ID_BUTTON2:
          _Marquee2.NewV = 100 - _Marquee2.NewV;
          _SerialSendCommand("MARQUEE", 0, _Marquee2.NewV);
          break;
        case GUI_ID_BUTTON3:
          _Marquee1.NewV = 100 - _Marquee1.NewV;
          _SerialSendCommand("MARQUEE", 1, _Marquee1.NewV);
          break;
        case GUI_ID_BUTTON4:
          _Garage.NewV = 100 - _Garage.NewV;
          _SerialSendCommand("GARAGE", _Garage.NewV, -1);
          break;
        case GUI_ID_BUTTON5:
          _LogoRPM = -RPM;
          _InvalidateObject(_hWinHouse, _LogoArrow.Rect);
          _SerialSendCommand("LOGO", 1, -1);
          break;
        case GUI_ID_BUTTON6:
          _LogoRPM  = 0;
          _LogoMulX = 1000;
          _InvalidateObject(_hWinHouse, _LogoArrow.Rect);
          _InvalidateObject(_hWinHouse, _Logo.Rect);
          _InvalidateObject2(_hWinMap, _LogoSmall.Rect);
          _SerialSendCommand("LOGO", 0, -1);
          break;
        case GUI_ID_BUTTON7:
          _LogoRPM = RPM;
          _InvalidateObject(_hWinHouse, _LogoArrow.Rect);
          _SerialSendCommand("LOGO", 2, -1);
          break;
        }
      }
    }
  case WM_TOUCH:
    WM_BringToTop(WM_GetParent(_hWinControl));
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbDialogElev
*/
static void _cbDialogElev(WM_MESSAGE* pMsg) {
  int i;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    _Elevator.Handle = pMsg->hWin; 
    break;
  case WM_NOTIFY_PARENT:
    if (_InitDialog) break;
    if (pMsg->Data.v == WM_NOTIFICATION_CLICKED) {
      int Id = WM_GetId(pMsg->hWinSrc);
      if (Id >= GUI_ID_BUTTON0 && Id <= GUI_ID_BUTTON4) {
        _ElevatorMove(Id - GUI_ID_BUTTON0);          
      } else {
        if (Id == GUI_ID_BUTTON5) {
          if (!_Elevator.Move) {
            if (_Elevator.Itself.ActV == _Elevator.Itself.NewV) {
              _ElevatorOpenDoor();
            }
          }
        }
        if (Id == GUI_ID_BUTTON6) {
          if (_Elevator.Pause) {
            BUTTON_SetText(pMsg->hWinSrc, "Pause");
          } else {
            BUTTON_SetText(pMsg->hWinSrc, "Resume");
          }
          _ElevatorPause();
        }
      }
    }
  case WM_TOUCH:
    WM_BringToTop(WM_GetParent(_hWinControl));
    break;
  case WM_PAINT:
    GUI_SetBkColor(GUI_BLACK);
    GUI_ClearRect(0, 0, 35, 15);      
    GUI_SetColor(GUI_GRAY);
    GUI_FillRect(0, 16, 35, 114);
    GUI_SetColor(GUI_WHITE);
    GUI_DrawRect(0, 0, 35, 114);
    GUI_DrawHLine(16, 0, 35);
    GUI_SetColor(GUI_RED);
    GUI_SetFont(&GUI_Font8x10_ASCII);
    GUI_DispCharAt(_Elevator.Level + '1', 9, 4);
    if (_Elevator.Move) {
      GUI_FillPolygon((_Elevator.Move < 0) ? _aArrowDown : _aArrowUp, 8, 22, 4);
    }
    GUI_SetBkColor(GUI_GRAY);
    GUI_SetFont(&GUI_Font6x8);
    for (i = 0; i < 5; i++) {
      GUI_SetColor((_Level[i].Elevator) ? GUI_RED : GUI_BLACK);
      GUI_DispCharAt(i + '1', 6, 97 - (i * 18));
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _NEC_Demo
*/
static void _NEC_Demo(void) {
  MULTIPAGE_Handle hMultiPage;
  FRAMEWIN_Handle hFrame;
  /* Use memory devices for all windows */
  WM_SetCreateFlags(WM_CF_MEMDEV);
  WM_EnableMemdev(WM_HBKWIN);
  /* Set the callback for the background window */
  WM_SetCallback(WM_HBKWIN, &_cbBkWindow);
  /* Create a framewin for the house */
  FRAMEWIN_SetDefaultCaptionSize(14);
  FRAMEWIN_SetDefaultFont(&GUI_Font10_1);
  hFrame = FRAMEWIN_Create("NEC - House", 0, WM_CF_SHOW, 100, 28, 217, 151);
  FRAMEWIN_SetMoveable(hFrame, 1);
  FRAMEWIN_SetActive(hFrame, 1);
  FRAMEWIN_CreateMinButton(hFrame, FRAMEWIN_BUTTON_RIGHT, 0);
  /* Get the client window and add a scrollbar */
  _hWinHouse = WM_GetClientWindow(hFrame);
  WM_SetCallback(_hWinHouse, &_cbWinHouse);
  _hScroll = SCROLLBAR_CreateAttached(_hWinHouse, SCROLLBAR_CF_VERTICAL);
  SCROLLBAR_SetNumItems(_hScroll, 780);
  SCROLLBAR_SetPageSize(_hScroll, 130);
  SCROLLBAR_SetValue(_hScroll, 650);
  FRAMEWIN_Minimize(hFrame);
  /* Create a framewin for the controls */
  _hWinControl = FRAMEWIN_Create("Control", 0, WM_CF_SHOW, 100, 5, 130, 181);
  FRAMEWIN_SetMoveable(_hWinControl, 1);
  FRAMEWIN_SetActive(_hWinControl, 1);
  FRAMEWIN_CreateMinButton(_hWinControl, FRAMEWIN_BUTTON_RIGHT, 0);
  FRAMEWIN_Minimize(_hWinControl);
  /* Get the client window and add controls */
  _hWinControl = WM_GetClientWindow(_hWinControl);
  WM_SetCallback(_hWinControl, &_cbWinControl);
  hMultiPage = MULTIPAGE_Create(3, 4, 117, 153, _hWinControl, 0, WM_CF_SHOW, 0);
  _hDialogLight  = _AddDialog("Light", ARRAY(_aDialogLight), &_cbDialogLight, hMultiPage);
  _AddDialog("Misc",  ARRAY(_aDialogMisc),  &_cbDialogMisc,  hMultiPage);
  _AddDialog("Elev.", ARRAY(_aDialogElev),  &_cbDialogElev,  hMultiPage);
  MULTIPAGE_SelectPage(hMultiPage, 0);
  /* Create a window for the house map */
  _hWinMap = WM_CreateWindow(0, 3, 57, 235, WM_CF_SHOW, &_cbWinMap, 0);
  /* Init some values */
  _Elevator.Itself.ActV = 650;
  _Elevator.Itself.NewV = 650;
  /* Init the serial interface */
  _SerialInit(&_cbReceiveCommand);
  /* Show the touch cursor */
  GUI_CURSOR_Select(&_TouchCursor);
  GUI_CURSOR_Show();
  /* Handle the windows */
  _ExecuteCommands = 1;
  while (1) {
    _SlideStatus();
    _ElevatorExec();
    if (_DrawRotateLogo()) {
      _InvalidateObject(_hWinHouse, _Logo.Rect);
      _InvalidateObject2(_hWinMap, _LogoSmall.Rect);
    }
    _SerialExec();
    WM_Exec();
  }
}

/*********************************************************************
*
*       MainTask
*
**********************************************************************
*/

void MainTask_demo(void) {
  GUI_Init();
  _NEC_Demo();
}
