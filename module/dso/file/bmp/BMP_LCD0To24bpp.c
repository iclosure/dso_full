
#include "BMPType.h"
#include "LCDConf.h"
#include "LCD.h"
#include "BMP.h"
#include <stdlib.h>
#include <stdio.h>


// 将16位色转换为24位色
RGBQUAD bpp16To24(U16 color16)
{
	RGBQUAD rgb;

	rgb.R = (color16 & 0xF800) >> 8; 
	rgb.G = (color16 & 0x07E0) >> 3;
	rgb.B = (color16 & 0x001F) << 3;
	rgb.Res= 0;

	return rgb;
}
/************************************************************
 *
 *                      publuc code
 *   参数说明：file可包含路径，...
 */
void BMP_LCD0To24bpp(const char *file) {
	BMPHEADER header;
	// 初始化位图头信息
	// ++++++++++++++++++++++++++++++++++++
	header.bfType			= 'B' | ('M'<<8);
    header.bfSize			= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + LCD_XSIZE*LCD_YSIZE*3;
    header.bfReserved1		= 0;
    header.bfReserved2		= 0;
    header.bfOffBits		= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	// ++++++++++++++++++++++++++++++++++++
    header.biSize			= sizeof(BITMAPINFOHEADER);
    header.biWidth		    = LCD_XSIZE;
    header.biHeight		    = - LCD_YSIZE;
    header.biPlanes		    = 1;
    header.biBitCount		= 24;  // 24bpp  //@@
    header.biCompression	= BI_RGB;
    header.biSizeImage		= header.bfSize*2;
    header.biXPelsPerMeter	= 0;
    header.biYPelsPerMeter	= 0;
    header.biClrUsed		= 0;
    header.biClrImportant	= 0;
	// ++++++++++++++++++++++++++++++++++++
	{
		FILE *fp;
		U16 x, y;
		char str[20];  // 
		I8 cnt=5;
		sprintf(str, "%s%s", file, ".bmp");
		// 创建一幅BMP图
		while(cnt--) {
			fp= fopen(str, "wb");
			if(fp > 0) break;
		}
		// 拷贝信息到BMP图
		fwrite(&header, sizeof(BMPHEADER), 1, fp);
		for(y=0; y<LCD_YSIZE; y++) {
			for(x=0; x<LCD_XSIZE; x++) {
				/*// simple
				putc((LCD0[y][x]&0x001F)<<3, fp); // B
				putc((LCD0[y][x]&0x07E0)>>3, fp); // G
				putc((LCD0[y][x]&0xF800)>>8, fp); // R*/
			}
		}

		fclose(fp);
	}
}
