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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  //���������������ڴ�С����ʱ�����ĺ���
void processInput(GLFWwindow *window);                                      //����������ĺ���
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);          //��괦����
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);   //���ִ�����

																			// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));                                 //Ĭ������Ĳ���
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;                                                     //ÿִ֡����Ҫ��Ȩƽ��һ��
float lastFrame = 0.0f;

#if !Debug
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // ȥ����ɫ����̨����
#endif //  !Debug

class Screen
{
public:
	Screen();
	~Screen();
	void Init();
private:
};