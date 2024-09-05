#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

#include <cstdint>  // For uint32_t
#include <vector>

class Platform {
public:
    // Constructor and Destructor
    static Platform* CreateInstance();
    static Platform* GetInstance() { return sInstance; };
    ~Platform() {};

    void CreatePlatform(float x, float y, float width, float height, uint32_t color);
    void RenderPlatform();
    void UpdatePlatform(float scrollSpeed);

    // Setters
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setColor(uint32_t color);

    // Getters
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    uint32_t getColor() const;

    // Update and Render
    void update(float scrollSpeed);
    void render() const;
    // Managing multiple platforms
    std::vector<Platform> platforms;

private:

    static Platform* sInstance;
    // Platform properties
    float mX;        // X position
    float mY;        // Y position
    float mWidth;    // Width of the platform
    float mHeight;   // Height of the platform
    uint32_t mColor; // Color of the platform
};

#endif // PLATFORM_H

