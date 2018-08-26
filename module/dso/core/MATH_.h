
/*
 * ***************************************************
 *                  ���Z  �W �X�T�T�[ �i �X�T�T�Y��
 *                  ���^�T�T�a �`  �] �l �^�T�T�_��
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
 File        : MATH_.h
 Purpose     : DSO math file.
   ----------------------------------------------------------------------
 */

#ifndef MATH__H_
#define MATH__H_

#include "LCD.h"
#include <math.h>
#include <stdlib.h>

/************************************************************
 *                 
 *                       defined
 */
#ifndef PI 
#define PI  3.1415926535897932  // (pi ?= 355/113)
#endif /* #ifndef PI  */

#ifndef SQRT
#define SQRT  
#define SQRT_2        (1.414213197969543)   /* 2��ƽ���� */
#define _1DIVSQRT_2   (0.707106963388370)   /* 2��ƽ�����ĵ��� */
#endif /* SQRT_2 */

/* ����Ҷ�任����,�������� */
#define FFTN(M)     (1L<<(M))

/************************************************************
 *                    FFT & IFFT
 */
void MATH_FFT (int x[], I8 m, I8 flag);  // ����ʵ���еĻ������ٸ���Ҷ�任.
void MATH_IFFT(int x[], I8 m);           // ���㹲��Գ�ʵ���еĻ������ٸ���Ҷ���任����任�����ʵ��.

/************************************************************
 *                    ���پ��
 */
void MATH_FastConv(int x[], I8 m, int y[], I16 n, I16 r);

/************************************************************
 *                    FIR�˲�
 */
void MATH_FIR(int data[], I16 m);

/************************************************************
 *                    ��ֵ����
 */
void  MATH_SincInterp(I16 sample[],I16 SampleN, I16 Interp[],I16 InterpN);  // �����ڲ庯��
float MATH_LagrInterp(int n, float t, float x[], float y[]);

/************************************************************
 *                    ����������[���Կ⺯��]
 */
// �ɱ����͵ıȽϺ���
int MATH_compareUp(const void *_key , const void *_base);    // ��������
int MATH_compareDown(const void *_key , const void *_base);  // ��������
// �¶���Ŀɱ����͵�������(Ĭ��Ϊ��������)
#define MATH_Qsort(base, n)      qsort(base,n,sizeof(I16), MATH_compareUp);
#define MATH_QsortUp(base, n)    qsort(base,n,sizeof(I16), MATH_compareUp);
#define MATH_QsortDown(base, n)  qsort(base,n,sizeof(I16), MATH_compareDown);
// Shell sort [ϣ������] 
void ShellSort(char *item, int count);

// Ѱ��һ�����������е�����[��С�������������]
void MATH_MostNum(I16 data[], int n, float mid, I16 *pLarge, I16 *pSmall);


/************************************************************
 *                    ���Ժ���
 */
void MATH_FFT_test(void);
void MATH_SincInterp_test(void);




#endif /*MATH__H_*/
