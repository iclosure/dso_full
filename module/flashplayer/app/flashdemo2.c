
//#include 
//#include
//#include
#include "GUI.h" 
#include "GUI_Private.h" 
#include "player.h"
#include "image.h" 

ddPlayer * dd_player ; 
ddImage * dd_image ;
FILE *flashfp;

void GUI_DrawImageRGBA(U8* pdata,int x0,int y0) 
{ 
	int i,j,width,height;
	U8 aa,bb,rr,gg;
	
	width = ddImage_getWidth(dd_image);
	height = ddImage_getHeight(dd_image);
	for( i = 0; i < height; i++) 
	{ 
		for( j = 0; j < width; j++) 
		{ 
			rr = *pdata++;
			gg = *pdata++;
			bb= *pdata++; 
			aa = *pdata++; 
			// alpha LCD_SetAlphaEx(aa,0);
			LCD_SetColor(rr | (gg << 8) | (U32)((U32)bb << 16)); LCD_DrawPixel(x0+j, y0+i); 
		} 
	} 
} 

void GUI_LoadFlash(char *filename) 
{ 
	flashfp = fopen(filename, "rb") ; 
	if(flashfp != NULL) 
	{
		dd_image = dd_newImage(176, 240) ;
		dd_player = dd_newPlayer_file(flashfp, dd_image) ;
		ddPlayer_readMovie(dd_player) ;
	} 
}

void GUI_ReleasFlash() 
{ 
	dd_destroyPlayer(dd_player) ;
	dd_destroyImage(dd_image) ;
	fclose(flashfp) ; 
} 

void GUI_FlashPlay(int x0,int y0) 
{
	ddPlayer_step(dd_player) ; 
	while(ddPlayer_executeFrameActions(dd_player, STEP_FRAME)) ; 
	ddPlayer_updateDisplay(dd_player, NULL, NULL) ;
	GUI_DrawImageRGBA((U8*)(ddImage_getData(dd_image)), x0, y0) ;
} 

void GUI_FLASH_Draw(int x0,int y0)
{ 
	// GUI_LoadFlash(); 
	while(1) {
		GUI_FlashPlay(x0,y0);
		GUI_Exec();
		GUI_Delay(10);
	}
}