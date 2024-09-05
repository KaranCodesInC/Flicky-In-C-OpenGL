#include <vector>
class FieldManagerC
{
public:
	static FieldManagerC	*CreateInstance();
	static FieldManagerC	*GetInstance() {return sInstance;};
	~FieldManagerC(){};

	FieldC* getFieldPtr();
	void init();
	void renderField();
	void shutdown();

	std::vector<FieldC*> getFields();  // Get all platforms
	
	void scrollFields(float scrollSpeed);
	void wrapFields();
	float totalScroll = 0.0f;
	const float screenWidth = 1024.0f;
	
private:
	static FieldManagerC *sInstance;
	FieldManagerC(){};
	
	FieldC *mFieldPtr = nullptr;
	std::vector<FieldC*> mFields;  // Vector to hold multiple platforms
};