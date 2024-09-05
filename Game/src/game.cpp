#define GAME_CPP
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
#include "collInfo.h"
#include "object.h"
#include "inputmapper.h"
#include "ball.h"
#include "field.h"
#include "random.h"
#include "gameObjects.h"
#include "openGLStuff.h"
#include "game.h"
#include "StateManager.h"
#include "BallManager.h"
#include "FieldManager.h"
#include "InputManager.h"
#include "SpriteDemoManager.h"
#include "igame.h"
#include "Flicky.h"
#include "Platform.h"

IGame* CreateGame() {
	return new CGame();
}

void DestroyGame(IGame* pGame) {
	delete pGame;
}

// Declarations
const char8_t CGame::mGameTitle[]="Framework1";


CGame::CGame() {
	Platform::CreateInstance();
	Flicky::CreateInstance();
	//BallManagerC::CreateInstance();
	StateManagerC::CreateInstance();
	FieldManagerC::CreateInstance();
	//	InputManagerC::CreateInstance();
	SpriteDemoManagerC::CreateInstance();
	//	InputManagerC::GetInstance()->init();
}

CGame::~CGame()
{
	delete Platform::GetInstance();
	//delete BallManagerC::GetInstance();
	delete StateManagerC::GetInstance();
	delete FieldManagerC::GetInstance();
	delete Flicky::GetInstance();
}

bool CGame::Initialize (GL_Window* window, Keys* keys)
{
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);

	Platform::GetInstance()->CreatePlatform(0.0f, -800.0f, 100.0f, 1260.0f, 0xFFFF0000);
	//BallManagerC::GetInstance()->init();
	StateManagerC::GetInstance()->setState(StateManagerC::HALF_BALLS_FILLED);
	FieldManagerC::GetInstance()->init();
	SpriteDemoManagerC::GetInstance()->init(28, 26);
	Flicky::GetInstance()->init();

	return true;
}

void CGame::Deinitialize() {
	//BallManagerC::GetInstance()->shutdown();
	StateManagerC::GetInstance()->shutdown();
	FieldManagerC::GetInstance()->shutdown();
	SpriteDemoManagerC::GetInstance()->shutdown();
}

float decelerationRate = 0.00000025f;    // The rate at which the speed decreases when no key is pressed	
float accelerationRate = 0.000002f;     
float maxScrollSpeed = 0.0003f;
uint32_t totalScroll = 0.0f;

void CGame::UpdateFrame(uint32_t milliseconds)
{

	if (g_keys->keyDown[VK_UP] && !Flicky::GetInstance()->isJumping) {
		Flicky::GetInstance()->isJumping = true;
		Flicky::GetInstance()->jumpVelocity = Flicky::GetInstance()->jumpForce;  // Apply the initial jump force
	}

	if (g_keys->keyDown[VK_LEFT]) {
		if (Flicky::GetInstance()->isDecelerating == true)
		{
			Flicky::GetInstance()->isDecelerating = false;
		}
		SpriteDemoManagerC::GetInstance()->scrollSpeed -= accelerationRate * milliseconds;
		if (SpriteDemoManagerC::GetInstance()->scrollSpeed < -maxScrollSpeed) {
			SpriteDemoManagerC::GetInstance()->scrollSpeed = -maxScrollSpeed;
		}

		Flicky::GetInstance()->updateDirection(true, false);
	}

	else if (g_keys->keyDown[VK_RIGHT]) {
		if (Flicky::GetInstance()->isDecelerating == true)
		{
			Flicky::GetInstance()->isDecelerating = false;
		}
		SpriteDemoManagerC::GetInstance()->scrollSpeed += accelerationRate * milliseconds;
		if (SpriteDemoManagerC::GetInstance()->scrollSpeed > maxScrollSpeed) {
			SpriteDemoManagerC::GetInstance()->scrollSpeed = maxScrollSpeed;
		}
		Flicky::GetInstance()->updateDirection(false, true);
	}

	else {
		// Apply deceleration when no key is pressed
		if (SpriteDemoManagerC::GetInstance()->scrollSpeed > 0) {
			SpriteDemoManagerC::GetInstance()->scrollSpeed -= decelerationRate * milliseconds;
			Flicky::GetInstance()->isDecelerating = true;  // Decelerating when slowing down
			if (SpriteDemoManagerC::GetInstance()->scrollSpeed < 0) {
				SpriteDemoManagerC::GetInstance()->scrollSpeed = 0;
				Flicky::GetInstance()->isDecelerating = false;
			}
		}

		else if (SpriteDemoManagerC::GetInstance()->scrollSpeed < 0) {
			SpriteDemoManagerC::GetInstance()->scrollSpeed += decelerationRate * milliseconds;
			Flicky::GetInstance()->isDecelerating = true;  // Decelerating when slowing down
			if (SpriteDemoManagerC::GetInstance()->scrollSpeed > 0) {
				SpriteDemoManagerC::GetInstance()->scrollSpeed = 0;
				Flicky::GetInstance()->isDecelerating = false;
			}
		}
	}

	const float epsilon = 0.0005f; // A small value to account for floating-point precision

	float flag = fmod(SpriteDemoManagerC::GetInstance()->totalScroll, SpriteDemoManagerC::GetInstance()->oneScreenScrollWidth);

	/*if (fabs(flag) < epsilon) // Check if flag is close to 0
	{
		bool ye = true;
		FieldManagerC::GetInstance()->wrapFields();
	}*/

	/*if (fabs(SpriteDemoManagerC::GetInstance()->totalScroll) >= SpriteDemoManagerC::GetInstance()->oneScreenScrollWidth)
	{
		FieldManagerC::GetInstance()->wrapFields();
		SpriteDemoManagerC::GetInstance()->totalScroll = 0.0f;
	}*/

	float scaledScrollSpeed = SpriteDemoManagerC::GetInstance()->scrollSpeed * milliseconds * 4020.0f;
	FieldManagerC::GetInstance()->scrollFields(scaledScrollSpeed);
	//FieldManagerC::GetInstance()->wrapFields(scaledScrollSpeed);

	if (Flicky::GetInstance()->isJumping) {
		Flicky::GetInstance()->posY += Flicky::GetInstance()->jumpVelocity * milliseconds;  // Move Flicky up
		Flicky::GetInstance()->jumpVelocity -= Flicky::GetInstance()->gravity * milliseconds;  // Apply gravity

		// Check if Flicky has landed back on the ground
		if (Flicky::GetInstance()->posY <= Flicky::GetInstance()->groundLevel) {
			Flicky::GetInstance()->posY = Flicky::GetInstance()->groundLevel;  // Snap Flicky to the ground level
			Flicky::GetInstance()->isJumping = false;    // Reset the jump state
			Flicky::GetInstance()->jumpVelocity = 0.0f;  // Reset velocity
		}
	}

	// Adjust scroll offset based on current scroll speed
	SpriteDemoManagerC::GetInstance()->scrollOffset += SpriteDemoManagerC::GetInstance()->scrollSpeed * milliseconds;

	// Wrap around the scroll offset to create a circular scrolling effect
	if (SpriteDemoManagerC::GetInstance()->scrollOffset >= 1.0f) {
		SpriteDemoManagerC::GetInstance()->scrollOffset -= 1.0f;
	}
	else if (SpriteDemoManagerC::GetInstance()->scrollOffset <= -1.0f) {
		SpriteDemoManagerC::GetInstance()->scrollOffset += 1.0f;
	}
}

	//SpriteDemoManagerC::GetInstance()->updateSprites(milliseconds);
	//BallManagerC::GetInstance()->updateBalls(milliseconds);
	//InputManagerC::GetInstance()->update(milliseconds);

void CGame::DrawScene(void)
{
	startOpenGLDrawing();

	Platform::GetInstance()->RenderPlatform();
	SpriteDemoManagerC::GetInstance()->renderSprites();
	//BallManagerC::GetInstance()->renderBalls();
	FieldManagerC::GetInstance()->renderField();
	Flicky::GetInstance()->drawFlicky();
}
