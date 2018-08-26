
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
 *                 ��ȡ�ļ�ĳһ������
 *    ע�⣺���������ļ���ʽӦ��Ϊ: ÿ���ַ��ֽ�����ͬ,����'.'Ϊһ�е���ʼ��־[���������ַ�����],
 *         �ԡ�\��Ϊһ�еĽ�����[Ҳ���������ַ�����].
 */

void FILE_GetStringOneLineEq(FILE *fp,   // �ļ���
				             char *str,  // �ַ�������λ��
				             int len)    // һ���ַ������ֽ���
{
	if(fgetc(fp) == '.') {
		while((len--) && (fgetc(fp) != '\\')) {
				fseek(fp, -1, SEEK_CUR);
				*str++ = fgetc(fp);
		}
		*str= '\0';
	}
	
	fseek(fp, len-1, SEEK_CUR);    // ������һ��
}

/***********************************************************
 * 
 *                 ��ȡ�ļ�ĳһ������
 *    ע�⣺���������ļ���ʽӦ��Ϊ: ÿ���ַ��ֽ�����ͬ,����'.'Ϊһ�е���ʼ��־[���������ַ�����],
 *         �ԡ�\��Ϊһ�еĽ�����[Ҳ���������ַ�����].
 */

void FILE_GetStringOneLineEqEx(FILE *fp,   // �ļ���
				               char *str,  // �ַ�������λ��
				               int n,      // ��ȡ���ļ���ͷ��ڼ��е��ַ���
							   size_t len) // ÿ�е��ֽ���
{
	fseek(fp, len*n, SEEK_SET);
	FILE_GetStringOneLineEq(fp, str, len);
}

/***********************************************************
 * 
 *                 ��ĳ����,��ȡ�ļ���ȫ������[����������]
 *    ע�⣺���������ļ���ʽӦ��Ϊ: ÿ���ַ��ֽ�����ͬ,����'.'Ϊһ�е���ʼ��־[���������ַ�����],
 *         �ԡ�\��Ϊһ�еĽ�����[Ҳ���������ַ�����].
 */

void FILE_GetTextEq(FILE *fp,       // �ļ���
				    char (*str)[80],  // �ı�����λ��
				    int n,          // ��ȡ���ļ���ͷ��ڼ��е��ַ���
				    size_t len)     // ÿ�е��ֽ���
{
	int i=0;
	fseek(fp, len*n, SEEK_SET);
	while(!feof(fp))
		FILE_GetStringOneLineEq(fp, str[i++], len);
}
