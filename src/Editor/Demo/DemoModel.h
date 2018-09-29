//
//  DemoModel.h
//  TmingEngine
//
//  Created by blue on 2018/9/4.
//

#ifndef DemoModel_h
#define DemoModel_h
#include <stdio.h>
#include "DemoTest.h"
#include "im.h"

class DemoModel : public DemoTest
{
public:
	DemoModel()
	{
	}
	~DemoModel()
	{
	}

	Camera * camera;
	Shader * ourShader;
	Model * ourModel;

	void Initlization() override;

	void Render_SceneObject() override;
};

#endif /* DemoModel_h */
