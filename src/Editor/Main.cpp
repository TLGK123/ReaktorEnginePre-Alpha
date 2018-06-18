//
//  Main.c
//  Editor
//
//  Created by blue on 2018/6/16.
//

#include <glad/glad.h>
/*
 OpenGL只是一个标准/规范，具体的实现是由驱动开发商针对特定显卡实现的。
 由于OpenGL驱动版本众多，它大多数函数的位置都无法在编译时确定下来，需要在运行时查询。
 
 // 定义函数原型
 typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
 // 找到正确的函数并赋值给函数指针
 GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
 // 现在函数可以被正常调用了
 GLuint buffer;
 glGenBuffers(1, &buffer);
 
 */

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
void processInput(GLFWwindow *window);                                      //处理按键输入的函数

//#if !Debug
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 去掉黑色控制台窗口
//#endif //  !Debug

//---------------------Data-------------
float vertrices[] ={
    -0.5f,-0.5,0.0f,
    0.5f,0.5f,0.0f,
    0.0f,0.5f,0.0f
};                                                                  //标准化的坐标，0，0 在正中心 其他位置都是百分比

//---------------------Edn Data---------
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
    
    //--------- OpenGL --对象------
    unsigned  int VBO;
    glGenBuffers(1,&VBO);               //设置缓冲对象的ID
    glBindBuffer(GL_ARRAY_BUFFER,VBO);  //把新创建的vbo 缓存对象 绑定到 GL_ARRAY_BUFFER上
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertrices),vertrices,GL_STATIC_DRAW); //把顶点的数据信息复制到 VBO的内存空间中去
    
    /*
     GL_STATIC_DRAW ：数据不会或几乎不会改变。  位置数据不会改变，每次渲染调用时都保持原样，所以它的使用类型最好是GL_STATIC_DRAW
     GL_DYNAMIC_DRAW：数据会被改变很多。       一个缓冲中的数据将频繁被改变
     GL_STREAM_DRAW ：数据每次绘制时都会改变。  这样就能确保显卡把数据放在能够高速写入的内存部分。
     */
    ///其实这个就是申请一片内存空间，然后向内存空间里面写数据
    //-----------
    
    
    //-----------开始加入GLSL---------
    
    char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);    //创建一个 GL_VERTEX_SHADER 类型的shader
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);   // 1是源代码的数量
    glCompileShader(vertexShader);
    int success;
    char info[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,512,NULL,info);
        std::cout<<"Shader 编译出差："<<info<<endl;
        
    }
    //------------GLSL---------end--------
    
    
    
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);                                     //通知GLFW将我们窗口的上下文设置为当前线程的主上下文了
    
    
    //---------------GLAD是用来管理OpenGL的函数指针的---------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glViewport(0, 0, 800, 600);                                         // 前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  //注册一个窗口变化的事件 ，也就会每当尺寸变化就调用的函数
    
    
    while(!glfwWindowShouldClose(window))                               //开启一个渲染循环
    {
        processInput(window);                                           //处理每帧的键盘输入
       
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window);                                        //双缓冲交换 --更新画面
        glfwPollEvents();
    }
    glfwTerminate();                                                    //结束后释放资源
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)                    //添加按键判断
        glfwSetWindowShouldClose(window, true);
}
