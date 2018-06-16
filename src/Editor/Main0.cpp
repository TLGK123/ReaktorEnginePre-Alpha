//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <learnopengl/shader_m.h>
//#include <learnopengl/camera.h>
//#include <learnopengl/model.h>
//#include <iostream>
//
//#include "imgui.h"
//#include "imgui_impl_glfw_gl3.h"
//
//#if !Debug
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址
//#endif //  !Debug
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//
//// settings
//const unsigned int SCR_WIDTH = 1366;
//const unsigned int SCR_HEIGHT = 768;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//
//int main()
//{
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//
//														 // glfw window creation
//														 // --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TmingEngine", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// tell GLFW to capture our mouse
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// glad: load all OpenGL function pointers
//	// ---------------------------------------
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// configure global opengl state
//	// -----------------------------
//	glEnable(GL_DEPTH_TEST);
//
//	// build and compile shaders
//	// -------------------------
//	Shader ourShader("1.model_loading.vs", "1.model_loading.fs");
//
//	// load models
//	// -----------
//	Model ourModel(FileSystem::getPath("resources/objects/nanosuit/nanosuit.obj"));
//
//
//	// draw in wireframe
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	// render loop
//	// -----------
//
//
//	// Setup ImGui binding
//	ImGui::CreateContext();
//	ImGuiIO& io = ImGui::GetIO(); (void)io;
//	ImGui_ImplGlfwGL3_Init(window, true);
//
//	// Setup style
//	ImGui::StyleColorsDark();
//
//	bool show_demo_window = true;
//	bool show_another_window = false;
//	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//
//	while (!glfwWindowShouldClose(window))
//	{
//
//		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
//		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
//		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
//		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
//		glfwPollEvents();
//		ImGui_ImplGlfwGL3_NewFrame();
//
//		// 1. Show a simple window.
//		// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
//		{
//			static float f = 0.0f;
//			static int counter = 0;
//			ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
//			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
//			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
//
//			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
//			ImGui::Checkbox("Another Window", &show_another_window);
//
//			if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
//				counter++;
//			ImGui::SameLine();
//			ImGui::Text("counter = %d", counter);
//
//			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//		}
//
//		// 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name your windows.
//		if (show_another_window)
//		{
//			ImGui::Begin("Another Window", &show_another_window);
//			ImGui::Text("Hello from another window!");
//			if (ImGui::Button("Close Me"))
//				show_another_window = false;
//			ImGui::End();
//		}
//
//		// 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
//		if (show_demo_window)
//		{
//			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
//			ImGui::ShowDemoWindow(&show_demo_window);
//		}
//
//		//创建一个帧缓冲
//		unsigned int fbo;
//		glGenFramebuffers(1, &fbo);
//		//激活的(Active)帧缓冲
//		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//
//		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
//		{
//		}
//			// 执行胜利的舞蹈
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		glDeleteFramebuffers(1, &fbo);
//
//		unsigned int texture;
//		glGenTextures(1, &texture);
//		glBindTexture(GL_TEXTURE_2D, texture);
//
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
//		glTexImage2D(
//			GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0,
//			GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
//		);
//		unsigned int rbo;
//		glGenRenderbuffers(1, &rbo);
//		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
//
//		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
//		unsigned int framebuffer;
//		glGenFramebuffers(1, &framebuffer);
//		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//		// 生成纹理
//		unsigned int texColorBuffer;
//		glGenTextures(1, &texColorBuffer);
//		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glBindTexture(GL_TEXTURE_2D, 0);
//
//		// 将它附加到当前绑定的帧缓冲对象
//		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
//		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//
//
//		// per-frame time logic
//		// --------------------
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		// -----
//		processInput(window);
//
//		// render
//		// ------
//		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// don't forget to enable shader before setting uniforms
//		ourShader.use();
//
//		// view/projection transformations
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		ourShader.setMat4("projection", projection);
//		ourShader.setMat4("view", view);
//
//		// render the loaded model
//		glm::mat4 model;
//		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
//		ourShader.setMat4("model", model);
//		ourModel.Draw(ourShader);
//
//
//		ImGui::Render();
//		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	ImGui_ImplGlfwGL3_Shutdown();
//	ImGui::DestroyContext();
//	// glfw: terminate, clearing all previously allocated GLFW resources.
//	// ------------------------------------------------------------------
//	glfwTerminate();
//	return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//
//	ImGuiIO& io = ImGui::GetIO();
//	bool mouseOnScene = io.WantCaptureMouse != 1;
//	bool rightMouseDown = (io.MouseDownDuration[1] >= 0.0f);
//	if (mouseOnScene && rightMouseDown)
//	{
//		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//			camera.ProcessKeyboard(FORWARD, deltaTime);
//		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//			camera.ProcessKeyboard(BACKWARD, deltaTime);
//		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//			camera.ProcessKeyboard(LEFT, deltaTime);
//		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//			camera.ProcessKeyboard(RIGHT, deltaTime);
//	}
//
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	ImGuiIO& io = ImGui::GetIO();
//
//	//ImGui::Text("WantCaptureMouse: %d", io.WantCaptureMouse);
//
//	bool mouseOnScene = io.WantCaptureMouse != 1;
//    bool rightMouseDown = (io.MouseDownDuration[1] >= 0.0f);
//	if (mouseOnScene && rightMouseDown)
//	{
//		camera.ProcessMouseMovement(xoffset, yoffset);
//	}	
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}