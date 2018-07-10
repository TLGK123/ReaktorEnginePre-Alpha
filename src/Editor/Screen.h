#ifndef Screen_h
#define Screen_h

#endif // !Screen_h

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  //���������������ڴ�С����ʱ�����ĺ���
void processInput(GLFWwindow *window);                                      //����������ĺ���

void mouse_callback(GLFWwindow* window, double xpos, double ypos);          //��괦����
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);   //���ִ�����

#if defined(_WIN32)
#if defined(NANOGUI_BUILD)
#      define TmingAPI __declspec(dllexport)
#else
#      define TmingAPI __declspec(dllimport)
#endif
#endif

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
