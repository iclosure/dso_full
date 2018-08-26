
#include "FILE.h"
#include <string.h>
#include <stdio.h>


/***********************************************************
 * 
 *             public code
 ***********************************************************
 */
size_t FILE_GetCharNumPerLineEq(FILE *fp) {
	char str[200];
	rewind(fp);
	if(!fscanf(fp,"%s",str))
		return 0;
	rewind(fp);
	return strlen(str)+2;
}

/***********************************************************
 * 
 *                 读取文件某一行内容
 *    注意：被操作的文件格式应该为: 每行字符字节数相同,且以'.'为一行的起始标志[不包括在字符串内],
 *         以‘\’为一行的结束符[也不包括在字符串内].
 */

void FILE_GetStringOneLineEq(FILE *fp,   // 文件名
				             char *str,  // 字符串保存位置
				             int len)    // 一行字符串的字节数
{
	if(fgetc(fp) == '.') {
		while((len--) && (fgetc(fp) != '\\')) {
				fseek(fp, -1, SEEK_CUR);
				*str++ = fgetc(fp);
		}
		*str= '\0';
	}
	
	fseek(fp, len-1, SEEK_CUR);    // 跳到下一行
}

/***********************************************************
 * 
 *                 读取文件某一行内容
 *    注意：被操作的文件格式应该为: 每行字符字节数相同,且以'.'为一行的起始标志[不包括在字符串内],
 *         以‘\’为一行的结束符[也不包括在字符串内].
 */

void FILE_GetStringOneLineEqEx(FILE *fp,   // 文件名
				               char *str,  // 字符串保存位置
				               int n,      // 读取从文件开头起第几行的字符串
							   size_t len) // 每行的字节数
{
	fseek(fp, len*n, SEEK_SET);
	FILE_GetStringOneLineEq(fp, str, len);
}

/***********************************************************
 * 
 *                 从某行起,读取文件的全部内容[限制性内容]
 *    注意：被操作的文件格式应该为: 每行字符字节数相同,且以'.'为一行的起始标志[不包括在字符串内],
 *         以‘\’为一行的结束符[也不包括在字符串内].
 */

void FILE_GetTextEq(FILE *fp,       // 文件名
				    char (*str)[80],  // 文本保存位置
				    int n,          // 读取从文件开头起第几行的字符串
				    size_t len)     // 每行的字节数
{
	int i=0;
	fseek(fp, len*n, SEEK_SET);
	while(!feof(fp))
		FILE_GetStringOneLineEq(fp, str[i++], len);
}
