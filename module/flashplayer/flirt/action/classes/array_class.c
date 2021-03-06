/*
 Flirt, an SWF rendering library
 Copyright (c) 2004-2006 Dave Hayden <dave@opaque.net>
 All rights reserved.
 
 http://www.opaque.net/flirt/

 This code is distributed under the two-clause BSD license.
 Read the LICENSE file or visit the URL above for details
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "array_class.h"
#include "object_class.h"
#include "../function.h"

ddActionClass* ddActionArrayClass = NULL;


static ddActionValue
ddActionArray_getProperty(ddActionContext* context, ddActionObject* object, const char* name)
{
	ddActionArray* array = (ddActionArray*)object;
	
	if ( !ddActionObject_isKindOfClass(object, ddActionArrayClass) )
		return ddUndefValue;

	if ( strcasecmp(name, "length") == 0 )
		return dd_newActionValue_int(array->length);

	return ddActionObject_getProperty_default(context, object, name);
}


ddActionArray*
dd_newActionArray_size(int size)
{
	ddActionArray* array_v = (ddActionArray *)(dd_malloc(sizeof(struct _ddActionArray)));
	ddActionObject_init((ddActionObject*)(array_v));

	array_v->length = size;
	
	ddActionObject_setClass((ddActionObject*)(array_v), ddActionArrayClass);

	return array_v;
}

ddActionArray*
dd_newActionArray()
{
	return dd_newActionArray_size(0);
}


void
ddActionArray_setMember(ddActionArray* array_v, int member, ddActionValue value)
{
	char* name = (char *)(dd_malloc(16)); /* XXX - ??? */
	sprintf(name, "%i", member);

	if ( member >= array_v->length )
		array_v->length = member+1;

	ddActionHash_setValue(((ddActionObject*)(array_v))->properties, name, value);
}


ddActionValue
ddActionArray_getMember(ddActionArray* array_v, int member)
{
	char* name;
	ddActionValue val;

	if ( member >= array_v->length )
		return ddNullValue;

	name = (char *)(dd_malloc(16)); /* XXX - ??? */
	sprintf(name, "%i", member);

	val = ddActionHash_findValue(((ddActionObject*)(array_v))->properties, name);

	dd_free(name);
	return val;
}


static ddActionValue
Array_concat(ddActionObject* object, ddActionContext* context, int nargs)
{
	//ddActionArray* array = (ddActionArray*)object;
	return ddNullValue;
}


static ddActionValue
Array_join(ddActionObject* object, ddActionContext* context, int nargs)
{
	//ddActionArray* array = (ddActionArray*)object;
	return ddNullValue;
}


static ddActionValue
Array_pop(ddActionObject* object, ddActionContext* context, int nargs)
{
	char* name;
	ddActionArray* array_v = (ddActionArray*)object;
	int num;
	
	if ( !ddActionObject_isKindOfClass(object, ddActionArrayClass) )
		return ddUndefValue;
	
	num = array_v->length-1;

	/* XXX */

	//ddActionValue val = ddActionArray_getMember(array, num);
	name = (char *)(dd_malloc(sizeof(char)*16));

	sprintf(name, "%i", num);
	ddActionHash_removeValue(object->properties, name);

	return ddNullValue;
}


static ddActionValue Array_push(ddActionObject* object, ddActionContext* context, int nargs)
{
	ddActionArray* array_v = (ddActionArray*)(object);
	int i;

	if ( !ddActionObject_isKindOfClass(object, ddActionArrayClass) )
		return ddUndefValue;

	for ( i = 0; i < nargs; ++i )
	{
		ddActionValue val = ddActionStack_pop(&context->stack);
		ddActionArray_setMember(array_v, array_v->length, val);
	}

	return ddNullValue;
}


static ddActionValue
Array_reverse(ddActionObject* object, ddActionContext* context, int nargs)
{
	ddActionArray* array_v = (ddActionArray *)(object);

	int i;
	int len;
	ddActionValue* members;

	if ( !ddActionObject_isKindOfClass(object, ddActionArrayClass) )
		return ddUndefValue;

	len = array_v->length;
	members = (ddActionValue *)(dd_malloc(len * sizeof(ddActionValue)));
	
	for ( i = 0; i < len; ++i )
		members[i] = ddActionArray_getMember(array_v, i);

	for ( i = 0; i < len; ++i )
		ddActionArray_setMember(array_v, len - i - 1, members[i]);

	dd_free(members);

	return ddNullValue;
}


static ddActionValue
Array_shift(ddActionObject* object, ddActionContext* context, int nargs)
{
	//ddActionArray* array = (ddActionArray*)object;
	return ddNullValue;
}


static ddActionValue
Array_slice(ddActionObject* object, ddActionContext* context, int nargs)
{
	//ddActionArray* array = (ddActionArray*)object;
	return ddNullValue;
}


static ddActionValue
Array_sort(ddActionObject* object, ddActionContext* context, int nargs)
{
	//ddActionArray* array = (ddActionArray*)object;
	return ddNullValue;
}


static ddActionValue
Array_splice(ddActionObject* object, ddActionContext* context, int nargs)
{
	//ddActionArray* array = (ddActionArray*)object;
	return ddNullValue;
}


#define ARRAY_TOSTRING_INCREMENT 256

static ddActionValue
Array_toString(ddActionObject* object, ddActionContext* context, int nargs)
{
	ddActionArray* array_v = (ddActionArray*)(object);
	
	char* strval = NULL;
	int i;
	int p = 0;
	int bufsize = 0;

	if ( !ddActionObject_isKindOfClass(object, ddActionArrayClass) )
		return ddUndefValue;
	
	for ( i = 0; i < array_v->length; ++i )
	{
		ddActionValue val = ddActionArray_getMember(array_v, i);
		char* str = ddActionValue_getStringValue(context, val);
		int len = strlen(str);

		if ( p + len + 1 > bufsize )
		{
			bufsize += ARRAY_TOSTRING_INCREMENT;
			strval = (char *)(dd_realloc(strval, bufsize));
		}

		if ( i > 0 )
			strval[p++] = ',';

		strcpy(strval+p, str);
		p+= len;
	}

	return dd_newActionValue_string(strval);
}


static ddActionValue
Array_unshift(ddActionObject* object, ddActionContext* context, int nargs)
{
	//ddActionArray* array = (ddActionArray*)object;
	return ddNullValue;
}


static ddActionValue
Array_constructor(ddActionObject* object, ddActionContext* context, int nargs)
{
	ddActionArray* array_v;

	if ( nargs == 1 )
	{
		ddActionValue val = ddActionStack_pop(&context->stack);
		int size = ddActionValue_getIntValue(val);
		ddActionValue_release(val);

		array_v = dd_newActionArray_size(size);
	}
	else
	{
		int i;

		array_v = dd_newActionArray();

		for ( i = 0; i < nargs; ++i )
		{
			ddActionValue val = ddActionStack_pop(&context->stack);
			ddActionArray_setMember(array_v, i, val);
			ddActionValue_release(val);
		}
	}
	
	return dd_newActionValue_object((ddActionObject*)(array_v));
}


ddActionFunction*
dd_initArrayClass()
{
	ddActionObject* classObject;
	ddActionFunction* ctor =
		dd_newActionNativeFunction(Array_constructor, FUNCTION_VARARGS);

	ddActionArrayClass = dd_newActionClass();
	classObject = (ddActionObject*)ddActionArrayClass;
	
	ddActionArrayClass->getProperty = ddActionArray_getProperty;

	ddActionObject_addNativeMethod(classObject, strdup("concat"), Array_concat, 1);
	ddActionObject_addNativeMethod(classObject, strdup("join"), Array_join, 1);
	ddActionObject_addNativeMethod(classObject, strdup("pop"), Array_pop, FUNCTION_VARARGS);
	ddActionObject_addNativeMethod(classObject, strdup("push"), Array_push, FUNCTION_VARARGS);
	ddActionObject_addNativeMethod(classObject, strdup("reverse"), Array_reverse, 0);
	ddActionObject_addNativeMethod(classObject, strdup("shift"), Array_shift, FUNCTION_VARARGS);
	ddActionObject_addNativeMethod(classObject, strdup("slice"), Array_slice, 0);
	ddActionObject_addNativeMethod(classObject, strdup("sort"), Array_sort, 1);
	ddActionObject_addNativeMethod(classObject, strdup("splice"), Array_splice, FUNCTION_VARARGS);
	ddActionObject_addNativeMethod(classObject, strdup("toString"), Array_toString, 0);
	ddActionObject_addNativeMethod(classObject, strdup("unshift"), Array_unshift, FUNCTION_VARARGS);

	ddActionFunction_setPrototype(ctor, classObject);

	return ctor;
}
