#ifndef SYSVAR_H_
#define SYSVAR_H_


#if 0000
#include "MENUType.h"


/**************************************************************
 * 
 *                     �����������������
 */
U16            OldKey, NewKey;  // ��ֵ
I8             index_MenuItem;  // �����˵����������
MENU_PAGE_DATA   ActivatePage;  // ��ʼ����ǰ��Ծ�˵�Ŀ��(ָ��ǰ���ڱ�����״̬)
SOFTKEY_DATA       ActivateSK;  // ��ǰҳ���Ծ���(ָ��ǰ���ڱ�����״̬)
SOFTKEY_DATA    CurrPageSK[6];  // ��ǰҳ�����п������
I8          index_sn,index_en;  // ��ǰ�����˵��Ĳ˵���[��ʼ]��[��ֹ]����[�������ָ��ߺͱ�����]
GUI_RECT			  WaveWin;  // ���λ��ƴ���
/**************************************************************
 * 
 *                     �˵�����������
 */
MENU_PAGE_DATA MENU_MEAS;  // ������

#endif /* 0000 */

#endif /*SYSVAR_H_*/
