#pragma once
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <SOIL.h>
#include "soil.h"

class Flicky
{
public:
	static Flicky *CreateInstance();
	static Flicky* GetInstance() { return sInstance; };
	~Flicky() {};
	float posX, posY;
	float ground;
	float_t movespeed;
	int lives;
	void init();
	void drawFlicky();
	bool facingLeft;
	bool facingRight;
	void updateDirection(bool leftPressed, bool rightPressed)
	{
		if (leftPressed) {
			facingLeft = true;
		}
		else if (rightPressed) {
			facingLeft = false;
		}
	}

	bool toggleSprite = false;
	bool isDecelerating = false;
	bool isJumping = false;    // To track if Flicky is jumping
	float jumpVelocity = 0.0f; // Vertical velocity for the jump
	float gravity = 0.0022f;   // Gravity value to pull Flicky down
	float groundLevel = -1575; // The Y position representing the ground level
	float jumpForce = 2.1f;    // Initial force applied when jumping

private:

	Flicky();
	static Flicky* sInstance;
	GLuint flickyTexture = 0;
	float mWidth;
	float mHeight;

};