#include "Screen.h"
#include <iostream>
using namespace std;

//void Screen::Init()
//{
//	cout << "Hello World" << endl;
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();                                                     //��ʼ��glfw
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  //�������汾�� 3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  //���ôΰ汾�� 3  ---��glfw 3.3
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //ʹ�õ��Ǻ���ģʽ(Core-profile)
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
//	glfwMakeContextCurrent(window);                                     //֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳�����������
//
//																		//---------------GLAD����������OpenGL�ĺ���ָ���---------------
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return;
//	}
//
//	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);                            //ǰ�����������ƴ������½ǵ�λ�á�����,�ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  //ע��һ�����ڱ仯���¼� ��Ҳ�ͻ�ÿ���ߴ�仯�͵��õĺ���
//	glfwSetCursorPosCallback(window, mouse_callback);                   //ע��һ������ƶ����¼�
//	glfwSetScrollCallback(window, scroll_callback);                     //ע����ֻ������¼�
//
//	glEnable(GL_DEPTH_TEST);                                            //����3D����Ҫ��Ȳ��ԣ�ǰ������
//																		//-----------��ʼ����GLSL---------
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
//	//��׼�������꣬0��0 �������� ����λ�ö��ǰٷֱ�
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
//	//--------- OpenGL --����------
//	unsigned int VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);               //���û�������ID
//
//										 // 1. ��VAO
//	glBindVertexArray(VAO);             //Ҫ��ʹ��VAO��Ҫ����ֻ��ʹ��glBindVertexArray��VAO
//										// 2. �Ѷ������鸴�Ƶ������й�OpenGLʹ��
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //���´�����vbo ������� �󶨵� GL_ARRAY_BUFFER��
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //�Ѷ����������Ϣ���Ƶ� VBO���ڴ�ռ���ȥ
//
//																			   /*
//																			   GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣  λ�����ݲ���ı䣬ÿ����Ⱦ����ʱ������ԭ������������ʹ�����������GL_STATIC_DRAW
//																			   GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ       һ�������е����ݽ�Ƶ�����ı�
//																			   GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣  ��������ȷ���Կ������ݷ����ܹ�����д����ڴ沿�֡�
//																			   */
//																			   ///��ʵ�����������һƬ�ڴ�ռ䣬Ȼ�����ڴ�ռ�����д����
//																			   //------------------------
//																			   // 3. ���ö�������ָ��
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	/*
//	��һ������ָ������Ҫ���õĶ������ԡ����ǵ������ڶ�����ɫ����ʹ��layout(location = 0)������position�������Ե�λ��ֵ(Location)�������԰Ѷ������Ե�λ��ֵ����Ϊ0����Ϊ����ϣ�������ݴ��ݵ���һ�����������У������������Ǵ���0��
//	�ڶ�������ָ���������ԵĴ�С������������һ��vec3������3��ֵ��ɣ����Դ�С��3��
//	����������ָ�����ݵ����ͣ�������GL_FLOAT(GLSL��vec*�����ɸ�����ֵ��ɵ�)��
//	�¸��������������Ƿ�ϣ�����ݱ���׼��(Normalize)�������������ΪGL_TRUE���������ݶ��ᱻӳ�䵽0�������з�����signed������-1����1֮�䡣���ǰ�������ΪGL_FALSE��
//	�����������������(Stride)�������������������Ķ���������֮��ļ���������¸���λ��������3��float֮�����ǰѲ�������Ϊ3 * sizeof(float)��Ҫע�������������֪����������ǽ������еģ���������������֮��û�п�϶������Ҳ��������Ϊ0����OpenGL�������岽���Ƕ��٣�ֻ�е���ֵ�ǽ�������ʱ�ſ��ã���һ�������и���Ķ������ԣ����Ǿͱ����С�ĵض���ÿ����������֮��ļ���������ں���ῴ����������ӣ���ע: �����������˼��˵���Ǵ�������Եڶ��γ��ֵĵط�����������0λ��֮���ж����ֽڣ���
//	���һ��������������void*��������Ҫ���ǽ��������ֵ�ǿ������ת��������ʾλ�������ڻ�������ʼλ�õ�ƫ����(Offset)������λ������������Ŀ�ͷ������������0�����ǻ��ں�����ϸ�������������
//	*/
//	glEnableVertexAttribArray(0);                                       //�Զ�������λ��ֵ��Ϊ���������ö�������
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
//	while (!glfwWindowShouldClose(window))                               //����һ����Ⱦѭ��
//	{
//		float currentFrame = glfwGetTime();                             //������֮֡���ʱ���
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		processInput(window);                                           //����ÿ֡�ļ�������
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);            // also clear the depth buffer now!
//
//																	   // 4. ��������
//																	   // bind textures on corresponding texture units
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//
//		ourShader.use();
//		glm::mat4 projection;
//		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); //������ƽ��ͷ��
//																													  //                        45.0f����Ұ                     ��߱�                ��ƽ�����       Զƽ�����
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
//		glfwSwapBuffers(window);                                        //˫���彻�� --���»���
//		glfwPollEvents();
//	}
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	glfwTerminate();                                                    //�������ͷ���Դ
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
