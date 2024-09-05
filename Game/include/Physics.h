#pragma once
class Physics
{
	static Physics* CreateInstance();
	static Physics* GetInstance() { return sInstance; };
	~Physics() {};
	bool collision();
	void lerp();
	private:
		Physics();
		static Physics* sInstance;
}; 
