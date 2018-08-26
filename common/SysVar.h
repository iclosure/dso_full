#ifndef SYSVAR_H_
#define SYSVAR_H_


#if 0000
#include "MENUType.h"


/**************************************************************
 * 
 *                     按键编码变量的声明
 */
U16            OldKey, NewKey;  // 键值
I8             index_MenuItem;  // 上拉菜单项计数变量
MENU_PAGE_DATA   ActivatePage;  // 初始化当前活跃菜单目标(指当前处于被操作状态)
SOFTKEY_DATA       ActivateSK;  // 当前页面活跃软键(指当前处于被操作状态)
SOFTKEY_DATA    CurrPageSK[6];  // 当前页面所有可用软键
I8          index_sn,index_en;  // 当前上拉菜单的菜单项[起始]和[终止]索引[不包括分隔线和标题栏]
GUI_RECT			  WaveWin;  // 波形绘制窗口
/**************************************************************
 * 
 *                     菜单变量的声明
 */
MENU_PAGE_DATA MENU_MEAS;  // 测量类

#endif /* 0000 */

#endif /*SYSVAR_H_*/
