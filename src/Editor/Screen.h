#include <GLFW/glfw3.h>
#ifndef glm
#define glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif 

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

#if defined(_WIN32)
#if defined(NANOGUI_BUILD)
#      define TmingAPI __declspec(dllexport)
#else
#      define TmingAPI __declspec(dllimport)
#endif
#endif

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  //函数声明，当窗口大小调整时触发的函数
void processInput(GLFWwindow *window);                                      //处理按键输入的函数
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);          //鼠标处理函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);   //滚轮处理函数

																			// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));                                 //默认相机的参数
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;                                                     //每帧执行需要加权平均一下
float lastFrame = 0.0f;

#if !Debug
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 去掉黑色控制台窗口
#endif //  !Debug

class Screen
{
public:
	Screen();
	~Screen();
	void Init();
private:
};