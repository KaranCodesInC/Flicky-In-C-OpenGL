#include "Platform.h"
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
#include "ShapeDraw.h"
#include <vector>

// Initialize the static instance
Platform* Platform::sInstance = NULL;

Platform* Platform::CreateInstance() {
    if (sInstance != NULL)return sInstance;
    else

        sInstance = new Platform();
    return sInstance;
}

void Platform::setPosition(float x, float y) {
    mX = x;
    mY = y;
}

void Platform::setSize(float width, float height) {
    mWidth = width;
    mHeight = height;
}

void Platform::setColor(uint32_t color) {
    mColor = color;
}

float Platform::getX() const {
    return mX;
}

float Platform::getY() const {
    return mY;
}

float Platform::getWidth() const {
    return mWidth;
}

float Platform::getHeight() const {
    return mHeight;
}

uint32_t Platform::getColor() const {
    return mColor;
}

void Platform::update(float scrollSpeed) {
    mX -= scrollSpeed;  // Move the platform based on scroll speed
}

void Platform::render() const {
    float left = mX - mWidth / 2.0f;
    float right = mX + mWidth / 2.0f;
    float bottom = mY - mHeight / 2.0f;
    float top = mY + mHeight / 2.0f;

    // Extract color components
	char8_t r = (char8_t)(mColor>>16 & 0xFF);
	char8_t g = (char8_t)(mColor>>8 & 0xFF);
	char8_t b = (char8_t)(mColor>>0 & 0xFF);

    // Draw platform using extracted colors
    DrawLine(left, top, right, top, r, g, b);
    DrawLine(right, top, right, bottom, r, g, b);
    DrawLine(right, bottom, left, bottom, r, g, b);
    DrawLine(left, bottom, left, top, r, g, b);
}

void Platform::CreatePlatform(float x, float y, float width, float height, uint32_t color) {
    Platform platform;
    platform.setPosition(x, y);
    platform.setSize(width, height);
    platform.setColor(color);
    platforms.push_back(platform);
}

void Platform::UpdatePlatform(float scrollSpeed) {
    for (auto& platform : platforms) {
        platform.update(scrollSpeed);
    }
}

void Platform::RenderPlatform() {
    for (const auto& platform : platforms) {
        platform.render();
    }
}
