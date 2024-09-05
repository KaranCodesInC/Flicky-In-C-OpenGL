#include <Windows.h>

struct VertexFormatPos3Tex2
{   // Custom vertex format for position+normal
	float tu , tv ;             ///< texture coordinates	
	float px , py , pz ;        ///< untransformed (world-space) position
};
	

	class SpriteDemoManagerC
	{
public:
	static SpriteDemoManagerC	*CreateInstance();
	static SpriteDemoManagerC	*GetInstance() {return sInstance;};
	~SpriteDemoManagerC(){};

	void		init(int width, int height);
	void		updateSprites(DWORD milliseconds);
	void		renderSprites();
	void		shutdown();

	int			getWidth() {return mWidth;}
	int			getHeight() {return mHeight;}


	void	setMood(int x, int y, int mood);
	void	setID(int x, int y, int id);
	void	setPosition(int x, int y, float xPosition, float yPosition);
	float	getXPosition(int x, int y);
	float	getYPosition(int x, int y);
	int		getMood(int x, int y);
	int		getSpriteID(int x, int y);

	//for sidescroll
	float scrollSpeed = 0.0f;  // Adjust this to control the speed of the scroll
	float scrollOffset = 0.0f;
	float zoomFactor = 1.2f;
	double_t totalScroll = 0;
	//double_t screenWidth = 1024;
	double_t oneScreenScrollWidth = 0.16180870318794405;
	double_t overflow = 0.0f;

private:
	static SpriteDemoManagerC *sInstance;
	SpriteDemoManagerC() {};
	void randomizeSprites();

	GLuint mSpriteTextureMap = 0;
	int mWidth = 0;
	int mHeight = 0;

	DWORD mLastUpdateTime = 0;
	DWORD mCurrentTime = 0;

	int *mMoodArray = nullptr;
	float *mPosArrayX = nullptr, *mPosArrayY = nullptr;
	int *mSpriteIDArray = nullptr;
	VertexFormatPos3Tex2 *mVertexArray = nullptr;
};

#define MOOD_UPDATE_DELTA_TIME 100