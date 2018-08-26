
#include "GUI_Protected.h"
#include "DSO_Private.h"
#include "LCD.h"
#include "MATH_.h"



/*********************************************************
 *                         正弦插值
 *
 *   函数说明：->I16 -- signed short;  TRIG_sin -- 定点正弦查表计算sin();
 *             ->所有计算过程全部为定点计算。
 *             ->只要满足 (SampleN-1)能被InterpN整除就能获得相当高的插值精确度。
 *             ->函数中的(<<8)是为了提高精确度而放大数据的。
 *             ->sample[m]*355 -- 355/226=?pi/2,补偿最后的sum* 226/355;
 *             ->sample[m]*TRIG_sin(angle)*226 /angle -- sample[m]*sin(angle)/angle
 *   author : lkh     date : 10/10/2011
 */
void MATH_SincInterp(I16 sample[],  // 待插值数据
					 I16 sampleN,   // 待插值数据点数
					 I16 Interp[],  // 插值后数据
					 I16 interpN)   // 插值后数据点数
{
	I16 i,m;
	I16 factor= interpN / (sampleN-1);  // 理论上(sampleN-1)应该被interpN整除
	int angle,sum;

	for(i=0; i<interpN; i++) {
		sum = 0.0;
		for(m=0; m<sampleN; m++) {
			angle = (m<<11) - (i<<11) / factor;  // angle = pi*(m-i*factor) * (2048/pi) 
			sum += (angle==0)? sample[m]*355 : sample[m]*TRIG_sin(angle)*226 /angle;
		}	                                     
		Interp[i] = sum / 355;  // sum再除以pi/2是因为正弦查表前被放大了pi/2 * 1024 ->... 
	}                              // ...-> 而且TRIG_sin(angle) /angle已经抵消了(*1024)
}
/*  函数原型 OK*
#include <math.h>
void MATH_SincInterp(I16 sample[],int sampleN, I16 Interp[], int interpN) {
	int i,m;
	float angle,sum;
	int factor= interpN / (sampleN-1);

	for(i=0; i<interpN; i++) {
		sum = 0.0;
		for(m=0; m<sampleN; m++) {
			angle = pi*(m-i/(float)factor);
			if(angle == 0)
				sum += sample[m];
			else
				sum += sin(angle) * sample[m] / angle;
		}
		Interp[i] = sum;
	}
}*/

/*********************************************************
 *          拉格朗日(三点)插值[俗称三次样条插值]
 *   函数返回一个双精度实型函数值，即插值点 t 处的函数近似值
 *   author : lkh     date : 10/13/2011
 */
float MATH_LagrInterp(int n,        // 给定结点的个数
					  float t,      // 指定插值点的值
					  float x[],    // 存放给定 n 个结点的值(从小到大)
					  float y[])    // 存放给定 n 个结点上的函数值
{
	int i,j,k,m;
	float z=0.0,s;
	if(n < 1)   /* 结点个数不对，返回 */
		return 0.0;
	if(n == 1)  /* 只有一个结点，取值返回 */
		return y[0];
	if(n == 2)  /* 只有两个节点，进行线性插值后返回 */
		return (y[0] * (t-x[1]) - y[1] * (t-x[0])) / (x[0]-x[1]);
	if(t <= x[1]) {  /* 取最前的三个结点 */
		k=0; m=2;
	} else if(t >= x[n-2]) {  /* 取中间的三个节点 */
		k= n-3; m= n-1; 
	} else {
		k=1; m=n;
		while((m-k) != 1) {
			i= (k+m) / 2;
			if(t < x[i-1])
				m=i;
			else
				k=i;
		}
		k--; m--;
		if(fabs(t-x[k]) < fabs(t-x[m]))
			k--;
		else
			m++;
	}
	z= 0.0;
	for(i=k; i<=m; i++) {  /* 进行三点二次插值 */
		s= 1.0;
		for(j=k; j<=m; j++) {
			if(j != i)
				s *= (t-x[j]) / (x[i]-x[j]);
			z += s*y[i];
		}
	}
	return z;
}

/*********************************************************
 *                    厄米特插值法
 *   函数返回一个双精度实型函数值，即插值点 t 处的函数近似值
 *   author : xxx     date : 10/13/2011
 */
float HermiteInterp(int n,       // 给定结点的个数
				 	float t,     // 指定插值点的值
				 	float x[],   // 存放给定 n 个结点的值(从小到大)
				 	float y[],   // 存放给定 n 个结点上的函数值
				 	float dy[])  // 存放给定 n 个结点上的一阶导数值
{
	int i,j;
	float p,q,s,z;
	
	z = 0.0;
	for(i=1; i<=n; i++)
	{
		s = 1.0;
		for(j=1; j<=n; j++)
			if(j != i) 
				s = s * (t - x[j-1]) / (x[i-1] - x[j-1]);
			s = s * s;
			p = 0.0;
			for(j=1; j<=n; j++)
				if(j != i) p = p + 1.0 / (x[i-1] - x[j-1]);
				q = y[i-1] + (t - x[i-1]) * (dy[i-1] - 2.0 * y[i-1] * p);
				z = z + q * s;          /* 进行累加 */
				
	}
	
	return (z);
	
}

/*********************************************************
 *           正弦插值测试函数
 */

#include "GUI.h"
#include <math.h>

#ifdef SampleN
#undef SampleN
#undef InterpN
#undef Nt
#undef f0
#undef fs
#endif

#define SampleN    (128+1)
#define InterpN    (512)
#define Nt         (6)
#define f0         (1024)
#define fs         ((SampleN-1) * (f0) / (Nt))


const I16 sample0[128+1] = {
	-255, -255, -255, -255, -255, -255, -255, -255, // 8
	-255, -255, -255, -255, -255, -255, -255, -255, // 8
	-255, -255, -255, -255, -255, -255, -255, -255, // 8
	-255, -255, -255, -255, -255, -255, -255, -255, // 8
	   0,    0,    0,    0,    0,    0,    0,    0, // 8
	   0,    0,    0,    0,    0,    0,    0,    0, // 8
	   0,    0,    0,    0,    0,    0,    0,    0, // 8
	   0,    0,    0,    0,    0,    0,    0,    0, // 8
	-255, -255, -255, -255, -255, -255, -255, -255, // 8
	-255, -255, -255, -255, -255, -255, -255, -255, // 8
	-255, -255, -255, -255, -255, -255, -255, -255, // 8
	-255, -255, -255, -255, -255, -255, -255, -255, // 8
	   0,    0,    0,    0,    0,    0,    0,    0, // 8
	   0,    0,    0,    0,    0,    0,    0,    0, // 8
	   0,    0,    0,    0,    0,    0,    0,    0, // 8
	   0,    0,    0,    0,    0,    0,    0,    0, // 8
	-255
};

static I16 sample[SampleN];
static I16 interp[InterpN];

void MATH_SincInterp_test(void) {
	int i;
	float t=0.0;

    for(i=0; i<SampleN ; i++, t+=1.0/fs)
		sample[i] = sample0[i] / 2 - rand()%8;
        //sample[i] = -(128+128*sin(2.*pi*f0*t)) - rand()%20*2;
		//sample[i] = - (128+128*sin(0.8*i)*cos(0.1*i));
		//sample[i] = rand()%255-255;
/*
	GUI_SetColor(GUI_YELLOW);
	WAVEWIN_DrawWave(sample,SampleN,50,300, InterpN);

	MATH_SincInterp(sample,SampleN,interp,InterpN);
	
//	MATH_QsortDown(sample,SampleN);
//	WAVEWIN_DrawWave(sample,SampleN,50,300, InterpN);

	GUI_SetColor(GUI_RED);
	WAVEWIN_DrawWave(interp,InterpN,50,300,InterpN);
//	MATH_QsortDown(interp,InterpN);
//	WAVEWIN_DrawWave(interp,InterpN,50,300,InterpN);
*/
}

/*********************************************************
 *           厄米特插值法测试函数
 */

void MATH_HermiteInterp_test(void) {


}