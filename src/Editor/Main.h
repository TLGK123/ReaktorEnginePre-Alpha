//
//  Main.h
//  Editor
//
//  Created by blue on 2018/6/16.
//

#ifndef Main_h
#define Main_h
#include"Screen.h"
#include <stdio.h>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;										// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));                                 //默认相机的参数
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;                                                     //每帧执行需要加权平均一下
float lastFrame = 0.0f;

#endif /* Main_h */
