#ifndef FILEOPT_H_
#define FILEOPT_H_

#include <stdio.h>


/***********************************************************
 * 
 *                ÎÄ¼þ²Ù×÷
 */
size_t FILE_GetCharNumPerLineEq(FILE *fp);
void FILE_GetStringOneLineEq(FILE *fp, char *str, int len);
void FILE_GetStringOneLineEqEx(FILE *fp, char *str, int n, size_t len);
void FILE_GetTextEq(FILE *fp, char (*str)[80], int n, size_t len);


#endif /*FILEOPT_H_*/
