//
//  DemoModel.cpp
//  Editor
//
//  Created by blue on 2018/9/4.
//
#define STB_IMAGE_IMPLEMENTATION

#include "DemoModel.h"

void DemoModel::Render_SceneObject() {
	// render
	// ------
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// don't forget to enable shader before setting uniforms
	ourShader->use();

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)1366 / (float)768, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	ourShader->setMat4("projection", projection);
	ourShader->setMat4("view", view);

	// render the loaded model
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));    // it's a bit too big for our scene, so scale it down
	ourShader->setMat4("model", model);
	ourModel->Draw(*ourShader);
}

void DemoModel::Initlization() {
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	ourShader = new Shader();
	ourModel = new Model();
	ourShader->Init("1.model_loading.vs", "1.model_loading.fs");
	ourModel->Init(FileSystem::getPath("resources/objects/nanosuit/nanosuit.obj"));
}