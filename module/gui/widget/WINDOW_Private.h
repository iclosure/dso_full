/*
*********************************************************************************************************
*                                             uC/GUI V3.98
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
File        : WINDOW_Private.h
Purpose     : WINDOW private header file
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef WINDOW_PRIVATE_H
#define WINDOW_PRIVATE_H

#include "WM.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Externals
*
**********************************************************************
*/

extern GUI_COLOR WINDOW__DefaultBkColor;

// 说明：此声明为用户L.K.H.添加
WM_HWIN WINDOW_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);



#endif   /* GUI_WINSUPPORT */
#endif   /* WINDOW_PRIVATE_H */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
