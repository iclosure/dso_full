
/*
 * ***************************************************
 *                  ©¶®Z  ®W ®X®T®T®[ ®i ®X®T®T®Y©¶
 *                  ©¶®^®T®T®a ®`  ®] ®l ®^®T®T®_©¶
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
 File        : DSO_Menu.c
 Purpose     : DSO Menu.
   ----------------------------------------------------------------------
 */


#include "DSO.h"
#include "DSO_Private.h"
#include <stdlib.h>



/*******************************************************************
*
*                     _AddMenuItem
*/

static void _AddMenuItem(MENU_Handle hObj, MENU_ITEM_DATA* pItemData, int Itemnum, MENU_Handle hSubmenu) {
	int i;
	if(pItemData->hSubmenu == 1)
		pItemData->hSubmenu = hSubmenu;
	for(i=0; i<Itemnum; i++)
		MENU_AddItem(hObj, &pItemData[i]);
}

/*******************************************************************
*
*                     DSO_MENU_CreateMenu
*/
void  DSO_MENU_CreateMenu(WM_HWIN hWin) {

	MENU_Handle hMenu;
	MENU_Handle hFile;
	MENU_Handle hControl;
	MENU_Handle hSetup;
	MENU_Handle hTrigger;
	MENU_Handle hMeasure;
	MENU_Handle hMath;
	MENU_Handle hAnalyze,hAnalyze_AutoTest;
	MENU_Handle hUtilties;
	MENU_Handle hHelp;

	MENU_SetDefaultFont(&GUI_Font16B_ASCII);
	/* Create File menu */
	hFile = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_VERTICAL, MENU_ID_MAIN1);
	_AddMenuItem(hFile,_MainMenu_File, GUI_COUNTOF(_MainMenu_File),0);
	/* Create Control menu */
	hControl = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_VERTICAL, MENU_ID_MAIN2);
	_AddMenuItem(hControl,_MainMenu_Control, GUI_COUNTOF(_MainMenu_Control),0);
	/* Create Setup menu */
	hSetup = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_VERTICAL, MENU_ID_MAIN3);
	_AddMenuItem(hSetup,_MainMenu_Setup, GUI_COUNTOF(_MainMenu_Setup),0);
	/* Create Trigger menu */
	hTrigger = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_VERTICAL, MENU_ID_MAIN4);
	_AddMenuItem(hTrigger,_MainMenu_Trigger, GUI_COUNTOF(_MainMenu_Trigger),0);
	/* Create Measure menu */
	hMeasure = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_VERTICAL, MENU_ID_MAIN5);
	_AddMenuItem(hMeasure,_MainMenu_Measure, GUI_COUNTOF(_MainMenu_Measure),0);
	/* Create Math menu */
	hMath = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_VERTICAL, MENU_ID_MAIN6);
	_AddMenuItem(hMath,_MainMenu_Math, GUI_COUNTOF(_MainMenu_Math),0);
	/* Create Analyze menu */
	hAnalyze = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_VERTICAL, MENU_ID_MAIN7);
	_AddMenuItem(hAnalyze,_MainMenu_Analyze, GUI_COUNTOF(_MainMenu_Analyze),/*hAnalyze_AutoTest*/0);
	/* Create Analyze->Automated Test Apps... menu */
	hAnalyze_AutoTest = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_HORIZONTAL, MENU_ID_MAIN7);
	_MainMenu_Analyze[6].hSubmenu = hAnalyze_AutoTest;
	_AddMenuItem(hAnalyze_AutoTest,_MainMenu_Analyze_AutoTest, GUI_COUNTOF(_MainMenu_Analyze_AutoTest),0);

	/* Create Utilties menu */
	hUtilties = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_VERTICAL, MENU_ID_MAIN8);
	_AddMenuItem(hUtilties,_MainMenu_Utilties, GUI_COUNTOF(_MainMenu_Utilties),0);
	/* Create Help menu */
	hHelp = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_VERTICAL, MENU_ID_MAIN9);
	_AddMenuItem(hHelp,_MainMenu_Help, GUI_COUNTOF(_MainMenu_Help),0);
	/* Create main menu */
	hMenu = MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_HORIZONTAL, MENU_ID_MAIN);
	_MainMenu_Main[0].hSubmenu = hFile;
	_MainMenu_Main[1].hSubmenu = hControl;
	_MainMenu_Main[2].hSubmenu = hSetup;
	_MainMenu_Main[3].hSubmenu = hTrigger;
	_MainMenu_Main[4].hSubmenu = hMeasure;
	_MainMenu_Main[5].hSubmenu = hMath;
	_MainMenu_Main[6].hSubmenu = hAnalyze;
	_MainMenu_Main[7].hSubmenu = hUtilties;
	_MainMenu_Main[8].hSubmenu = hHelp;
	_AddMenuItem(hMenu, _MainMenu_Main, GUI_COUNTOF(_MainMenu_Main), 0);

	/* Attach menu to framewin */
	FRAMEWIN_AddMenu(hWin, hMenu);
	/* ÀıΩ¯…Ë÷√ */
	MENU_SetBorderSize(hFile,MENU_BI_LEFT,20);
	MENU_SetBorderSize(hControl,MENU_BI_LEFT,20);
	MENU_SetBorderSize(hSetup,MENU_BI_LEFT,20);
	MENU_SetBorderSize(hTrigger,MENU_BI_LEFT,20);
	MENU_SetBorderSize(hMeasure,MENU_BI_LEFT,20);
	MENU_SetBorderSize(hMath,MENU_BI_LEFT,20);
	MENU_SetBorderSize(hAnalyze,MENU_BI_LEFT,20);
	MENU_SetBorderSize(hUtilties,MENU_BI_LEFT,20);
	MENU_SetBorderSize(hHelp,MENU_BI_LEFT,20);
}


/*************************** End of source ******************************/
