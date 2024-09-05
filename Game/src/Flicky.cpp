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
#include "Flicky.h"

Flicky* Flicky::sInstance = NULL;

Flicky* Flicky::CreateInstance()
{
	if (sInstance != NULL)return sInstance;
	else

		sInstance = new Flicky();
	return sInstance;
}

void Flicky::init()
{
	/* load an image file directly as a new OpenGL texture */
	flickyTexture = SOIL_load_OGL_texture("asset/Flicky.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

Flicky::Flicky()
{
	lives = 3;
	movespeed = 5;
	posX = 0;
	posY = -1575;
	mWidth = 210;
	mHeight = 410;
}

void Flicky::drawFlicky()
{
	// Reset the texture matrix to prevent flickyTexture from inheriting any transformations
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();  // Reset texture matrix to identity
	glMatrixMode(GL_MODELVIEW);  // Switch back to modelview matrix

	float_t Updated_PosX = posX;
	float_t Updated_PosY = posY;

	float_t quadWidth = 220 / 1.3;
	float_t quadHeight = 400 / 1.3;
	float_t SpriteX = Updated_PosX;
	float_t SpriteY = Updated_PosY;

	float_t leftMostU, rightMostU, highestV, lowestV;

	
	if (isJumping && SpriteDemoManagerC::GetInstance()->scrollSpeed == 0) {
		// Jump sprite coordinates when jumping with direction (adjust as needed)
		leftMostU = 150 / (float)770;
		rightMostU = 230 / (float)760;
		highestV = 625 / (float)736;
		lowestV = 500 / (float)685;
	}
	else if (isJumping) {

		quadWidth = 280 / 1.3;
		quadHeight = 400 / 1.3;
		// Jump sprite coordinates when jumping with direction (adjust as needed)
		leftMostU = 150 / (float)820;
		rightMostU = 230 / (float)680;
		highestV = 625 / (float)625;
		lowestV = 500 / (float)575;

	}
	else if (SpriteDemoManagerC::GetInstance()->scrollSpeed == 0) {
		quadWidth = 220 / 1.3;
		quadHeight = 400 / 1.3;

		// Idle pose coordinates
		leftMostU = 20 / (float)580;
		rightMostU = 100 / (float)740;
		highestV = 625 / (float)1550;
		lowestV = 500 / (float)1850;
	}
	else if (isDecelerating) {
		quadWidth = 280 / 1.3;
		quadHeight = 350 / 1.3;

		// Skid animation coordinates
		leftMostU = 120 / (float)3000;
		rightMostU = 200 / (float)1150;
		highestV = 625 / (float)1200;
		lowestV = 500 / (float)1200;
	}
	else {
		quadWidth = 220 / 1.3;
		quadHeight = 400 / 1.3;

		// Toggle between two frames when moving
		if (toggleSprite) {
			// Frame 1 coordinates
			leftMostU = 20 / (float)667;
			rightMostU = 100 / (float)667;
			highestV = 625 / (float)864;
			lowestV = 500 / (float)864;
		}
		else {
			// Frame 2 coordinates 
			leftMostU = 20 / (float)97;
			rightMostU = 100 / (float)327;
			highestV = 625 / (float)864;
			lowestV = 500 / (float)864;
		}

		// Toggle sprite for the next frame
		toggleSprite = !toggleSprite;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, flickyTexture);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glDisable(GL_CULL_FACE);

	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

	glBegin(GL_QUADS);
	if (facingLeft) {
		// Texture coordinates for facing left
		glTexCoord2f(rightMostU, 1 - highestV); glVertex3f(SpriteX - (quadWidth / 2), SpriteY - (quadHeight / 2), 0.0);
		glTexCoord2f(leftMostU, 1 - highestV); glVertex3f(SpriteX + (quadWidth / 2), SpriteY - (quadHeight / 2), 0.0);
		glTexCoord2f(leftMostU, 1 - lowestV); glVertex3f(SpriteX + (quadWidth / 2), SpriteY + (quadHeight / 2), 0.0);
		glTexCoord2f(rightMostU, 1 - lowestV); glVertex3f(SpriteX - (quadWidth / 2), SpriteY + (quadHeight / 2), 0.0);
	}
	else {
		// Texture coordinates for facing right
		glTexCoord2f(leftMostU, 1 - highestV); glVertex3f(SpriteX - (quadWidth / 2), SpriteY - (quadHeight / 2), 0.0);
		glTexCoord2f(rightMostU, 1 - highestV); glVertex3f(SpriteX + (quadWidth / 2), SpriteY - (quadHeight / 2), 0.0);
		glTexCoord2f(rightMostU, 1 - lowestV); glVertex3f(SpriteX + (quadWidth / 2), SpriteY + (quadHeight / 2), 0.0);
		glTexCoord2f(leftMostU, 1 - lowestV); glVertex3f(SpriteX - (quadWidth / 2), SpriteY + (quadHeight / 2), 0.0);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

