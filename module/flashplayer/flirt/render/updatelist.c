/*
 Flirt, an SWF rendering library
 Copyright (c) 2004-2006 Dave Hayden <dave@opaque.net>
 All rights reserved.
 
 http://www.opaque.net/flirt/

 This code is distributed under the two-clause BSD license.
 Read the LICENSE file or visit the URL above for details
*/

#include "updatelist.h"

ddUpdateList*
dd_newUpdateList()
{
	ddUpdateList* list_p = (ddUpdateList *)(dd_malloc(sizeof(ddUpdateList)));
	list_p->nAlloced = 0;
	list_p->nRects = 0;
	list_p->rects = NULL;
	return list_p;
}


void
dd_destroyUpdateList(ddUpdateList* list_p)
{
	if ( list_p->rects != NULL )
		dd_free(list_p->rects);
	
	dd_free(list_p);
}


void
ddUpdateList_clear(ddUpdateList* list_p)
{
	list_p->nRects = 0;
}


void
ddUpdateList_constrainToRect(ddUpdateList* list_p, ddRect bounds)
{
	int i, j;

	for ( i = 0, j = 0; i < list_p->nRects; ++i )
	{
		if ( ddRect_intersectsRect(list_p->rects[i], bounds) )
		{
			list_p->rects[j] = ddRect_intersectRect(list_p->rects[i], bounds);
			++j;
		}
	}

	list_p->nRects = j;
}


#ifdef DD_RENDER_TOPDOWN

void
ddUpdateList_fillImageBackground(ddUpdateList* list_p,
								 ddImage* image, ddColor background)
{
	int i;

	for ( i = 0; i < list_p->nRects; ++i )
		ddImage_blendRect(image, list_p->rects[i], background);
}

#endif /* DD_RENDER_TOPDOWN */


int
ddUpdateList_intersectsRect(ddUpdateList* list_p, ddRect rect)
{
	int i;

	for ( i = 0; i < list_p->nRects; ++i )
	{
		if ( ddRect_intersectsRect(rect, list_p->rects[i]) )
			return 1;
	}

	return 0;
}


void
ddUpdateList_makeIntegerRects(ddUpdateList* list_p)
{
	int i;

	for ( i = 0; i < list_p->nRects; ++i )
		list_p->rects[i] = ddRect_integerRect(list_p->rects[i]);
}


#define UPDATELIST_INCREMENT 4

/*
 if new rect is cut fully across either dimension by an existing rect,
 we can include just the difference
 */

void
ddUpdateList_includeRect(ddUpdateList* list_p, ddRect rect)
{
	int i;
	int j;
	
	if ( !RECT_VALID(rect) )
		return;

	for ( i = 0; i < list_p->nRects; ++i )
	{
		ddRect hit = list_p->rects[i];

		if ( ddRect_intersectsRect(rect, hit) )
		{
			hit = ddRect_containRect(hit, rect);

			for ( j = i + 1; j < list_p->nRects; ++j )
			{
				if ( ddRect_intersectsRect(hit, list_p->rects[j]) )
				{
					hit = ddRect_containRect(hit, list_p->rects[j]);
					list_p->rects[j] = ddInvalidRect;
				}
			}

			list_p->rects[i] = hit;

			return;
		}
	}

	if ( list_p->nRects == list_p->nAlloced )
	{
		list_p->nAlloced += UPDATELIST_INCREMENT;
		list_p->rects = (ddRect *)(dd_realloc(list_p->rects, list_p->nAlloced * sizeof(ddRect)));
	}

	list_p->rects[list_p->nRects] = rect;
	++list_p->nRects;
}


void
ddUpdateList_getRects(ddUpdateList* list_p, ddRect** outRects, int* outCount)
{
	if ( outRects != NULL )
		*outRects = list_p->rects;
	
	if ( outCount != NULL )
		*outCount = list_p->nRects;
}


ddRect
ddUpdateList_containingRect(ddUpdateList* list_p)
{
	int i;
	ddRect bounds = ddInvalidRect;
	
	for ( i = 0; i < list_p->nRects; ++i )
		bounds = ddRect_containRect(bounds, list_p->rects[i]);

	return bounds;
}
