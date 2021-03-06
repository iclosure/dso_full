/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*
* C-file generated by
*
*        �C/GUI-BitmapConvert V3.96.
*        Compiled Jul 19 2005, 13:50:35
*          (c) 2002-2005  Micrium, Inc.
  www.micrium.com

  (c) 1998-2005  Segger
  Microcontroller Systeme GmbH
  www.segger.com
*
**********************************************************************
*
* Source file: button_mean
* Dimensions:  40 * 40
* NumColors:   0
*
**********************************************************************
*/

#include "stdlib.h"

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif


static GUI_CONST_STORAGE unsigned char acbutton_mean[] = {
  /* RLE: 099 Pixels @ 000,000*/ 99, 0x00, 0x00, 
  /* RLE: 001 Pixels @ 019,002*/ 1, 0x00, 0x00, 
  /* RLE: 005 Pixels @ 020,002*/ 5, 0x00, 0x00, 
  /* ABS: 002 Pixels @ 025,002*/ 0, 2, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 009 Pixels @ 027,002*/ 9, 0x00, 0x00, 
  /* RLE: 001 Pixels @ 036,002*/ 1, 0x00, 0x00, 
  /* RLE: 021 Pixels @ 037,002*/ 21, 0x00, 0x00, 
  /* ABS: 002 Pixels @ 018,003*/ 0, 2, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 006 Pixels @ 020,003*/ 6, 0x00, 0x00, 
  /* RLE: 003 Pixels @ 026,003*/ 3, 0x00, 0x00, 
  /* RLE: 006 Pixels @ 029,003*/ 6, 0x00, 0x00, 
  /* RLE: 001 Pixels @ 035,003*/ 1, 0x00, 0x00, 
  /* RLE: 022 Pixels @ 036,003*/ 22, 0x00, 0x00, 
  /* ABS: 010 Pixels @ 018,004*/ 0, 10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB, 0x5A, 0x34, 0xA5, 0x55, 0xAD, 0xB2, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 009 Pixels @ 028,004*/ 9, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 037,004*/ 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 019 Pixels @ 000,005*/ 19, 0x00, 0x00, 
  /* ABS: 008 Pixels @ 019,005*/ 0, 8, 0x00, 0x00, 0xEB, 0x5A, 0xFF, 0xFF, 0x9E, 0xF7, 0x5D, 0xEF, 0xFF, 0xFF, 0x55, 0xAD, 0x00, 0x00, 
  /* RLE: 007 Pixels @ 027,005*/ 7, 0x00, 0x00, 
  /* ABS: 002 Pixels @ 034,005*/ 0, 2, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 021 Pixels @ 036,005*/ 21, 0x00, 0x00, 
  /* ABS: 010 Pixels @ 017,006*/ 0, 10, 0x00, 0x00, 0x00, 0x00, 0x41, 0x08, 0xFF, 0xFF, 0xF7, 0xBD, 0x20, 0x00, 0x00, 0x00, 0x4D, 0x6B, 0xFF, 0xFF, 0x96, 0xB5, 
  /* RLE: 008 Pixels @ 027,006*/ 8, 0x00, 0x00, 
  /* ABS: 004 Pixels @ 035,006*/ 0, 4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 020 Pixels @ 039,006*/ 20, 0x00, 0x00, 
  /* ABS: 009 Pixels @ 019,007*/ 0, 9, 0x41, 0x08, 0xFF, 0xFF, 0xEB, 0x5A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8E, 0x73, 0xFF, 0xFF, 0x1C, 0xE7, 
  /* RLE: 005 Pixels @ 028,007*/ 5, 0xDB, 0xDE, 
  /* ABS: 002 Pixels @ 033,007*/ 0, 2, 0x79, 0xCE, 0x75, 0xAD, 
  /* RLE: 024 Pixels @ 035,007*/ 24, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 019,008*/ 0, 3, 0x41, 0x08, 0xFF, 0xFF, 0x6D, 0x6B, 
  /* RLE: 004 Pixels @ 022,008*/ 4, 0x00, 0x00, 
  /* ABS: 009 Pixels @ 026,008*/ 0, 9, 0x4D, 0x6B, 0xD7, 0xBD, 0xD7, 0xBD, 0xD7, 0xBD, 0xD7, 0xBD, 0xD7, 0xBD, 0xD7, 0xBD, 0x5D, 0xEF, 0xDF, 0xFF, 
  /* RLE: 024 Pixels @ 035,008*/ 24, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 019,009*/ 0, 3, 0x41, 0x08, 0xFF, 0xFF, 0x6D, 0x6B, 
  /* RLE: 011 Pixels @ 022,009*/ 11, 0x00, 0x00, 
  /* ABS: 002 Pixels @ 033,009*/ 0, 2, 0x30, 0x84, 0xFF, 0xFF, 
  /* RLE: 024 Pixels @ 035,009*/ 24, 0x00, 0x00, 
  /* ABS: 007 Pixels @ 019,010*/ 0, 7, 0x41, 0x08, 0xFF, 0xFF, 0x6D, 0x6B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 004 Pixels @ 026,010*/ 4, 0x00, 0x00, 
  /* ABS: 005 Pixels @ 030,010*/ 0, 5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x8C, 0xFF, 0xFF, 
  /* RLE: 024 Pixels @ 035,010*/ 24, 0x00, 0x00, 
  /* ABS: 016 Pixels @ 019,011*/ 0, 16, 0x41, 0x08, 0xFF, 0xFF, 0x6D, 0x6B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x8C, 0xFF, 0xFF, 
  /* RLE: 024 Pixels @ 035,011*/ 24, 0x00, 0x00, 
  /* ABS: 016 Pixels @ 019,012*/ 0, 16, 0x41, 0x08, 0xFF, 0xFF, 0x6D, 0x6B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x8C, 0xFF, 0xFF, 
  /* RLE: 007 Pixels @ 035,012*/ 7, 0x00, 0x00, 
  /* RLE: 001 Pixels @ 002,013*/ 1, 0x00, 0x00, 
  /* RLE: 006 Pixels @ 003,013*/ 6, 0x00, 0x00, 
  /* RLE: 001 Pixels @ 009,013*/ 1, 0x00, 0x00, 
  /* RLE: 009 Pixels @ 010,013*/ 9, 0x00, 0x00, 
  /* ABS: 032 Pixels @ 019,013*/ 0, 32, 0x41, 0x08, 0xFF, 0xFF, 0x6D, 0x6B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x8C, 0xFF, 0xFF, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 008 Pixels @ 011,014*/ 8, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 019,014*/ 0, 3, 0x41, 0x08, 0xFF, 0xFF, 0x4D, 0x6B, 
  /* RLE: 005 Pixels @ 022,014*/ 5, 0x00, 0x00, 
  /* RLE: 001 Pixels @ 027,014*/ 1, 0x00, 0x00, 
  /* RLE: 005 Pixels @ 028,014*/ 5, 0x00, 0x00, 
  /* ABS: 048 Pixels @ 033,014*/ 0, 48, 0x72, 0x8C, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x81, 0x28, 0x42, 0x59, 0x22, 0x59, 0x40, 0x10, 0x20, 0x08, 0x22, 0x59, 0x22, 0x59, 0xA1, 0x28, 0x40, 0x00, 0x14, 0xF7, 0xAA, 0x9B, 0xE2, 0x38, 0x00, 0x00, 0xC1, 0x38, 0x22, 0x51, 0x22, 0x51, 0x00, 0x00, 0x81, 0x20, 0x42, 0x59, 
        0x22, 0x59, 0x40, 0x18, 0x20, 0x00, 0x6C, 0xB4, 0xF3, 0xF6, 0xA1, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 004 Pixels @ 001,016*/ 4, 0x00, 0x00, 
  /* ABS: 085 Pixels @ 005,016*/ 0, 85, 0x20, 0x18, 0xA0, 0x8A, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA5, 0x72, 0xAC, 0xF5, 0x8C, 0xFD, 0x43, 0x39, 0xC1, 0x20, 0x8B, 0xF5, 0xAB, 0xF5, 0xE6, 0x82, 0x00, 0x00, 0xE6, 0xBB, 0xE9, 0xDC, 
        0x49, 0xBC, 0x00, 0x00, 0xE8, 0xAB, 0x8B, 0xED, 0x4B, 0xE5, 0x00, 0x00, 0x65, 0x62, 0xAB, 0xFD, 0xAB, 0xF5, 0x63, 0x39, 0xA1, 0x20, 0xE9, 0xE4, 0x88, 0xD4, 0x26, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x20, 0x08, 0xA5, 0xB3, 0xE0, 0xFC, 0xE6, 0xBB, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x61, 0x20, 0xC1, 0x48, 0xC1, 0x48, 0x20, 0x10, 0x20, 0x08, 0xC1, 0x48, 0xC1, 0x40, 0x60, 0x20, 0x40, 0x00, 0x76, 0xF7, 0x8A, 0x93, 
        0x81, 0x28, 0x00, 0x00, 0x81, 0x30, 0xC1, 0x40, 0xC1, 0x40, 0x00, 0x00, 0x40, 0x18, 0xC1, 0x48, 0xC2, 0x48, 0x20, 0x10, 0x00, 0x00, 0x6D, 0xAC, 0x35, 0xFF, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x41, 0x08, 0xA2, 0xD3, 0xA0, 0xFC, 0x20, 0xFC, 0x80, 0xFC, 0xC2, 0xDB, 0x82, 0x10, 
  /* RLE: 009 Pixels @ 010,018*/ 9, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 019,018*/ 0, 3, 0x41, 0x08, 0xFF, 0xFF, 0x4D, 0x6B, 
  /* RLE: 005 Pixels @ 022,018*/ 5, 0x00, 0x00, 
  /* RLE: 001 Pixels @ 027,018*/ 1, 0x00, 0x00, 
  /* RLE: 005 Pixels @ 028,018*/ 5, 0x00, 0x00, 
  /* ABS: 018 Pixels @ 033,018*/ 0, 18, 0x72, 0x8C, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x08, 0x88, 0x9B, 0xA9, 0xDC, 0x25, 0xDC, 0x40, 0xFC, 0x25, 0xDC, 0xA9, 0xD4, 0xC8, 0xAB, 
        0x40, 0x08, 
  /* RLE: 008 Pixels @ 011,019*/ 8, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 019,019*/ 0, 3, 0x41, 0x08, 0xFF, 0xFF, 0x6D, 0x6B, 
  /* RLE: 008 Pixels @ 022,019*/ 8, 0x00, 0x00, 
  /* ABS: 005 Pixels @ 030,019*/ 0, 5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x8C, 0xFF, 0xFF, 
  /* RLE: 005 Pixels @ 035,019*/ 5, 0x00, 0x00, 
  /* ABS: 011 Pixels @ 000,020*/ 0, 11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x30, 0x20, 0x18, 0xE1, 0x48, 0xC0, 0xFC, 0x20, 0x51, 0x20, 0x18, 0x60, 0x30, 0x00, 0x00, 
  /* RLE: 008 Pixels @ 011,020*/ 8, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 019,020*/ 0, 3, 0x41, 0x08, 0xFF, 0xFF, 0x6D, 0x6B, 
  /* RLE: 011 Pixels @ 022,020*/ 11, 0x00, 0x00, 
  /* ABS: 002 Pixels @ 033,020*/ 0, 2, 0x71, 0x8C, 0xFF, 0xFF, 
  /* RLE: 006 Pixels @ 035,020*/ 6, 0x00, 0x00, 
  /* ABS: 011 Pixels @ 001,021*/ 0, 11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x28, 0xC0, 0xFC, 0xE0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 007 Pixels @ 012,021*/ 7, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 019,021*/ 0, 3, 0x41, 0x08, 0xFF, 0xFF, 0x6D, 0x6B, 
  /* RLE: 011 Pixels @ 022,021*/ 11, 0x00, 0x00, 
  /* ABS: 002 Pixels @ 033,021*/ 0, 2, 0x71, 0x8C, 0xFF, 0xFF, 
  /* RLE: 005 Pixels @ 035,021*/ 5, 0x00, 0x00, 
  /* ABS: 012 Pixels @ 000,022*/ 0, 12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x28, 0xC0, 0xFC, 0x00, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 007 Pixels @ 012,022*/ 7, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 019,022*/ 0, 3, 0x41, 0x08, 0xFF, 0xFF, 0x6D, 0x6B, 
  /* RLE: 011 Pixels @ 022,022*/ 11, 0x00, 0x00, 
  /* ABS: 002 Pixels @ 033,022*/ 0, 2, 0x71, 0x8C, 0xFF, 0xFF, 
  /* RLE: 005 Pixels @ 035,022*/ 5, 0x00, 0x00, 
  /* ABS: 011 Pixels @ 000,023*/ 0, 11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x28, 0xC0, 0xFC, 0xE0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 008 Pixels @ 011,023*/ 8, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 019,023*/ 0, 3, 0x41, 0x08, 0xFF, 0xFF, 0x6D, 0x6B, 
  /* RLE: 011 Pixels @ 022,023*/ 11, 0x00, 0x00, 
  /* ABS: 002 Pixels @ 033,023*/ 0, 2, 0x71, 0x8C, 0xFF, 0xFF, 
  /* RLE: 005 Pixels @ 035,023*/ 5, 0x00, 0x00, 
  /* ABS: 015 Pixels @ 000,024*/ 0, 15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x28, 0xC0, 0xFC, 0xE0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x08, 0x82, 0x10, 0x82, 0x10, 0x61, 0x08, 
  /* RLE: 004 Pixels @ 015,024*/ 4, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 019,024*/ 0, 3, 0x41, 0x08, 0xFF, 0xFF, 0x6D, 0x6B, 
  /* RLE: 011 Pixels @ 022,024*/ 11, 0x00, 0x00, 
  /* ABS: 005 Pixels @ 033,024*/ 0, 5, 0x71, 0x8C, 0xFF, 0xFF, 0x82, 0x10, 0x61, 0x08, 0x00, 0x00, 
  /* RLE: 007 Pixels @ 038,024*/ 7, 0x00, 0x00, 
  /* ABS: 017 Pixels @ 005,025*/ 0, 17, 0xC0, 0x28, 0xC0, 0xFC, 0x00, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x8C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x08, 0xFF, 0xFF, 0x4D, 0x6B, 
  /* RLE: 006 Pixels @ 022,025*/ 6, 0x00, 0x00, 
  /* ABS: 010 Pixels @ 028,025*/ 0, 10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB2, 0x94, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x61, 0x08, 
  /* RLE: 007 Pixels @ 038,025*/ 7, 0x00, 0x00, 
  /* ABS: 017 Pixels @ 005,026*/ 0, 17, 0xC0, 0x28, 0xE0, 0xFC, 0xE0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86, 0x31, 0x0C, 0x63, 0x0C, 0x63, 0x9A, 0xD6, 0xFF, 0xFF, 0x28, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x8E, 0x73, 
  /* RLE: 006 Pixels @ 022,026*/ 6, 0x00, 0x00, 
  /* ABS: 010 Pixels @ 028,026*/ 0, 10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA6, 0x31, 0xEB, 0x5A, 0x0C, 0x63, 0xEB, 0x5A, 0x20, 0x00, 
  /* RLE: 007 Pixels @ 038,026*/ 7, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 005,027*/ 0, 3, 0xC0, 0x28, 0xE0, 0xFC, 0xE0, 0x38, 
  /* RLE: 006 Pixels @ 008,027*/ 6, 0x00, 0x00, 
  /* ABS: 008 Pixels @ 014,027*/ 0, 8, 0x61, 0x08, 0xDB, 0xDE, 0xFF, 0xFF, 0x69, 0x4A, 0x86, 0x31, 0xB6, 0xB5, 0xFF, 0xFF, 0xAA, 0x52, 
  /* RLE: 006 Pixels @ 022,027*/ 6, 0x00, 0x00, 
  /* RLE: 001 Pixels @ 028,027*/ 1, 0x00, 0x00, 
  /* RLE: 016 Pixels @ 029,027*/ 16, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 005,028*/ 0, 3, 0xC0, 0x28, 0xC0, 0xFC, 0x00, 0x39, 
  /* RLE: 005 Pixels @ 008,028*/ 5, 0x00, 0x00, 
  /* ABS: 010 Pixels @ 013,028*/ 0, 10, 0x00, 0x00, 0x00, 0x00, 0x82, 0x10, 0xBA, 0xD6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEB, 0x5A, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 007 Pixels @ 023,028*/ 7, 0x00, 0x00, 
  /* RLE: 003 Pixels @ 030,028*/ 3, 0x00, 0x00, 
  /* ABS: 007 Pixels @ 033,028*/ 0, 7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 005 Pixels @ 000,029*/ 5, 0x00, 0x00, 
  /* ABS: 017 Pixels @ 005,029*/ 0, 17, 0xC0, 0x28, 0xC0, 0xFC, 0x00, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x10, 0xA6, 0x31, 0xA6, 0x31, 0x86, 0x31, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 006 Pixels @ 022,029*/ 6, 0x00, 0x00, 
  /* RLE: 001 Pixels @ 028,029*/ 1, 0x00, 0x00, 
  /* RLE: 004 Pixels @ 029,029*/ 4, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 033,029*/ 0, 3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 005 Pixels @ 036,029*/ 5, 0x00, 0x00, 
  /* ABS: 013 Pixels @ 001,030*/ 0, 13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x28, 0xC0, 0xFC, 0x00, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 014 Pixels @ 014,030*/ 14, 0x00, 0x00, 
  /* RLE: 001 Pixels @ 028,030*/ 1, 0x00, 0x00, 
  /* RLE: 011 Pixels @ 029,030*/ 11, 0x00, 0x00, 
  /* ABS: 011 Pixels @ 000,031*/ 0, 11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x28, 0xC0, 0xFC, 0xE0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 029 Pixels @ 011,031*/ 29, 0x00, 0x00, 
  /* ABS: 012 Pixels @ 000,032*/ 0, 12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x28, 0xC0, 0xFC, 0xE0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 028 Pixels @ 012,032*/ 28, 0x00, 0x00, 
  /* ABS: 012 Pixels @ 000,033*/ 0, 12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x28, 0xC0, 0xFC, 0xE0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 028 Pixels @ 012,033*/ 28, 0x00, 0x00, 
  /* RLE: 001 Pixels @ 000,034*/ 1, 0x00, 0x00, 
  /* RLE: 004 Pixels @ 001,034*/ 4, 0x00, 0x00, 
  /* ABS: 003 Pixels @ 005,034*/ 0, 3, 0x60, 0x20, 0xE0, 0xFC, 0xA0, 0x30, 
  /* RLE: 032 Pixels @ 008,034*/ 32, 0x00, 0x00, 
  /* ABS: 011 Pixels @ 000,035*/ 0, 11, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0xC3, 0x69, 0xC4, 0x61, 0x43, 0x8A, 0xA0, 0xFC, 0x62, 0x8A, 0xC4, 0x61, 0xC4, 0x69, 0x20, 0x08, 
  /* RLE: 031 Pixels @ 011,035*/ 31, 0x00, 0x00, 
  /* ABS: 009 Pixels @ 002,036*/ 0, 9, 0x40, 0x08, 0xAA, 0xD4, 0xEA, 0xDC, 0xC9, 0xDC, 0x46, 0xDC, 0xC9, 0xD4, 0xEA, 0xDC, 0xEA, 0xDC, 0x61, 0x10, 
  /* RLE: 029 Pixels @ 011,036*/ 29, 0x00, 0x00, 
  /* ABS: 012 Pixels @ 000,037*/ 0, 12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x28, 0x20, 0x28, 0x40, 0x28, 0x41, 0x20, 0x41, 0x28, 0x40, 0x28, 0x40, 0x28, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 028 Pixels @ 012,037*/ 28, 0x00, 0x00, 
  /* ABS: 012 Pixels @ 000,038*/ 0, 12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 028 Pixels @ 012,038*/ 28, 0x00, 0x00, 
  /* ABS: 012 Pixels @ 000,039*/ 0, 12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  /* RLE: 028 Pixels @ 012,039*/ 28, 0x00, 0x00, 


  0};  /* 910 for 1600 pixels */

GUI_CONST_STORAGE GUI_BITMAP bmbutton_mean = {
  40, /* XSize */
  40, /* YSize */
  80, /* BytesPerLine */
  16, /* BitsPerPixel */
  (unsigned char *)acbutton_mean,  /* Pointer to picture data */
  NULL  /* Pointer to palette */
 ,GUI_DRAW_RLEM16
};

/* *** End of file *** */
