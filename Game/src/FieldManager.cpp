#define FIELD_MANAGER_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collinfo.h"
#include "object.h"
#include "inputMapper.h"
#include "field.h"
#include "FieldManager.h"
#include <vector>

FieldManagerC* FieldManagerC::sInstance=NULL;


FieldManagerC *FieldManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new FieldManagerC();
	return sInstance;
}

void FieldManagerC::init()
{
	// Create multiple platforms with different positions and sizes
	mFields.push_back(new FieldC(-140.0f, -787.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(-140.0f, 65.0f, 120, 1500, 0x000000FF));  // Another platform
	mFields.push_back(new FieldC(-140.0f, 925.0f, 120, 1500, 0x000000FF)); // Another platform
	mFields.push_back(new FieldC(-2150.0f, 1355.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(-2150.0f, 500.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(-2150.0f, -350.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(-2150.0f, -1210.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(1875.0f, 1355.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(1875.0f, 500.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(1875.0f, -1210.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(1875.0f, -350.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(-4150.0f, -787.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(-4150.0f, 65.0f, 120, 1500, 0x000000FF));  // Another platform
	mFields.push_back(new FieldC(-4150.0f, 925.0f, 120, 1500, 0x000000FF)); // Another platform
	mFields.push_back(new FieldC(-6170.0f, 1355.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(-6170.0f, 500.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(-6170.0f, -350.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(-6170.0f, -1210.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(3880.0f, -787.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(3880.0f, 65.0f, 120, 1500, 0x000000FF));  // Another platform
	mFields.push_back(new FieldC(3880.0f, 925.0f, 120, 1500, 0x000000FF)); // Another platform
	mFields.push_back(new FieldC(5895.0f, 1355.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(5895.0f, 500.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(5895.0f, -1210.0f, 120, 1500, 0x000000FF));
	mFields.push_back(new FieldC(5895.0f, -350.0f, 120, 1500, 0x000000FF));
}

void FieldManagerC::scrollFields(float scrollSpeed)
{
	for (FieldC* field : mFields)
	{
		field->scroll(scrollSpeed);  // Call the scroll method of each platform
	}
}

FieldC *FieldManagerC::getFieldPtr()
{
	return mFieldPtr;
}

void FieldManagerC::renderField()
{
	for (FieldC* field : mFields)
	{
		field->render();
	}
}

void FieldManagerC::shutdown()
{
	for (FieldC* field : mFields)
	{
		delete field;
	}
	mFields.clear();
}

std::vector<FieldC*> FieldManagerC::getFields()
{
	return mFields;
}

void FieldManagerC::wrapFields()
{
	for (FieldC* field : mFields)
	{
		field->wrapFields();  // Call the scroll method of each platform
	}
}


