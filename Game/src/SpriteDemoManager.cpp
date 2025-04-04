#define STATE_MANAGER_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include <assert.h>
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "spriteDemoManager.h"
#include "random.h"
#include "soil.h"

SpriteDemoManagerC* SpriteDemoManagerC::sInstance=NULL;


SpriteDemoManagerC *SpriteDemoManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new SpriteDemoManagerC();
	return sInstance;
}
void SpriteDemoManagerC::init(int height, int width)
{
	mHeight = height;
	mWidth = width;

	mMoodArray = (int*)malloc(height*width*sizeof(int));
	mPosArrayX = (float *)malloc(height*width*sizeof(float));
	mPosArrayY = (float *)malloc(height*width*sizeof(float));
	mSpriteIDArray = (int *)malloc(height*width*sizeof(int));

	randomizeSprites();


/* load an image file directly as a new OpenGL texture */
	mSpriteTextureMap = SOIL_load_OGL_texture("asset/Area2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);


	mVertexArray = (VertexFormatPos3Tex2 *)malloc(height*width*4*sizeof(VertexFormatPos3Tex2));
}
void SpriteDemoManagerC::shutdown()
{
	free(mMoodArray);
	free(mPosArrayX);
	free(mPosArrayY);
	free(mSpriteIDArray);
	free(mVertexArray);
}

float xLeft = -11725;
float xRight = 7575;
float yHigh = 7580;
float yLow = -11575;

float xTextLeft = 0.0;
float xTextRight = 1.0;
float yTextTop = 1.0;
float yTextBottom = 0.0;

void SpriteDemoManagerC::renderSprites()
{
	totalScroll += scrollSpeed;
	/*glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, 1);
#if 1
	glBegin (GL_QUADS);
	for(int y=0; y < mHeight; ++y)
	{
		for(int x=0; x < mWidth; ++x)
		{	
			GLfloat xPositionLeft = (getXPosition(x,y) - 32.0f)*4000.0f/1024.0f;
			xPositionLeft = xPositionLeft/2.0f;
			GLfloat xPositionRight = (getXPosition(x,y) + 32.0f)*4000.0f/1024.0f;
			xPositionRight = xPositionRight/2.0f;

			GLfloat yPositionTop = (getYPosition(x,y) - 16.0f) * 1600.0f/168.0f;
			yPositionTop = yPositionTop/2.0f;
			GLfloat yPositionBottom = (getYPosition(x,y) + 16.0f) * 1600.0f/168.0f;
			yPositionBottom = yPositionBottom/2.0f;

			GLfloat xTextureCoord = getSpriteID(x,y)*(1.0f/8.0f);
			GLfloat yTextureCoord = getMood(x,y)*(1.0f/4.0f);


			glColor4ub(0xFF, 0xFF, 0xFF,0xFF);
			glTexCoord2f (xTextureCoord, yTextureCoord);
			glVertex3f (xPositionLeft, yPositionTop, 0.0);
			glTexCoord2f (xTextureCoord + (1.0f/8.0f), yTextureCoord);
			glVertex3f (xPositionRight, yPositionTop, 0.0);
			glTexCoord2f (xTextureCoord + (1.0/8.0f), yTextureCoord + (1.0/4.0f));
			glVertex3f (xPositionRight, yPositionBottom, 0.0);
			glTexCoord2f (xTextureCoord, yTextureCoord + (1.0/4.0f));
			glVertex3f (xPositionLeft, yPositionBottom, 0.0);
		}	
	}	
#else
	VertexFormatPos3Tex2 *vert = mVertexArray;

	for(int y=0; y < mHeight; ++y)
		{
			for(int x=0; x < mWidth; ++x)
			{	
				GLfloat xPositionLeft = (getXPosition(x,y) - 32.0f)*4000.0f/1024.0f;
				xPositionLeft = xPositionLeft/2.0f;
				GLfloat xPositionRight = (getXPosition(x,y) + 32.0f)*4000.0f/1024.0f;
				xPositionRight = xPositionRight/2.0f;

				GLfloat yPositionTop = (getYPosition(x,y) - 16.0f) * 1600.0f/168.0f;
				yPositionTop = yPositionTop/2.0f;
				GLfloat yPositionBottom = (getYPosition(x,y) + 16.0f) * 1600.0f/168.0f;
				yPositionBottom = yPositionBottom/2.0f;

				GLfloat xTextureCoord = getSpriteID(x,y)*(1.0f/8.0f);
				GLfloat yTextureCoord = getMood(x,y)*(1.0f/4.0f);

				vert->px = xPositionLeft;
				vert->py = yPositionTop;
				vert->pz = 0.0f;
				vert->tu = xTextureCoord;
				vert->tv = yTextureCoord;
				vert++;

				vert->px = xPositionRight;
				vert->py = yPositionTop;
				vert->pz = 0.0f;
				vert->tu = xTextureCoord + (1.0f/8.0f);
				vert->tv = yTextureCoord;
				vert++;

				vert->px = xPositionRight;
				vert->py = yPositionBottom;
				vert->pz = 0.0f;
				vert->tu = xTextureCoord + (1.0f/8.0f);
				vert->tv = yTextureCoord + (1.0f/4.0f);
				vert++;

				vert->px = xPositionLeft;
				vert->py = yPositionBottom;
				vert->pz = 0.0f;
				vert->tu = xTextureCoord;
				vert->tv = yTextureCoord + (1.0f/4.0f);
				vert++;
			}
	}

	glColor4ub(0xFF, 0xFF, 0xFF,0xFF);
    glInterleavedArrays(GL_T2F_V3F , sizeof(VertexFormatPos3Tex2) , mVertexArray);
    glDrawArrays( GL_QUADS, 0 , 4*mWidth*mHeight );

#endif
	glEnd ();*/
	//float wrappedOffset = fmod(0.01f, 1.0f);
	float zoomFactor = 1.2f;
	float translationAmount = scrollOffset / zoomFactor; // Calculate translation amount
	glEnable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    glBindTexture(GL_TEXTURE_2D, mSpriteTextureMap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Apply texture translation and scaling using the texture matrix
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    
    // Scale down the texture to zoom out
    glScalef(zoomFactor, zoomFactor, 1.0f);

    // Translate the texture for sidescrolling
    glTranslatef(scrollOffset / zoomFactor, 0.0f, 0.0f);

    // Reset to model view matrix mode
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

	// Calculate translated texture coordinates
	float u1_translated = -2.0f + translationAmount;
	float u2_translated = 2.0f + translationAmount;
	float u3_translated = 2.0f + translationAmount;
	float u4_translated = -2.0f + translationAmount;

    // Render the background quad
    glBegin(GL_QUADS);
	glTexCoord2f(-2.0f, -2.0f); glVertex2f(xLeft, yLow);
	glTexCoord2f(2.0f, -2.0f); glVertex2f(xRight, yLow);
	glTexCoord2f(2.0f, 2.0f); glVertex2f(xRight, yHigh);
	glTexCoord2f(-2.0f, 2.0); glVertex2f(xLeft, yHigh);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void SpriteDemoManagerC::updateSprites(DWORD milliseconds)
{
	mCurrentTime += milliseconds;

	if(mCurrentTime - mLastUpdateTime > MOOD_UPDATE_DELTA_TIME)
	{
		int numberToUpdate = getRangedRandom((mWidth*mHeight)/3,((mWidth*mHeight)/3) + 20);
		mLastUpdateTime = mCurrentTime;
		for(int i = 0;i < numberToUpdate;++i)
		{
			int x = getRangedRandom(0,mWidth-1);
			int y = getRangedRandom(0,mHeight-1);
			setMood(x,y,getRangedRandom(0,3));
		}
	}
}

void SpriteDemoManagerC::randomizeSprites()
{
	for(int y=0; y < mHeight; ++y)
	{
		for(int x=0; x < mWidth; ++x)
		{
			setID(x,y,getRangedRandom(0,7));
			setMood(x,y,getRangedRandom(0,3));
			float xPos = (float)(x-mWidth/2)*64.0f;
			float yPos = (float)(y-mHeight/2)*32.0f;
			setPosition(x,y,xPos,yPos);
		}
	}
}

void SpriteDemoManagerC::setMood(int x, int y, int mood)
{
	assert(x < mWidth);
	assert(y < mHeight);
	assert(mood < 4);

	int offset = y*mWidth + x;
	mMoodArray[offset] = mood;
}

void SpriteDemoManagerC::setID(int x, int y, int id)
{
	assert(x < mWidth);
	assert(y < mHeight);
	assert(id < 8);

	int offset = y*mWidth + x;
	mSpriteIDArray[offset] = id;
}

void SpriteDemoManagerC::setPosition(int x, int y, float xPosition, float yPosition)
{
	assert(x < mWidth);
	assert(y < mHeight);

	int offset = y*mWidth + x;
	mPosArrayX[offset] = xPosition;
	mPosArrayY[offset] = yPosition;
}

float SpriteDemoManagerC::getXPosition(int x, int y)
{
	assert(x < mWidth);
	assert(y < mHeight);

	int offset = y*mWidth + x;
	
	return mPosArrayX[offset];
}
float SpriteDemoManagerC::getYPosition(int x, int y)
{
	assert(x < mWidth);
	assert(y < mHeight);

	int offset = y*mWidth + x;
	
	return mPosArrayY[offset];
}
int	SpriteDemoManagerC::getMood(int x, int y)
{
	assert(x < mWidth);
	assert(y < mHeight);

	int offset = y*mWidth + x;
	
	return mMoodArray[offset];
}
int	SpriteDemoManagerC::getSpriteID(int x, int y)
{
	assert(x < mWidth);
	assert(y < mHeight);

	int offset = y*mWidth + x;
	
	return mSpriteIDArray[offset];
}