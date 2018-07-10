#include "Screen.h"
#include <iostream>
using namespace std;

//void Screen::Init()
//{
//	cout << "Hello World" << endl;
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();                                                     //初始化glfw
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  //设置主版本号 3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  //设置次版本号 3  ---》glfw 3.3
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //使用的是核心模式(Core-profile)
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // uncomment this statement to fix compilation on OS X
//#endif
//
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TmingEngine", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return;
//	}
//	glfwMakeContextCurrent(window);                                     //通知GLFW将我们窗口的上下文设置为当前线程的主上下文了
//
//																		//---------------GLAD是用来管理OpenGL的函数指针的---------------
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return;
//	}
//
//	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);                            //前两个参数控制窗口左下角的位置。第三,四个参数控制渲染窗口的宽度和高度（像素）
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  //注册一个窗口变化的事件 ，也就会每当尺寸变化就调用的函数
//	glfwSetCursorPosCallback(window, mouse_callback);                   //注册一个鼠标移动的事件
//	glfwSetScrollCallback(window, scroll_callback);                     //注册滚轮滑动的事件
//
//	glEnable(GL_DEPTH_TEST);                                            //进入3D后需要深度测试，前后分清楚
//																		//-----------开始加入GLSL---------
//	Shader ourShader("7.4.camera.vs", "7.4.camera.fs");
//	//------------GLSL---------end--------
//
//	//---------------------Data-------------
//	float vertices[] = {
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//	};
//	//标准化的坐标，0，0 在正中心 其他位置都是百分比
//	glm::vec3 cubePositions[] = {
//		glm::vec3(0.0f,  0.0f,  0.0f),
//		glm::vec3(2.0f,  5.0f, -15.0f),
//		glm::vec3(-1.5f, -2.2f, -2.5f),
//		glm::vec3(-3.8f, -2.0f, -12.3f),
//		glm::vec3(2.4f, -0.4f, -3.5f),
//		glm::vec3(-1.7f,  3.0f, -7.5f),
//		glm::vec3(1.3f, -2.0f, -2.5f),
//		glm::vec3(1.5f,  2.0f, -2.5f),
//		glm::vec3(1.5f,  0.2f, -1.5f),
//		glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//	//---------------------Edn Data---------
//
//	//--------- OpenGL --对象------
//	unsigned int VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);               //设置缓冲对象的ID
//
//										 // 1. 绑定VAO
//	glBindVertexArray(VAO);             //要想使用VAO，要做的只是使用glBindVertexArray绑定VAO
//										// 2. 把顶点数组复制到缓冲中供OpenGL使用
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //把新创建的vbo 缓存对象 绑定到 GL_ARRAY_BUFFER上
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //把顶点的数据信息复制到 VBO的内存空间中去
//
//																			   /*
//																			   GL_STATIC_DRAW ：数据不会或几乎不会改变。  位置数据不会改变，每次渲染调用时都保持原样，所以它的使用类型最好是GL_STATIC_DRAW
//																			   GL_DYNAMIC_DRAW：数据会被改变很多。       一个缓冲中的数据将频繁被改变
//																			   GL_STREAM_DRAW ：数据每次绘制时都会改变。  这样就能确保显卡把数据放在能够高速写入的内存部分。
//																			   */
//																			   ///其实这个就是申请一片内存空间，然后向内存空间里面写数据
//																			   //------------------------
//																			   // 3. 设置顶点属性指针
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	/*
//	第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
//	第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
//	第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
//	下个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
//	第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，我们把步长设置为3 * sizeof(float)。要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，我们在后面会看到更多的例子（译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节）。
//	最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。
//	*/
//	glEnableVertexAttribArray(0);                                       //以顶点属性位置值作为参数，启用顶点属性
//
//																		// color attribute
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	unsigned int texture1, texture2;
//	// texture 1
//	// ---------
//	glGenTextures(1, &texture1);
//	glBindTexture(GL_TEXTURE_2D, texture1);
//	// set the texture wrapping parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	// set texture wrapping to GL_REPEAT (default wrapping method)
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	// set texture filtering parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	// load image, create texture and generate mipmaps
//	int width, height, nrChannels;
//
//	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//											// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
//	unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
//	// texture 2
//	// ---------
//	glGenTextures(1, &texture2);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//	// set the texture wrapping parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	// set texture filtering parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	// load image, create texture and generate mipmaps
//	data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
//
//	ourShader.use();
//	// either set it manually like so:
//	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
//	// or set it via the texture class
//	ourShader.setInt("texture1", 0);
//	ourShader.setInt("texture2", 1);
//
//	while (!glfwWindowShouldClose(window))                               //开启一个渲染循环
//	{
//		float currentFrame = glfwGetTime();                             //计算两帧之间的时间差
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		processInput(window);                                           //处理每帧的键盘输入
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);            // also clear the depth buffer now!
//
//																	   // 4. 绘制物体
//																	   // bind textures on corresponding texture units
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//
//		ourShader.use();
//		glm::mat4 projection;
//		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); //创建了平截头体
//																													  //                        45.0f是视野                     宽高比                近平面距离       远平面距离
//		ourShader.setMat4("projection", projection);
//
//		glm::mat4 view = camera.GetViewMatrix();
//		ourShader.setMat4("view", view);
//
//		// render container
//		glBindVertexArray(VAO);
//		for (unsigned int i = 0; i < 10; i++)
//		{
//			// calculate the model matrix for each object and pass it to shader before drawing
//			glm::mat4 model;
//			model = glm::translate(model, cubePositions[i]);
//			float angle = 20.0f * i;
//			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//			ourShader.setMat4("model", model);
//
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//
//		glfwSwapBuffers(window);                                        //双缓冲交换 --更新画面
//		glfwPollEvents();
//	}
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	glfwTerminate();                                                    //结束后释放资源
//	return;
//}
//
//Screen::~Screen()
//{
//}
//
//Screen::Screen()
//{
//}
