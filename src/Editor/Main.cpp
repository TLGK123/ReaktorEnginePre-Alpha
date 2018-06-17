//
//  Main.c
//  Editor
//
//  Created by blue on 2018/6/16.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

#include "Main.h"
#include <iostream>
using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);  //函数声明，当窗口大小调整时触发的函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main ()
{
    cout<<"Hello World"<<endl;
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();                                                     //初始化glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  //设置主版本号 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  //设置次版本号 3  ---》glfw 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //使用的是核心模式(Core-profile)
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // uncomment this statement to fix compilation on OS X
#endif
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);                                 //通知GLFW将我们窗口的上下文设置为当前线程的主上下文了
    
    
    //---------------GLAD是用来管理OpenGL的函数指针的---------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glViewport(0, 0, 800, 600);                                     // 前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  //注册一个窗口变化的事件 ，也就会每当尺寸变化就调用的函数
    
    
    while(!glfwWindowShouldClose(window))                               //开启一个渲染循环
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}
