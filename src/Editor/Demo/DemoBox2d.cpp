#include "DemoBox2d.h"

Settings settings;
void DemoBox2d::Render_SceneObject()
{
	tiles->Step(&settings);
}