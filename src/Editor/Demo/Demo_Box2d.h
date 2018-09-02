#include "DemoTest.h"
class Demo1 :public DemoTest
{
public:
	Tiles * tiles;
	Demo1() :DemoTest()
	{
		tiles = new Tiles();
	}

	~Demo1()
	{
	}

	void Render_SceneObject() override;


private:

};
