# 游戏引擎编辑器
@[toc]
## UI图形库
 >编辑器图形库使用的是开源框架imgui。这个开源的UI框架的特点是方便，容易使用，扩展性很强，使用的MIT的开源协议。所以能够很好的进行二次开发，定制自己引擎的样子。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;因为想要进行跨平台的编辑器的开发设计，所以需要基于一个全平台都能使用的windows窗口抽象层，基于这个抽象层，上使用imgui进行界面设计。所以我选择使用OpenGL + imgui 进行开发，利用OpenGL中对于窗口抽象的库，glfw来创建窗口。再利用imgui绘制窗口。未来可以将OpenGL替换为vulkan 。只要上层的图形抽象做好，就可以进行底层图形库的替换。
 
 ## 界面功能布局设计
![在这里插入图片描述](https://img-blog.csdnimg.cn/20191026222140968.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L25hbl9mZW5nX3l1,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20191026231337406.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L25hbl9mZW5nX3l1,size_16,color_FFFFFF,t_70)
>虽然自己作为长久的Unity使用者，但是对于引擎编辑器的功能区，的设计并没有非常深入的了解，但是，Unity吸引我从cocos转向它，正是因为它有良好的用户习惯的延续，对于初学者，针对老的教程也能在新版本中有比较容易的过渡，在经历了大版本的更新后，也没有改变大体 布局，这个为学习者提供了良好的过渡。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;所以对于，Unity编辑器界面的设计，目前阶段就是模仿Unity做的，自己也同样做一个出来。同时也会去关注一些，主流的3D模型软件的界面操作，将更加优秀的布局设计和功能带到自己的引擎中。

## 目前阶段侧重点---Shader展示
> 当前处于游戏引擎开发的最初级阶段，力图从各个方面进行完善不太现实。所以当前主要的侧重点在于针对Shader学习，提供一个良好的IDE环境，这个环境界面其实就是游戏引擎的雏形应该要有的功能。

 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于一个良好的Shader编译，运行，调试开发和纠错环境。需要的基本功能，就是和真正的3D游戏开发极其类似，所以我希望自己能在某个部分有所突破和创新以后，逐步完善游戏引擎的每个功能模块。
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

## 内置Shader代码编辑器(第三方库)
### [ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit)
这个是我移植进去的,第三方代码编辑库,使用的imgui框架,简单轻巧.也一直在保持更新
### Shader语法高亮
其实对语法的高亮,就是对于特定的一些关键词,进行不同颜色标记,在代码编辑器中,预先存下所有关于shader的关键词,再对关键词进行匹配判断,进行颜色区分就可以形成语法.
### 资源管理自动打开Shader
现在能够在资源管理器中,点击.vs 或者.fs 后缀的glsl 的shader文件.能够直接显示,但是目前没有加上保存功能,因为代码编辑器的源码没有,完全吸收.可能存在错误编辑.比如字体和字符集的问题,可能导致保存文件无法下次被正确读取.所有暂时不开放代码修改后的保存功能,尽量目前编辑shader代码还是使用vscode

## 编辑器下载连接
 [PC下的64位编辑器](https://download.csdn.net/download/nan_feng_yu/11871143)
[MacOS的64位编辑器](https://download.csdn.net/download/nan_feng_yu/11870943) 

## 数字内容管理
> 数字容管理,简单来说就是文件夹管理,资源管理器.管理自己游戏中用到的资源.既然要管理这些资源.
> 既然要管理这些资源,所以肯定得有不同资源的解析器parser . 有些资源的格式是专有的 ,有格式保护,那么
> 就需要去下载官方的sdk工具.比如 fbx,就需要专门的sdk.其他的格式比如 obj就不需要,可以直接自己解析.

## 计划蓝图
- [x] 完成 assimp 库的源码导入
- [x] Docking动态编辑合并界面独立窗口
- [x] 优化视窗点
- [ ] 完善自己写的数学库
- [x] 编辑器Scene 窗口全屏显示
- [ ] 底层渲染引擎使用OpenGL ES 3.0
- [ ] 确定跨平台窗口框架
- [ ] 接入跨平台窗口的第三方库
- [ ] 完成项目到iOS的工程导出
- [x] 基于引擎编辑器窗口,再创建窗口
- [x] 资源管理器,一级列表界面显示资源
- [ ] 资源管理器,二级界面显示文件图标
- [x] 独立处理代码编辑器
- [x] 添加预览器,针对图片进行预览
- [ ] scene界面看模型窗口缩放不会导致画面压缩
 

# 游戏引擎运行时
## 系统的启动和结束
>由于 c++  静态类,无法控制初始化函数,但是系统的启动,需要控制每个组件的启动顺序.所以可以把初始化类的一些操作,单独抽象到一个init函数中

可以在类下构造函数中,去注册一些,它需要的系统,但是不进行初始化,把初始化留在另一个人为控制的函数中,这样就可以,控制初始化的时机.
## 时间连续性
> 这个就是指的,游戏是一直在玩的一种软件.是连续一段时间内的操作.不可以间隔开的.打开游戏一直玩,不过这个也是相对的.比如现在流行的回合卡牌战斗游戏.这些号称只要5分钟可以解决的战斗.但是游戏依然是在一个时间段内,持续操作的,互相反馈的事.
## 游戏对象抽象
>游戏中有太多的对象,目前对于游戏对象的抽象有些设计成为 GameObject
## 接受用户输入
>针对键盘,鼠标,手柄等等控制器,输入设备,识别后.定义按键映射,就能控制游戏中角色的状态.


# 引用和参考的第三方开源库

1. [https://github.com/BalazsJako/ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit) 基于imgui的文本编辑库 :
2. [https://github.com/ocornut/imgui](https://github.com/ocornut/imgui)  开源c++ 编辑器 UI 封装库,强大简易
3. [https://github.com/PanosK92/SpartanEngine](https://github.com/PanosK92/SpartanEngine) 开源的游戏引擎 ,代码结构简单优雅,目前有大量代码参考;来源于此引擎
4. [https://github.com/urho3d/Urho3D](https://github.com/urho3d/Urho3D)  开源游戏引擎, 大量的编译脚本代码CMakeList.txt ,来源于此引擎
5. [https://github.com/assimp/assimp](https://github.com/assimp/assimp) 开源3D模型资源解析,转换,输出库
6. [https://github.com/erincatto/Box2D](https://github.com/erincatto/Box2D) 开源2D物理碰撞引擎库
7. [https://github.com/Dav1dde/glad](https://github.com/Dav1dde/glad) OpenGL函数自动加载辅助库
8. [https://github.com/g-truc/glm](https://github.com/g-truc/glm) 针对OpenGL 方便使用的线性代数数学库
9. [https://github.com/rokups/ImNodes](https://github.com/rokups/ImNodes) 基于imgui的节点编辑器
10. [https://github.com/nothings/stb](https://github.com/nothings/stb)  支持各种格式的图片加载器
11. [https://github.com/jbeder/yaml-cpp](https://github.com/jbeder/yaml-cpp) 场景,预制,配置文件,序列化
12. [http://www.libsdl.org/](http://www.libsdl.org/) SDL跨平台窗口环境提供库
13. [https://github.com/thedmd/imgui-node-editor](https://github.com/thedmd/imgui-node-editor) 一个比较完整的,基于imgui的蓝图编辑器
