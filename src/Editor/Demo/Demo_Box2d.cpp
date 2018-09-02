#include "Demo_box2d.h"

Settings settings;
void Demo1::Render_SceneObject()
{
	tiles->Step(&settings);
}