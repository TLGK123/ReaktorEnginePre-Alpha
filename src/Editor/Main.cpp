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

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}";

#if !Debug
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 去掉黑色控制台窗口
#endif //  !Debug

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
    glfwMakeContextCurrent(window);                                     //通知GLFW将我们窗口的上下文设置为当前线程的主上下文了
    
    
    //---------------GLAD是用来管理OpenGL的函数指针的---------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glViewport(0, 0, 800, 600);                                         // 前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  //注册一个窗口变化的事件 ，也就会每当尺寸变化就调用的函数
    
    
    //-----------开始加入GLSL---------
    
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);           //创建一个 GL_VERTEX_SHADER 类型的shader
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);   // 1是源代码的数量
    glCompileShader(vertexShader);                             //编译顶点shader
    int success;
    char info[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);    //获取编译的信息，比如是否出差，错在哪
    
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,512,NULL,info);
        std::cout<<"Shader 编译出差："<<info<<endl;
        
    }
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);        //创建一个片段shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();                         //创建一个渲染的着色器程序(Shader Program)
    
    glAttachShader(shaderProgram, vertexShader);               //附加顶点shader
    glAttachShader(shaderProgram, fragmentShader);             //附加片段shader
    glLinkProgram(shaderProgram);                              //链接上shader
    
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);   //检测shader链接出错信息
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, info);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info << std::endl;
    }
    
    glDeleteShader(vertexShader);                               //删除使用过的数据
    glDeleteShader(fragmentShader);
    
    //------------GLSL---------end--------
    
    //---------------------Data-------------
    float vertices[] ={
        -0.5f,-0.5,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f
    };                                                                  //标准化的坐标，0，0 在正中心 其他位置都是百分比
    
    //---------------------Edn Data---------
    
    
    //--------- OpenGL --对象------
    unsigned int VBO ,VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);               //设置缓冲对象的ID
    
    // 1. 绑定VAO
    glBindVertexArray(VAO);             //要想使用VAO，要做的只是使用glBindVertexArray绑定VAO
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER,VBO);  //把新创建的vbo 缓存对象 绑定到 GL_ARRAY_BUFFER上
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW); //把顶点的数据信息复制到 VBO的内存空间中去
    
    /*
     GL_STATIC_DRAW ：数据不会或几乎不会改变。  位置数据不会改变，每次渲染调用时都保持原样，所以它的使用类型最好是GL_STATIC_DRAW
     GL_DYNAMIC_DRAW：数据会被改变很多。       一个缓冲中的数据将频繁被改变
     GL_STREAM_DRAW ：数据每次绘制时都会改变。  这样就能确保显卡把数据放在能够高速写入的内存部分。
     */
    ///其实这个就是申请一片内存空间，然后向内存空间里面写数据
    //------------------------
    // 3. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    /*
     第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
     第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
     第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
     下个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
     第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，我们把步长设置为3 * sizeof(float)。要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，我们在后面会看到更多的例子（译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节）。
     最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。
     */
    glEnableVertexAttribArray(0);                                       //以顶点属性位置值作为参数，启用顶点属性
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    while(!glfwWindowShouldClose(window))                               //开启一个渲染循环
    {
        processInput(window);                                           //处理每帧的键盘输入
       
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 4. 绘制物体
        glUseProgram(shaderProgram);                                   // 当我们渲染一个物体时要使用着色器程序
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);                                        //双缓冲交换 --更新画面
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
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
