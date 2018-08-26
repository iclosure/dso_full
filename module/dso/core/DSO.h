
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
 File        : DSO.h
 Purpose     : DSO APP include file
   ----------------------------------------------------------------------
 */

#ifndef DSO_H_
#define DSO_H_


#include "LCDConf.h"
#include "GUI.h"
#include "DIALOG_Intern.h"
#include "MENU.h"
#include "FRAMEWIN.h"

#include "DSO_GUIConf.h"
#include "DSO_ParaConf.h"
#include "DSO_ConfDefaults.h"
#include "DSOType.h"


/* 显示屏的中心 */
#ifndef LCD_XSIZE_CENTER2
#define LCD_XSIZE_CENTER2    (LCD_XSIZE/2)
#define LCD_YSIZE_CENTER2    (LCD_YSIZE/2)
#define LCD_XSIZE_CENTER4    (LCD_XSIZE/4)
#define LCD_YSIZE_CENTER4    (LCD_YSIZE/4)
#endif /*LCD_XSIZE_CENTER2*/

/* 模型显示窗口模式 */
#define DSO_WAVEWIN_SMALL         0x001
#define DSO_WAVEWIN_LARGE         0x002

/*  */
/******************************************************
 * 
 * DSO: the back picture of some buttons
 * 
 */

// bmp pictures
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_logo;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_amplitude;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_dutycycle;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_period;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_freq;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_minimum;  //
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_maximum;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_vpp;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_topvalue;  //
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_mean;  //  
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_negwidth;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_poswidth;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_area;  //  
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_tririse;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_trifall;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_upshoot;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_downshoot;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmwavewin_large;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmMark_HLeftIcon;   // 
extern GUI_CONST_STORAGE GUI_BITMAP bmMark_HRightIcon;  // 
extern GUI_CONST_STORAGE GUI_BITMAP bmMark_VDownIcon;   // 


// gif pictures
extern unsigned char acwavewin_large_gif[17672];  //
extern unsigned char acwavewin_large_jpeg[44756];  //

// jpeg pictures

// 定义无效ID
#define GUI_ID_INVALIDE      (GUI_ID_USER + 1) 

/*********************************************************************
*
*              标题栏菜单项信息
*/

/* GUI_ID_USER = 0x800 [in GUI.h]*/
/* Main Menu Item */
#define MENU_ID_MAIN         (GUI_ID_INVALIDE + 1) 
#define MENU_ID_MAIN1        (MENU_ID_MAIN + 1) 
#define MENU_ID_MAIN2        (MENU_ID_MAIN + 2) 
#define MENU_ID_MAIN3        (MENU_ID_MAIN + 3) 
#define MENU_ID_MAIN4        (MENU_ID_MAIN + 4) 
#define MENU_ID_MAIN5        (MENU_ID_MAIN + 5) 
#define MENU_ID_MAIN6        (MENU_ID_MAIN + 6) 
#define MENU_ID_MAIN7        (MENU_ID_MAIN + 7) 
#define MENU_ID_MAIN8        (MENU_ID_MAIN + 8) 
#define MENU_ID_MAIN9        (MENU_ID_MAIN + 9) 
#define MENU_ID_MAIN_END      MENU_ID_MAIN9
/* File Menu Item */
#define MENU_ID_FILE1        (MENU_ID_MAIN_END + 1) 
#define MENU_ID_FILE2        (MENU_ID_MAIN_END + 2) 
#define MENU_ID_FILE3        (MENU_ID_MAIN_END + 3) 
#define MENU_ID_FILE4        (MENU_ID_MAIN_END + 4) 
#define MENU_ID_FILE5        (MENU_ID_MAIN_END + 5) 
#define MENU_ID_FILE6        (MENU_ID_MAIN_END + 6) 
#define MENU_ID_FILE7        (MENU_ID_MAIN_END + 7) 
#define MENU_ID_FILE8        (MENU_ID_MAIN_END + 8) 
#define MENU_ID_FILE9        (MENU_ID_MAIN_END + 9) 
#define MENU_ID_FILE_END      MENU_ID_FILE9
/* Control Menu Item */
#define MENU_ID_CONTROL1     (MENU_ID_FILE_END + 1) 
#define MENU_ID_CONTROL2     (MENU_ID_FILE_END + 2) 
#define MENU_ID_CONTROL3     (MENU_ID_FILE_END + 3) 
#define MENU_ID_CONTROL4     (MENU_ID_FILE_END + 4) 
#define MENU_ID_CONTROL5     (MENU_ID_FILE_END + 5) 
#define MENU_ID_CONTROL6     (MENU_ID_FILE_END + 6) 
#define MENU_ID_CONTROL7     (MENU_ID_FILE_END + 7) 
#define MENU_ID_CONTROL8     (MENU_ID_FILE_END + 8) 
#define MENU_ID_CONTROL9     (MENU_ID_FILE_END + 9) 
#define MENU_ID_CONTROL_END   MENU_ID_CONTROL9
/* Setup Menu Item */
#define MENU_ID_SETUP1       (MENU_ID_CONTROL_END + 1) 
#define MENU_ID_SETUP2       (MENU_ID_CONTROL_END + 2) 
#define MENU_ID_SETUP3       (MENU_ID_CONTROL_END + 3) 
#define MENU_ID_SETUP4       (MENU_ID_CONTROL_END + 4)
#define MENU_ID_SETUP5       (MENU_ID_CONTROL_END + 5) 
#define MENU_ID_SETUP6       (MENU_ID_CONTROL_END + 6) 
#define MENU_ID_SETUP7       (MENU_ID_CONTROL_END + 7) 
#define MENU_ID_SETUP8       (MENU_ID_CONTROL_END + 8)
#define MENU_ID_SETUP9       (MENU_ID_CONTROL_END + 9) 
#define MENU_ID_SETUP10      (MENU_ID_CONTROL_END +10)
#define MENU_ID_SETUP_END     MENU_ID_SETUP8
/* Trigger Menu Item */
#define MENU_ID_TRIGGER1     (MENU_ID_SETUP_END + 1) 
#define MENU_ID_TRIGGER2     (MENU_ID_SETUP_END + 2) 
#define MENU_ID_TRIGGER3     (MENU_ID_SETUP_END + 3) 
#define MENU_ID_TRIGGER4     (MENU_ID_SETUP_END + 4) 
#define MENU_ID_TRIGGER5     (MENU_ID_SETUP_END + 5) 
#define MENU_ID_TRIGGER6     (MENU_ID_SETUP_END + 6) 
#define MENU_ID_TRIGGER7     (MENU_ID_SETUP_END + 7) 
#define MENU_ID_TRIGGER8     (MENU_ID_SETUP_END + 8) 
#define MENU_ID_TRIGGER_END   MENU_ID_TRIGGER8
/* Measure Menu Item */
#define MENU_ID_MEASURE1     (MENU_ID_TRIGGER_END + 1) 
#define MENU_ID_MEASURE2     (MENU_ID_TRIGGER_END + 2) 
#define MENU_ID_MEASURE3     (MENU_ID_TRIGGER_END + 3) 
#define MENU_ID_MEASURE4     (MENU_ID_TRIGGER_END + 4) 
#define MENU_ID_MEASURE5     (MENU_ID_TRIGGER_END + 5) 
#define MENU_ID_MEASURE6     (MENU_ID_TRIGGER_END + 6) 
#define MENU_ID_MEASURE7     (MENU_ID_TRIGGER_END + 7) 
#define MENU_ID_MEASURE8     (MENU_ID_TRIGGER_END + 8) 
#define MENU_ID_MEASURE9     (MENU_ID_TRIGGER_END + 9) 
#define MENU_ID_MEASURE10    (MENU_ID_TRIGGER_END + 10) 
#define MENU_ID_MEASURE11    (MENU_ID_TRIGGER_END + 11) 
#define MENU_ID_MEASURE12    (MENU_ID_TRIGGER_END + 12) 
#define MENU_ID_MEASURE13    (MENU_ID_TRIGGER_END + 13) 
#define MENU_ID_MEASURE_END   MENU_ID_MEASURE13
/* Math Menu Item */
#define MENU_ID_MATH1        (MENU_ID_MEASURE_END + 1) 
#define MENU_ID_MATH2        (MENU_ID_MEASURE_END + 2) 
#define MENU_ID_MATH3        (MENU_ID_MEASURE_END + 3) 
#define MENU_ID_MATH4        (MENU_ID_MEASURE_END + 4) 
#define MENU_ID_MATH5        (MENU_ID_MEASURE_END + 5) 
#define MENU_ID_MATH6        (MENU_ID_MEASURE_END + 6) 
#define MENU_ID_MATH_END      MENU_ID_MATH6
/* Analyze Menu Item */
#define MENU_ID_ANALYZE1     (MENU_ID_MATH_END + 1) 
#define MENU_ID_ANALYZE2     (MENU_ID_MATH_END + 2) 
#define MENU_ID_ANALYZE3     (MENU_ID_MATH_END + 3) 
#define MENU_ID_ANALYZE4     (MENU_ID_MATH_END + 4) 
#define MENU_ID_ANALYZE5     (MENU_ID_MATH_END + 5) 
#define MENU_ID_ANALYZE6     (MENU_ID_MATH_END + 6) 
#define MENU_ID_ANALYZE7     (MENU_ID_MATH_END + 7) 
#define MENU_ID_ANALYZE8     (MENU_ID_MATH_END + 8) 
#define MENU_ID_ANALYZE9     (MENU_ID_MATH_END + 9) 
#define MENU_ID_ANALYZE_END   MENU_ID_ANALYZE9
/* Utitlies Menu Item */
#define MENU_ID_UTILTIES1    (MENU_ID_ANALYZE_END + 1) 
#define MENU_ID_UTILTIES2    (MENU_ID_ANALYZE_END + 2) 
#define MENU_ID_UTILTIES3    (MENU_ID_ANALYZE_END + 3) 
#define MENU_ID_UTILTIES4    (MENU_ID_ANALYZE_END + 4) 
#define MENU_ID_UTILTIES5    (MENU_ID_ANALYZE_END + 5) 
#define MENU_ID_UTILTIES6    (MENU_ID_ANALYZE_END + 6) 
#define MENU_ID_UTILTIES7    (MENU_ID_ANALYZE_END + 7) 
#define MENU_ID_UTILTIES8    (MENU_ID_ANALYZE_END + 8) 
#define MENU_ID_UTILTIES9    (MENU_ID_ANALYZE_END + 9) 
#define MENU_ID_UTILTIES10   (MENU_ID_ANALYZE_END +10) 
#define MENU_ID_UTILTIES_END  MENU_ID_UTILTIES10
/* Help Menu Item */
#define MENU_ID_HELP1        (MENU_ID_UTILTIES_END + 1) 
#define MENU_ID_HELP2        (MENU_ID_UTILTIES_END + 2) 
#define MENU_ID_HELP_END      MENU_ID_HELP2

/*********************************************************************
*
*              主窗口右边的按钮信息
*/

#define RIGHT_BUTTON         (MENU_ID_HELP_END + 1) 
#define RIGHT_BUTTON1        (RIGHT_BUTTON + 1) 
#define RIGHT_BUTTON2        (RIGHT_BUTTON + 2) 
#define RIGHT_BUTTON3        (RIGHT_BUTTON + 3) 
#define RIGHT_BUTTON4        (RIGHT_BUTTON + 4) 
#define RIGHT_BUTTON5        (RIGHT_BUTTON + 5) 
#define RIGHT_BUTTON6        (RIGHT_BUTTON + 6) 
#define RIGHT_BUTTON7        (RIGHT_BUTTON + 7) 
#define RIGHT_BUTTON8        (RIGHT_BUTTON + 8) 
#define RIGHT_BUTTON9        (RIGHT_BUTTON + 9) 
#define RIGHT_BUTTON10       (RIGHT_BUTTON +10) 
#define RIGHT_BUTTON11       (RIGHT_BUTTON +11) 
#define RIGHT_BUTTON12       (RIGHT_BUTTON +12) 
#define RIGHT_BUTTON13       (RIGHT_BUTTON +13) 
#define RIGHT_BUTTON14       (RIGHT_BUTTON +14) 
#define RIGHT_BUTTON15       (RIGHT_BUTTON +15) 
#define RIGHT_BUTTON16       (RIGHT_BUTTON +16) 
#define RIGHT_BUTTON17       (RIGHT_BUTTON +17)
#define RIGHT_BUTTON_END      RIGHT_BUTTON17

/**************************************************************
*
*       LCD_DispFullBitmap  [用户添加：in ../../../UCGUI/GUI/LCDDriver/LCDDummy.c]
*/
#define GUI_DispFullBitmap     LCD_DispFullBitmap
void GUI_DispFullBitmap(const char *pBitmap);


/**************************************************************
 * 
 *          DSO_InitGUI [初始化示波器主界面]
 * 
 */

void DSO_InitGUI(void);







#endif /*DSO_H_*/
