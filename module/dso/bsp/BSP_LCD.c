/*
*********************************************************************************************************
*                                                uC/GUI
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
File        : LCDDummy.C
Purpose     : Empty driver
              This driver does no perform any function, but it can be
              used for 2 purposes:
              a) Satisfy all externals so an application can be
                compiled and linked in target hardware even if the
                driver is not already available
              b) Template for a starting point for a new driver.
----------------------------------------------------------------------   
Adapting to a new system (creating a new driver):
  In this case, the first step is to fill the routines 
  LCD_L0_GetPixelIndex, LCD_L0_SetPixelIndex and LCD_L0_Init with
  functionality, which is sufficient to make the hardware work.
  A second (optional) step would be to optimize higher level routines. 
----------------------------------------------------------------------   
Version-Date---Author-Explanation                                        
----------------------------------------------------------------------   
1.00.00 020417 JE     a) Changed to have only to adapt _GetPixelIndex
                         and _SetPixelIndex
0.90.00 020214 JE     a) First release
---------------------------END-OF-HEADER------------------------------
*/

#ifndef WIN32

#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIDebug.h"
#include "GUIType.h"
#include <stdio.h>
#include <string.h>
/* for linux framebuffer */

#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/types.h>

//###########################################
//#include <asm/page.h>
/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT		12
#define PAGE_SIZE		(1UL << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE-1))
//###########################################


typedef struct __FBDEV {
        int			   id;		           // 设备ID
        char	       fbname[20];   	   // LCD设备名
        U32			   offset;	           // framebuffer映射偏移量
        volatile U16   *pwfbmem;	       // framebuffer映射变量0，以双字节表示一个像素点
        volatile U8    *pbfbmem;	       // framebuffer映射变量0，以单字节表示一个像素点
		U16 			ScreenWidth;	   // 屏宽
		U16 			ScreenHeight;      // 屏高
	    U32 			screensize;		   // lCD屏幕物理尺寸(一个像素点用16位表示)
        struct fb_fix_screeninfo finfo;    // LCD 固定参数结构体*
        struct fb_var_screeninfo vinfo;    // LCD 可变s参数结构体 
} FBDEV, *pFBDEV;

// 全局液晶设备文件信息
FBDEV fbdev = {.fbname="/dev/fb0"};
//FBDEV fbdev = {.fbname="/dev/fb"};   // 在linux环境下仿真用


#if (LCD_CONTROLLER == -1) \
    && (!defined(WIN32) | defined(LCD_SIMCONTROLLER))

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#ifndef LCD_INIT_CONTROLLER
  #define LCD_INIT_CONTROLLER()
#endif

/*********************************************************************
*
*       Macros for MIRROR_, SWAP_ and LUT_
*/
#if (!defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) x
    #define LOG2PHYS_Y(x, y) y
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) y
    #define LOG2PHYS_Y(x, y) x
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) x
    #define LOG2PHYS_Y(x, y) LCD_YSIZE - 1 - (y)
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) y
    #define LOG2PHYS_Y(x, y) LCD_XSIZE - 1 - (x)
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) LCD_XSIZE - 1 - (x)
    #define LOG2PHYS_Y(x, y) y
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) LCD_YSIZE - 1 - (y)
    #define LOG2PHYS_Y(x, y) x
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) LCD_XSIZE - 1 - (x)
    #define LOG2PHYS_Y(x, y) LCD_YSIZE - 1 - (y)
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) LCD_YSIZE - 1 - (y)
    #define LOG2PHYS_Y(x, y) LCD_XSIZE - 1 - (x)
  #endif
#else
  #if   ( defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) x
    #define LOG2PHYS_Y(x, y) LCD__aLine2Com0[y]
  #elif (!defined (LCD_LUT_COM) &&  defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) LCD__aCol2Seg0[x]
    #define LOG2PHYS_Y(x, y) y
  #elif ( defined (LCD_LUT_COM) &&  defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) LCD__aCol2Seg0[x]
    #define LOG2PHYS_Y(x, y) LCD__aLine2Com0[y]
  #endif
#endif

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/

/*********************************************************************
*
*       Draw Bitmap 1 BPP
*/
static void  _DrawBitLine1BPP(int x, int y, U8 const GUI_UNI_PTR *p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX Index0 = *(pTrans+0);
  LCD_PIXELINDEX Index1 = *(pTrans+1);
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      do {
        LCD_L0_SetPixelIndex(x++, y, (*p & (0x80 >> Diff)) ? Index1 : Index0);
			  if (++Diff == 8) {
          Diff = 0;
				  p++;
			  }
		  } while (--xsize);
      break;
    case LCD_DRAWMODE_TRANS:
      do {
  		  if (*p & (0x80 >> Diff))
          LCD_L0_SetPixelIndex(x, y, Index1);
        x++;
			  if (++Diff == 8) {
          Diff = 0;
				  p++;
			  }
		  } while (--xsize);
      break;
    case LCD_DRAWMODE_XOR:;
      do {
  		  if (*p & (0x80 >> Diff)) {
          int Pixel = LCD_L0_GetPixelIndex(x, y);
          LCD_L0_SetPixelIndex(x, y, LCD_NUM_COLORS - 1 - Pixel);
        }
        x++;
			  if (++Diff == 8) {
          Diff = 0;
				  p++;
			  }
		  } while (--xsize);
      break;
	}
}

/*********************************************************************
*
*       Draw Bitmap 2 BPP
*/
#if (LCD_MAX_LOG_COLORS > 2)
static void  _DrawBitLine2BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
          LCD_L0_SetPixelIndex(x++, y, PixelIndex);
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          LCD_L0_SetPixelIndex(x++, y, Index);
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          if (Index) {
            LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
            LCD_L0_SetPixelIndex(x, y, PixelIndex);
          }
          x++;
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          if (Index) {
            LCD_L0_SetPixelIndex(x, y, Index);
          }
          x++;
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
  }
}
#endif

/*********************************************************************
*
*       Draw Bitmap 4 BPP
*/
#if (LCD_MAX_LOG_COLORS > 4)
static void  _DrawBitLine4BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
          LCD_L0_SetPixelIndex(x++, y, PixelIndex);
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          LCD_L0_SetPixelIndex(x++, y, Index);
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          if (Index) {
            LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
            LCD_L0_SetPixelIndex(x, y, PixelIndex);
          }
          x++;
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          if (Index) {
            LCD_L0_SetPixelIndex(x, y, Index);
          }
          x++;
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
  }
}
#endif

/*********************************************************************
*
*       Draw Bitmap 8 BPP
*/
#if (LCD_MAX_LOG_COLORS > 16)
static void  _DrawBitLine8BPP(int x, int y, U8 const GUI_UNI_PTR * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixel;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          LCD_L0_SetPixelIndex(x, y, *(pTrans + Pixel));
        }
      } else {
        for (; xsize > 0; xsize--, x++, p++) {
          LCD_L0_SetPixelIndex(x, y, *p);
        }
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          if (Pixel) {
            LCD_L0_SetPixelIndex(x, y, *(pTrans + Pixel));
          }
        }
      } else {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          if (Pixel) {
            LCD_L0_SetPixelIndex(x, y, Pixel);
          }
        }
      }
      break;
  }
}
#endif

/*********************************************************************
*
*       Draw Bitmap 16 BPP
*/
#if (LCD_BITSPERPIXEL > 8)
static void  DrawBitLine16BPP(int x, int y, U16 const GUI_UNI_PTR * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX pixel;
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) == 0) {
    if (pTrans) {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        LCD_L0_SetPixelIndex(x, y, *(pTrans + pixel));
      }
    } else {
      for (;xsize > 0; xsize--, x++, p++) {
        LCD_L0_SetPixelIndex(x, y, *p);
      }
    }
  } else {
    if (pTrans) {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          LCD_L0_SetPixelIndex(x, y, *(pTrans + pixel));
        }
      }
    } else {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          LCD_L0_SetPixelIndex(x, y, pixel);
        }
      }
    }
  }
}
#endif

/*********************************************************************
*
*       Exported functions
*
**********************************************************************
*/

/*********************************************************************
*
*       LCD_L0_SetPixelIndex
*
* Purpose:
*   Sets the index of the given pixel. The upper layers
*   calling this routine make sure that the coordinates are in range, so
*   that no check on the parameters needs to be performed.
*/

void LCD_L0_SetPixelIndex(int x, int y, int PixelIndex) {
  /* Convert logical into physical coordinates (Dep. on LCDConf.h) *
  #if LCD_SWAP_XY | LCD_MIRROR_X| LCD_MIRROR_Y
    int xPhys = LOG2PHYS_X(x, y);
    int yPhys = LOG2PHYS_Y(x, y);
  #else
    #define xPhys x
    #define yPhys y
  #endif
  */
  /* Write into hardware ... Adapt to your system */
  {
      /* ... */
	  //int offset;
	  //offset = (x + fbdev.vinfo.xres * y) + fbdev.offset;
	  //*(fbdev.pwfbmem + offset) = PixelIndex;
	  *(fbdev.pwfbmem + x + LCD_XSIZE * y) = PixelIndex;
	  
	  // 网上
	  //offset = (x + fbdev.vinfo.xoffset) * (fbdev.vinfo.bits_per_pixel >> 3) + (y+fbdev.vinfo.yoffset) * fbdev.finfo.line_length;
      //*(fbdev.pwfbmem + offset) = PixelIndex; /* 16bpp */

  }
}

/*********************************************************************
*
*       LCD_L0_GetPixelIndex
*
* Purpose:
*   Returns the index of the given pixel. The upper layers
*   calling this routine make sure that the coordinates are in range, so
*   that no check on the parameters needs to be performed.
*/
unsigned int LCD_L0_GetPixelIndex(int x, int y) {
  //LCD_PIXELINDEX PixelIndex;
  /* Convert logical into physical coordinates (Dep. on LCDConf.h) *
  #if LCD_SWAP_XY | LCD_MIRROR_X| LCD_MIRROR_Y
    int xPhys = LOG2PHYS_X(x, y);
    int yPhys = LOG2PHYS_Y(x, y);
  #else
    #define xPhys x
    #define yPhys y
  #endif */
  /* Read from hardware ... Adapt to your system */
  {
      //PixelIndex = 0; /* ... */
	  //int offset;
	  //offset = (x + fbdev.vinfo.xres * y) + fbdev.offset;
	  //return *(fbdev.pwfbmem + offset);  /* 16bpp */
	  return *(fbdev.pwfbmem + x + LCD_XSIZE * y);  /* 16bpp */
	  
	  //
	  //offset = (x + fbdev.vinfo.xoffset) * (fbdev.vinfo.bits_per_pixel >> 3) + (y+fbdev.vinfo.yoffset) * fbdev.finfo.line_length;
      //return *(fbdev.pFrameBuffer + offset); /* 16bpp */
  }
  
  //return PixelIndex;
}

/*********************************************************************
*
*       LCD_L0_XorPixel
*/
void LCD_L0_XorPixel(int x, int y) {
  LCD_PIXELINDEX PixelIndex = LCD_L0_GetPixelIndex(x, y);
  LCD_L0_SetPixelIndex(x, y, LCD_NUM_COLORS - PixelIndex - 1);
}

/*********************************************************************
*
*       LCD_L0_DrawHLine
*/
void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; x0 <= x1; x0++) {
      LCD_L0_XorPixel(x0, y);
    }
  } else {
    for (; x0 <= x1; x0++) {
      LCD_L0_SetPixelIndex(x0, y, LCD_COLORINDEX);
    }
  }
}

/*********************************************************************
*
*       LCD_L0_DrawVLine
*/
void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; y0 <= y1; y0++) {
      LCD_L0_XorPixel(x, y0);
    }
  } else {
    for (; y0 <= y1; y0++) {
      LCD_L0_SetPixelIndex(x, y0, LCD_COLORINDEX);
    }
  }
}

/*********************************************************************
*
*       LCD_L0_FillRect
*/
void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  for (; y0 <= y1; y0++) {
    LCD_L0_DrawHLine(x0, y0, x1);
  }
}

/*********************************************************************
*
*       LCD_L0_DrawBitmap
*/
void LCD_L0_DrawBitmap(int x0, int y0,
                       int xsize, int ysize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const U8 GUI_UNI_PTR * pData, int Diff,
                       const LCD_PIXELINDEX* pTrans)
{
  int i;
  /* Use _DrawBitLineXBPP */
  for (i=0; i<ysize; i++) {
    switch (BitsPerPixel) {
    case 1:
      _DrawBitLine1BPP(x0, i + y0, pData, Diff, xsize, pTrans);
      break;
    #if (LCD_MAX_LOG_COLORS > 2)
      case 2:
        _DrawBitLine2BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 4)
      case 4:
        _DrawBitLine4BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 16)
      case 8:
        _DrawBitLine8BPP(x0, i + y0, pData, xsize, pTrans);
        break;
    #endif
    #if (LCD_BITSPERPIXEL > 8)
      case 16:
        DrawBitLine16BPP(x0, i + y0, (const U16 *)pData, xsize, pTrans);
        break;
    #endif
    }
    pData += BytesPerLine;
  }
}

/*********************************************************************
*
*       LCD_L0_SetOrg
*/
void LCD_L0_SetOrg(int x, int y) {
  GUI_USE_PARA(x);
  GUI_USE_PARA(y);
}

/*********************************************************************
*
*       LCD_On / LCD_Off
*/
void LCD_On (void) {
#ifdef LCD_ON
  LCD_ON();
#endif
}

void LCD_Off (void) {
#ifdef LCD_OFF
  LCD_OFF();
#endif
}



/********************************************************
*          Name : fb_printinfo
*      Function : print LCD‘s basic info
*        Inputs : pfbdev -- 
*        Output : None
*   Description : None
*
*       Version : v1.0
*        Author : L.K.H.
*          date : 2011/04/08
********************************************************/
#include <stdio.h>
void fb_printinfo(void)
{
	// ###################
	// 打印fb_fix_screeninfo信息
	printf("id[16]=%x\n", fbdev.finfo.id);
	printf("smem_start=%d\n", fbdev.finfo.smem_start);
	printf("smem_len=%d\n", fbdev.finfo.smem_len);
	printf("type=%d\n", fbdev.finfo.type);
	printf("type_aux=%d\n", fbdev.finfo.type_aux);
	printf("visual=%d\n", fbdev.finfo.visual);
	printf("xpanstep=%d, ypanstep=%d\n", fbdev.finfo.xpanstep, fbdev.finfo.ypanstep);
	printf("line_length=%d\n", fbdev.finfo.line_length);
	printf("mmio_start=%d\n", fbdev.finfo.mmio_start);
	printf("mmio_len=%d\n", fbdev.finfo.mmio_len);
	printf("accel=%d\n", fbdev.finfo.accel);
	//printf("reserved=%s\n", fbdev.vinfo.reserved);
	// ###################

	// ###################
	// 打印fb_var_screeninfo信息
	printf("xres=%d, yres=%d\n", fbdev.vinfo.xres, fbdev.vinfo.yres);
	printf("xres_virtual=%d, yres_virtual=%d\n", fbdev.vinfo.xres_virtual, fbdev.vinfo.yres_virtual);
	printf("xoffset=%d, yoffset=%d\n", fbdev.vinfo.xoffset, fbdev.vinfo.yoffset);
	printf("bits_per_pixel=%d, grayscale=%d\n", fbdev.vinfo.bits_per_pixel, fbdev.vinfo.grayscale);
	printf(".red.offset=%d, .red.length=%d, .red.msb_right=%d\n", fbdev.vinfo.red.offset, fbdev.vinfo.red.length, fbdev.vinfo.red.msb_right);
	printf(".green.offset=%d, .green.length=%d, .green.msb_right=%d\n", fbdev.vinfo.green.offset, fbdev.vinfo.green.length, fbdev.vinfo.green.msb_right);
	printf(".blue.offset=%d, .blue.length=%d, .blue.msb_right=%d\n", fbdev.vinfo.blue.offset, fbdev.vinfo.blue.length, fbdev.vinfo.blue.msb_right);
	printf(".transp.offset=%d, .transp.length=%d, .transp.msb_right=%d\n", fbdev.vinfo.transp.offset, fbdev.vinfo.transp.length, fbdev.vinfo.transp.msb_right);
	printf("############################\n");
	printf("nonstd=%d\n", fbdev.vinfo.nonstd);
	printf("activate=%d\n", fbdev.vinfo.activate);
	printf("height=%d, width=%d\n", fbdev.vinfo.height,fbdev.vinfo.width);
	printf("accel_flags=%d\n", fbdev.vinfo.accel_flags);
	printf("pixclock=%d\n", fbdev.vinfo.pixclock);
	printf("left_margin=%d, right_margin=%d\n", fbdev.vinfo.left_margin,fbdev.vinfo.right_margin);
	printf("upper_margin=%d, lower_margin=%d\n", fbdev.vinfo.upper_margin,fbdev.vinfo.lower_margin);
	printf("hsync_len=%d, vsync_len=%d\n", fbdev.vinfo.hsync_len,fbdev.vinfo.vsync_len);
	printf("sync=%d\n", fbdev.vinfo.sync);
	printf("vmode=%d\n", fbdev.vinfo.vmode);
	printf("rotate=%d\n", fbdev.vinfo.rotate);
	//printf("reserved=%s\n", fbdev.vinfo.reserved);
	// ###################

	printf("screensize=%dx%d \n", fbdev.vinfo.xres,fbdev.vinfo.yres );
	printf("fbdev.offset=%d\n", fbdev.offset);
}

/*********************************************************************
*
*       LCD_L0_Init
*
* Purpose:
*   Initialises the LCD-controller.
*/
int  LCD_L0_Init(void) {
    //LCD_INIT_CONTROLLER();
	fbdev.id = open(fbdev.fbname, O_RDWR);

    if(fbdev.id < 0)
    {
		printf("Error: opening %s: %d. Check kernel config\n", fbdev.fbname,fbdev.id);
		close(fbdev.id);
        return -1;
	}

    if (-1 == ioctl(fbdev.id,FBIOGET_VSCREENINFO,&(fbdev.vinfo)))
	{
		printf("ioctl FBIOGET_VSCREENINFO\n");
		close(fbdev.id);
		return -1;
	}

    if (-1 == ioctl(fbdev.id,FBIOGET_FSCREENINFO,&(fbdev.finfo)))
	{
		printf("ioctl FBIOGET_FSCREENINFO\n");
		close(fbdev.id);
	 	return -1;
	}

	/* set screensiez >: lCD屏幕物理尺寸(一个像素点用16位表示) */
	fbdev.screensize = fbdev.vinfo.xres*fbdev.vinfo.yres;  //*fbdev.vinfo.bits_per_pixel/8;
	fbdev.ScreenWidth  = fbdev.vinfo.xres;
	fbdev.ScreenHeight = fbdev.vinfo.yres;

	// map physics address to virtual address
	// fbdev.finfo.smem_start=f0000000
	fbdev.offset = (U32)(fbdev.finfo.smem_start) & (~PAGE_MASK);

	fbdev.pbfbmem= mmap(NULL, fbdev.finfo.smem_len + fbdev.offset,
			PROT_READ | PROT_WRITE, MAP_SHARED, fbdev.id, 0);
	fbdev.pwfbmem = (U16 *)fbdev.pbfbmem; 
	
	//fb_printinfo();

	return 0;
}

/*********************************************************************
*
*       LCD_DispFullBitmap
*/

void LCD_DispFullBitmap(const char *pBitmap)
{
	memcpy((char *)fbdev.pbfbmem, (char *)pBitmap, LCD_XSIZE*LCD_YSIZE<<1);
}

/*********************************************************************
*
*       LCD_L0_GetDevFunc   [用户添加：匹配3.98不报错]
*/
void * LCD_L0_GetDevFunc(int Index) {
  GUI_USE_PARA(Index);
  return NULL;
}


/*********************************************************************
*
*       LCD_L0_SetLUTEntry
*/
void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR Color) {
  GUI_USE_PARA(Pos);
  GUI_USE_PARA(Color);
}

#else

void LCDDummy_c(void) { } /* avoid empty object files */

#endif /* (LCD_CONTROLLER undefined) */

#endif /* #ifndef WIN32 */
