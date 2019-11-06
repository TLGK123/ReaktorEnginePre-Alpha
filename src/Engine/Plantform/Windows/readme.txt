这个是窗口层，针对不同的平台，对接产生原生的窗口。
目前，打算使用SDL来创建窗口环境。SDL可以创建多个平台的窗口环境。
对于不同的平台，main函数也不一样。

This is a windows layer that used for generate a native windows context.
The window context is used for hight level Graphic API like for OpenGL , vulkan , DX11.
As we know , different platform have differnet main function ,So this layer will handle 
all this preoblem. Now , we use SDL to generate windows context ,then use OpenGL to draw windows.