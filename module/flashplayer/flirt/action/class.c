/*
 Flirt, an SWF rendering library
 Copyright (c) 2004-2006 Dave Hayden <dave@opaque.net>
 All rights reserved.
 
 http://www.opaque.net/flirt/

 This code is distributed under the two-clause BSD license.
 Read the LICENSE file or visit the URL above for details
*/

#include "class.h"
#include "classes/object_class.h"

ddActionClass* ddActionClassClass = NULL;

ddActionClass*
dd_newActionClass()
{
	ddActionClass* class_p = (ddActionClass *)(dd_malloc(sizeof(ddActionClass)));
	
	ddActionObject_init((ddActionObject*)class_p);
	
	class_p->parent.refCount = OBJECT_STATIC;
	
	class_p->getProperty = NULL;
	class_p->setProperty = NULL;
	class_p->destroy = NULL;
	
	ddActionObject_setClass((ddActionObject*)(class_p), ddActionClassClass);
	ddActionClass_setSuperclass(class_p, ddActionObjectClass);

	return class_p;
}


void
ddActionClass_setSuperclass(ddActionClass* class_p, ddActionClass* superclass)
{
	ddActionObject_setPrototype((ddActionObject*)class_p, (ddActionObject*)superclass);
}


void
ddActionClass_addNativeMethod(ddActionClass* classObject, char* name, ddNativeFunction function, int nargs)
{
	ddActionObject_addNativeMethod((ddActionObject*)classObject, name, function, nargs);
}
