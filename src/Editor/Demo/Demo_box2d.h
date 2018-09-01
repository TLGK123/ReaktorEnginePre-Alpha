#include "DemoTest.h"
class Demo1 :public TestDemo
{
public:
	Tiles * tiles;
	Demo1() :TestDemo()
	{
		tiles = new Tiles();
	}

	~Demo1()
	{
	}

	void Render_SceneObject() override;


private:

};
