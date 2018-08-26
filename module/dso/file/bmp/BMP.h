#ifndef BITMAP_H_
#define BITMAP_H_



/**********************************************************
 *
 *                    defined
 */

#define BI_RGB		    0L
#define BI_RLE8		    1L
#define BI_RLE4		    2L
#define BI_BITFIELDS	3L

#define WIDTHBYTES(i)    ((i+31)/32 * 4)

/**********************************************************
 *
 *                    Éú³ÉÒ»·ùBMPÍ¼
 */
void BMP_LCD0To24bpp(const char *file);




#endif /*BITMAP_H_*/
