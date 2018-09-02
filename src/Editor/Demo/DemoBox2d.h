#include "DemoTest.h"
#include "Tiles.h"
class DemoBox2d :public DemoTest
{
public:
	Tiles * tiles;
	DemoBox2d() :DemoTest()
	{
		tiles = new Tiles();
	}

	~DemoBox2d()
	{
	}

	void Render_SceneObject() override;


private:

};
