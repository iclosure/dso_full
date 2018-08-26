
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
 File        : DSO_UserData.h
 Purpose     : DSO : some user datas
   ----------------------------------------------------------------------
 */


#include "DSO.h"
#include "DIALOG_Intern.h"
#include <stdlib.h>
#include "LISTBOX.h"
#include "CHECKBOX.h"
#include "SLIDER.h"
#include "FRAMEWIN.h"
#include "TEXT.h"
#include "DROPDOWN.h"
#include "MENU.h"
#include "WINDOW_Private.h"


/**************************************************************
 * 
 *  Pictures
 * 
 */

BUTTON_BkPicInfo _RightButton_BkPicInfo[17] = {





	{0,&bmbutton_logo,      RIGHT_BUTTON1},
	{0,&bmbutton_amplitude, RIGHT_BUTTON2},
	{0,&bmbutton_dutycycle, RIGHT_BUTTON3},
	{0,&bmbutton_period,    RIGHT_BUTTON4},
	{0,&bmbutton_freq,      RIGHT_BUTTON5},
	{0,&bmbutton_minimum,   RIGHT_BUTTON6},
	{0,&bmbutton_maximum,   RIGHT_BUTTON7},
	{0,&bmbutton_vpp,       RIGHT_BUTTON8},
	{0,&bmbutton_topvalue,  RIGHT_BUTTON9},
	{0,&bmbutton_mean,      RIGHT_BUTTON10},
	{0,&bmbutton_negwidth,  RIGHT_BUTTON11},
	{0,&bmbutton_poswidth,  RIGHT_BUTTON12},
	{0,&bmbutton_area,      RIGHT_BUTTON13},
	{0,&bmbutton_tririse,   RIGHT_BUTTON14},
	{0,&bmbutton_trifall,   RIGHT_BUTTON15},
	{0,&bmbutton_upshoot,   RIGHT_BUTTON16},
	{0,&bmbutton_downshoot, RIGHT_BUTTON17},
};


/*********************************************************************
*
*                       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created manually, but could also be created by a GUI-builder.
*/
///////////////////////////////////////////////////////////
/* Main Menu Item */
MENU_ITEM_DATA _MainMenu_Main[9] = {
	{ "File",     MENU_ID_MAIN1, 0, 0 },
	{ "Control",  MENU_ID_MAIN2, 0, 0 },
	{ "Setup",    MENU_ID_MAIN3, 0, 0 },
	{ "Trigger",  MENU_ID_MAIN4, 0, 0 },
	{ "Measure",  MENU_ID_MAIN5, 0, 0 },
	{ "Math",     MENU_ID_MAIN6, 0, 0 },
	{ "Analyze",  MENU_ID_MAIN7, 0, 0 },
	{ "Utilties", MENU_ID_MAIN8, 0, 0 },
	{ "Help",     MENU_ID_MAIN9, 0, 0 },
};
///////////////////////////////////////////////////////////
/* File Menu Item */
MENU_ITEM_DATA _MainMenu_File[10] = {
	{ "New...    Ctrl+N", MENU_ID_FILE1, 0, 0 },
	{ "Open...   Ctrl+O", MENU_ID_FILE2, 0, 0 },
	{ "Close",            MENU_ID_FILE3, MENU_IF_DISABLED, 0 },
	{ "Save     Ctrl+S",  MENU_ID_FILE4, MENU_IF_DISABLED, 0 },
	{ "Save all ",        MENU_ID_FILE5, MENU_IF_DISABLED, 0 },
	{ "Setup...",         MENU_ID_FILE6, 0, 0 },
	{ "Print     Ctrl+P", MENU_ID_FILE7, MENU_IF_DISABLED, 0 },
	{ "Recent",           MENU_ID_FILE8, 0, 0 },
	{ 0,                              0, MENU_IF_SEPARATOR, 0 },
	{ "Exit",             MENU_ID_FILE9, 0, 0 },
};
///////////////////////////////////////////////////////////
/* Control Menu Item */
MENU_ITEM_DATA _MainMenu_Control[4] = {
	{ "NULL", MENU_ID_CONTROL1, 0, 0 },
	{ "NULL", MENU_ID_CONTROL2, 0, 0 },
	{ "NULL", MENU_ID_CONTROL3, 0, 0 },
	{ "NULL", MENU_ID_CONTROL4, 0, 0 },
};
///////////////////////////////////////////////////////////
/* Setup Menu Item */
MENU_ITEM_DATA _MainMenu_Setup[10] = {
	{ "Channel 1...",         MENU_ID_SETUP1, 0, 0 },
	{ "Channel 2...",         MENU_ID_SETUP2, 0, 0 },
	{ "Probes...",            MENU_ID_SETUP3, 0, 0 },
	{ "Serial Decode...",     MENU_ID_SETUP4, 0, 0 },
	{ "Serial Search...",     MENU_ID_SETUP5, 0, 0 },
	{ "Digital...",           MENU_ID_SETUP6, 0, 0 },
	{ "Horizontal...",        MENU_ID_SETUP7, 0, 0 },
	{ "Acquisition...",       MENU_ID_SETUP8, 0, 0 },
	{ "Display...",           MENU_ID_SETUP9, 0, 0 },
	{ "Waveform Memories...", MENU_ID_SETUP10,0, 0 },
};
///////////////////////////////////////////////////////////
/* Trigger Menu Item */
MENU_ITEM_DATA _MainMenu_Trigger[8] = {
	{ "Setup Trigger...",     MENU_ID_TRIGGER1, 0, 0 },
	{ "Shortcuts",            MENU_ID_TRIGGER2, 0, 0 },
	{ "Gallery...",           MENU_ID_TRIGGER3, 0, 0 },
	{ "InfiniiScan...",       MENU_ID_TRIGGER4, 0, 0 },
	{ "Trigger Sawe/Load...", MENU_ID_TRIGGER5, 0, 0 },
	{ "Conditioning...",      MENU_ID_TRIGGER6, 0, 0 },
	{ "Trigger Action...",    MENU_ID_TRIGGER7, 0, 0 },
	{ "Trigger Levels...",    MENU_ID_TRIGGER8, 0, 0 },
};
///////////////////////////////////////////////////////////
/* Measure Menu Item */
MENU_ITEM_DATA _MainMenu_Measure[13] = {
	{ "Markers...",             MENU_ID_MEASURE1, 0, 0 },
	{ "QuickMeas",              MENU_ID_MEASURE2, 0, 0 },
	{ "Delete",                 MENU_ID_MEASURE3, 0, 0 },
	{ "Voltage",                MENU_ID_MEASURE4, 0, 0 },
	{ "Time",                   MENU_ID_MEASURE5, 0, 0 },
	{ "Mixed",                  MENU_ID_MEASURE6, 0, 0 },
	{ "Frequency",              MENU_ID_MEASURE7, 0, 0 },
	{ "Eye Pattern",            MENU_ID_MEASURE8, 0, 0 },
	{ "Jitter",                 MENU_ID_MEASURE9, 0, 0 },
	{ "Limit Test & Search...", MENU_ID_MEASURE10,0, 0 },
	{ "Setup...",               MENU_ID_MEASURE11,0, 0 },
	{ "Thresholds...",          MENU_ID_MEASURE12,0, 0 },
	{ "Level Qualification...", MENU_ID_MEASURE13,0, 0 },
};
///////////////////////////////////////////////////////////
/* Math Menu Item */
MENU_ITEM_DATA _MainMenu_Math[6] = {
	{ "FFT",  MENU_ID_MATH1, 0, 0 },
	{ "NULL", MENU_ID_MATH2, 0, 0 },
	{ "NULL", MENU_ID_MATH3, 0, 0 },
	{ "NULL", MENU_ID_MATH4, 0, 0 },
	{ "NULL", MENU_ID_MATH5, 0, 0 },
	{ "NULL", MENU_ID_MATH6, 0, 0 },
};
///////////////////////////////////////////////////////////
/* Analyze Menu Item */
MENU_ITEM_DATA _MainMenu_Analyze[6] = {
	{ "Math(FFT and more)...",  MENU_ID_ANALYZE1, 0, 0 },
	{ "Histogram...",           MENU_ID_ANALYZE2, 0, 0 },
	{ "Mask setup...",          MENU_ID_ANALYZE3, 0, 0 },
	{ "Serial Data...",         MENU_ID_ANALYZE4, 0, 0 },
	{ "Equalization...",        MENU_ID_ANALYZE5, 0, 0 },
	{ "Automated Test Apps...", MENU_ID_ANALYZE6, 0, 0 },
};
/* Analyze->Automated Test Apps... Menu Item */
MENU_ITEM_DATA _MainMenu_Analyze_AutoTest[3] = {
	{ "DDR2 Test",    MENU_ID_ANALYZE1, 0, 0 },
	{ "SATA&G Test",  MENU_ID_ANALYZE2, 0, 0 },
	{ "User Defined", MENU_ID_ANALYZE3, 0, 0 },
};
///////////////////////////////////////////////////////////
/* Utilties Menu Item */
MENU_ITEM_DATA _MainMenu_Utilties[10] = {
	{ "Calibration...",            MENU_ID_UTILTIES1, 0, 0 },
	{ "Self Test...",              MENU_ID_UTILTIES2, 0, 0 },
	{ "eGUI...",                   MENU_ID_UTILTIES3, 0, 0 },
	{ "Remeote Setup...",          MENU_ID_UTILTIES4, 0, 0 },
	{ "Web Cotrol...",             MENU_ID_UTILTIES5, 0, 0 },
	{ "LXI LAN Setup...",          MENU_ID_UTILTIES6, 0, 0 },
	{ "Install Option License...", MENU_ID_UTILTIES7, 0, 0 },
	{ "User Preferences...",       MENU_ID_UTILTIES8, 0, 0 },
	{ "Multipurpose",              MENU_ID_UTILTIES9, 0, 0 },
	{ "Customize Multipurpose...", MENU_ID_UTILTIES10,0, 0 },
};
///////////////////////////////////////////////////////////
/* Help Menu Item */
MENU_ITEM_DATA _MainMenu_Help[2] = {
	{ "Contents...    F1",  MENU_ID_HELP1,0, 0 },
	{ "About Infiniium...", MENU_ID_HELP2,0, 0 },
};
///////////////////////////////////////////////////////////
/****************************************************************
 ****************************************************************
 *                       对话框信息
 */
/****************************************************************
 *  
 *                     主菜单对话框信息
 */

const GUI_WIDGET_CREATE_INFO _aDialogCreate[18] = {
  { FRAMEWIN_CreateIndirect, "Dialog", 0,                 30,   5, 260, 230, FRAMEWIN_CF_MOVEABLE, 0  },
  { BUTTON_CreateIndirect,   "OK",     GUI_ID_OK,        100,   5,  60,  20 },
  { BUTTON_CreateIndirect,   "Cancel", GUI_ID_CANCEL,    100,  30,  60,  20 },
  { TEXT_CreateIndirect,     "LText",  0,                 10,  55,  48,  15, TEXT_CF_LEFT  },
  { TEXT_CreateIndirect,     "RText",  0,                 10,  80,  48,  15, TEXT_CF_RIGHT },
  { EDIT_CreateIndirect,     NULL,     GUI_ID_EDIT0,      60,  55, 100,  15, 0, 50 },
  { EDIT_CreateIndirect,     NULL,     GUI_ID_EDIT1,      60,  80, 100,  15, 0, 50 },
  { TEXT_CreateIndirect,     "Hex",    0,                 10, 100,  48,  15, TEXT_CF_RIGHT },
  { EDIT_CreateIndirect,     NULL,     GUI_ID_EDIT2,      60, 100, 100,  15, 0, 6 },
  { TEXT_CreateIndirect,     "Bin",    0,                 10, 120,  48,  15, TEXT_CF_RIGHT },
  { EDIT_CreateIndirect,     NULL,     GUI_ID_EDIT3,      60, 120, 100,  15 },
  { LISTBOX_CreateIndirect,  NULL,     GUI_ID_LISTBOX0,   10,  10,  60,  40 },
  { CHECKBOX_CreateIndirect, NULL,     GUI_ID_CHECK0,     10, 140,   0,   0 },
  { CHECKBOX_CreateIndirect, NULL,     GUI_ID_CHECK1,     30, 140,   0,   0 },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER0,    60, 140, 180,  20 },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER1,    10, 170, 230,  30 },
  { DROPDOWN_CreateIndirect,  NULL,    GUI_ID_DROPDOWN0, 170,  10,  80,  60, 0, 3  },
  { DROPDOWN_CreateIndirect,  NULL,    GUI_ID_DROPDOWN1, 170,  60,  80,  60, 0, 3  }
};

/****************************************************************
 *  
 *                     Help->2_About Infiniium
 */
const GUI_WIDGET_CREATE_INFO _aDialog_Help_AboutInfiniium[18] = {
  { FRAMEWIN_CreateIndirect, "Dialog", 0,                 30,   5, 260, 230, FRAMEWIN_CF_MOVEABLE, 0  },
  { BUTTON_CreateIndirect,   "OK",     GUI_ID_OK,        100,   5,  60,  20 },

};

