
#if 0000

#include "DSO.h"
#include "SysVar.h"

GUI_RECT	WaveWin= {WAVEWIN_SX,WAVEWIN_SY,WAVEWIN_EX,WAVEWIN_EY};  // 波形绘制窗口
/**************************************************************
 * 
 *                     测量类::菜单变量的初始化
 */
/* <>measure::SK_1</> */
MENU_ITEM_DATA MEAS_SK1_MenuUp_Item[10]= {
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmSlopeRisingEdge},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmSlopeRisingEdge},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmSlopeRisingEdge},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmSlopeRisingEdge},
	{0, MENUUP_IF_TITLE,0, &MENU_MEAS,NULL},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmSlopeRisingEdge},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmSlopeRisingEdge},
	{0, MENUUP_IF_TITLE,0, &MENU_MEAS,NULL},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmSlopeRisingEdge},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmSlopeRisingEdge},
};
MENU_UP_DATA MEAS_SK1_MenuUp= {
	MEAS_SK1_MenuUp_Item, 10, {0,0,0,MENUUP_EY}
};
/* <>measure::SK_2</> */
MENU_UP_DATA MEAS_SK2_MenuUp;
SOFTKEY_DATA  MEAS_SK2_MenuUp_Menu0_SK[3]= {
	{ 2, 3, SOFTKEY_IF_STATIC},
	{ 4, 5, SOFTKEY_IF_STATIC},
	{ 5, 6, SOFTKEY_IF_STATIC},
};
MENU_PAGE_DATA MEAS_SK2_MenuUp_Menu0_Page= {
	3, MEAS_SK2_MenuUp_Menu0_SK
};
MENU_ITEM_DATA MEAS_SK2_MenuUp_Item[18]= {
	{0, MENUUP_IF_TITLE,0, &MENU_MEAS},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmicon_mean_cycle},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmicon_mean_fs},
	{0, MENUUP_IF_SEPARATOR,0, &MENU_MEAS},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmicon_dc_rms_cycle},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmicon_dc_rms_fs},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmicon_ac_rms_cycle},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,&MEAS_SK2_MenuUp_Menu0_Page, &bmicon_ac_rms_fs},
	{0, MENUUP_IF_TITLE,0, &MENU_MEAS},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmSlopeRisingEdge},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmSlopeFallingEdge},
	{0, MENUUP_IF_TITLE,0, &MENU_MEAS},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmicon_period},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmicon_freq},
	
	{0, MENUUP_IF_SEPARATOR,0, &MENU_MEAS},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmSlopeRisingEdge},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmicon_dc_rms_fs},
	{0, MENUUP_IF_MENU, 0, &MENU_MEAS,NULL, &bmicon_ac_rms_cycle},
};
MENU_UP_DATA MEAS_SK2_MenuUp= {
	MEAS_SK2_MenuUp_Item, 18,{0,0,0,MENUUP_EY}
};
SOFTKEY_DATA  MEAS_SK[4]= {
	{ 0, 1, SOFTKEY_IF_STATIC, &MEAS_SK1_MenuUp},
	{ 1, 2, SOFTKEY_IF_STATIC, &MEAS_SK2_MenuUp},
//	{ 2, 3, SOFTKEY_IF_STATIC},
	{ 4, 4, SOFTKEY_IF_DISABLED},
	{ 5, 6, SOFTKEY_IF_STATIC},
};

MENU_PAGE_DATA MENU_MEAS= {
	4, MEAS_SK
};

#endif /* 0000 */
