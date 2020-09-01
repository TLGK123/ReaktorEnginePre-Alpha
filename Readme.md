![在这里插入图片描述](https://img-blog.csdnimg.cn/20200703085730198.jpg)  

# TmingEngine
@[toc]
## Open Source 
[https://github.com/xiaomingfun/TmingEngine](https://github.com/xiaomingfun/TmingEngine)
## UI Library
 >TmingEnggine use a open source UI framework named  [dear-imgui](https://github.com/ocornut/imgui) . The advantage of this framework is easy using ，convenient extension ，little limilimit with using MIT LICENSE 。So we can easy to develop a game editor by import this framework.

My goal is to develop a full-platform Editor (Windows Mac Linux) ,then I need to abstract a windows layer，above this abstract layer to develop the game engine editor。So I use OpenGL  for backend rendering，use  glfw to create a windows , finally use the dear-imgui to build editor layout widget 。I want to use vulkan to replace the OpenGL in the future。If the abstract windows layer design good enough ，then we can easy to change backend rendering library.
 
 ## The Editor Layout
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200712175513449.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L25hbl9mZW5nX3l1,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200712175527528.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L25hbl9mZW5nX3l1,size_16,color_FFFFFF,t_70)

>Even though I have used Unity for a long time , but I still don't know why Unity have  to design those widgets . But those layout design is the really reason that I change use the tool from Cocos to Unity. Because of the  continuation  of the user habit , as a beginner ，we can also fellow the old version  tutorial to exercise in the the latest editor tool .

So the design of TmingEngine editor , I just imitate the Unity . I will learn other 3D rendering  tool UI layout , then bring the good design to  my  project.

## Current Focus on-------Shader
>  It's a demo stage  now ,so we can't develop all part of a completed engine at the same time. So I focus on support a convenient IDE to test and display the shader ，then  to finish other part of a completed engine.

## Soft Rendering
I have imported a soft rendering framework [tinyrenderer](https://github.com/ssloy/tinyrenderer) to TmingEngine . We can make the vertext shader and fragment shader by just writting c++ code directly .

 Because all the part of the  rendering pipeline we defined by ourself , so we can just use c++ code to change the model's vertext  and the screen pixel color , and we can make a breakpoint at the runtime. But a model maybe have a thousand of vertext , therefore the performance of soft rendering will be not effective enough. 

## Internal Shader Code Editor 
Thrid part Code editor   [ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit)
Use this code editor we can  write glsl shader more easy , maybe support other feature in the future.
We can select a glsl file at the editor asset layout  , then the shader code will be open .

## Editor Download Link
[Windows 64](https://download.csdn.net/download/nan_feng_yu/11871143) (outdated)
[MacOS](https:prepa//download.csdn.net/download/nan_feng_yu/11870943) (outdated)

## Building
## The Required Tools 

CMake [https://cmake.org](https://cmake.org) 

### Build the Project
## Windows （Visual Studio）
1. git clone https://github.com/xiaomingfun/TmingEngine
2. cd TmingEngine
3. click GenerateProject.bat 
4. open the build/TmingEngine.sln
5. enjoy it !!

## Mac OS & Windows （Xcode & Visual Studio）
1. git clone https://github.com/xiaomingfun/TmingEngine
2. You can use CMake GUI Tool the generate the Project to build folder 
      1. CMake GUI Tool :  Set Source Path (path/to/TmingEngine)
      2. CMake GUI Tool :  Set Binary Source Path (path/to/TmingEngine/build)
      3. Congigure 
      4. Genarate
      5. Open Project
3. enjoy it !!

## Linux & Mac OS  （Unix Makefile）
1. git clone https://github.com/xiaomingfun/TmingEngine
2. cd TmingEngine
3. ./GenerateProject.sh
4. enjoy it !!

## Roadmap
- [x] import assimp by source code
- [x] Auto docking layout  that windows can mixing and dispersing
- [x] write math lib by myself
- [ ] optimize the scene view for editor
- [ ] export iOS project
- [x] Base on the Editor framework ,create a independent window
- [x] Project file manager to display file
- [x] internal code editor
- [x] add preview to display a picture
- [x] test lua and AngleScript
- [ ] using script to write editor layout 
- [x] load a model from file manager 
- [x] 使用思源字体支持中文
 



#  The reference 

1.  [https://github.com/BalazsJako/ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit) 
2. [https://github.com/ocornut/imgui](https://github.com/ocornut/imgui)  
3. [https://github.com/PanosK92/SpartanEngine](https://github.com/PanosK92/SpartanEngine) 
4. [https://github.com/urho3d/Urho3D](https://github.com/urho3d/Urho3D)  
5. [https://github.com/assimp/assimp](https://github.com/assimp/assimp) 
6. [https://github.com/erincatto/Box2D](https://github.com/erincatto/Box2D) 
7. [https://github.com/Dav1dde/glad](https://github.com/Dav1dde/glad) 
8. [https://github.com/g-truc/glm](https://github.com/g-truc/glm)
9. [https://github.com/rokups/ImNodes](https://github.com/rokups/ImNodes) 
10. [https://github.com/nothings/stb](https://github.com/nothings/stb)  
11. [https://github.com/jbeder/yaml-cpp](https://github.com/jbeder/yaml-cpp) 
12. [http://www.angelcode.com/angelscript/](http://www.angelcode.com/angelscript/)
13. [https://github.com/adobe-fonts/source-han-sans/tree/release](https://github.com/adobe-fonts/source-han-sans/tree/release)
14. [https://github.com/ssloy/tinyrenderer](https://github.com/ssloy/tinyrenderer)
15. [http://www.yinwang.org/blog-cn/2012/08/01/interpreter](http://www.yinwang.org/blog-cn/2012/08/01/interpreter)