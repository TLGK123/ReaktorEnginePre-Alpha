//The MIT License
//
//Copyright(c) 2016 - 2020 littleblue
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//copies of the Software, and to permit persons to whom the Software is furnished
//to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#include "Project.h"

void AssetTree(string path);
void AssetTreeL(string path);
void AssetTreeR(string path);
void MenuFile();

TmingEngine::Project::~Project()
{
}



void TmingEngine::Project::Begin()
{

}



void TmingEngine::Project::Update()
{
	ImGui::SetNextWindowSize(ImVec2(400, 560), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Project", &p_open))
	{
		ImGui::End();
		return;
	}

	//ImGui::BeginChild("left pane", ImVec2(200, 0), true);
	ImGui::Columns(2, "Assets", true);
	if (ImGui::TreeNode("Assets"))
	{
	
		auto current = FileSystem::getPath("");
		AssetTree(current);
		//AssetTreeL(current);
		//ImGui::NextColumn;

		//if (!rightContent.empty())
		//{
		//	AssetTreeR(rightContent);
		//}
		//
		//ImGui::NextColumn;
		ImGui::TreePop();
	}
	ImGui::Columns(1);
	//ImGui::EndChild();
	ImGui::SameLine();
	ImGui::End();

}

struct PathObjInfo
{
	string name;
	bool isFolder;
};

vector<PathObjInfo> getPathFileOrFolderinfo(string path)
{
	vector<PathObjInfo> restInfo;
#ifdef __APPLE__
	struct dirent* dirp;
	DIR* dir = opendir(path.c_str());
	while ((dirp = readdir(dir)) != nullptr)
	{
		PathObjInfo info;
		if (dirp->d_type == DT_REG)
		{
			info.name = dirp->d_name;
			info.isFolder = false;
			restInfo.push_back(info);
		}
		else if (dirp->d_type == DT_DIR)
		{
			string temp = string(dirp->d_name);
			if (temp == "." || temp == "..")
			{

			}
			else
			{
				info.name = dirp->d_name;
				info.isFolder = true;
				restInfo.push_back(info);
			}
		}
	}
#else // APPLE

	HANDLE hFind;
	WIN32_FIND_DATA findData;
	LARGE_INTEGER size;
	char dirNew[100];

	// 向目录加通配符，用于搜索第一个文件 
	strcpy(dirNew, path.c_str());
	strcat(dirNew, "\\*.*");

	hFind = FindFirstFile(dirNew, &findData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		cout << "Failed to find first file!\n";
		return restInfo;
	}
	do
	{
		// 忽略"."和".."两个结果 
		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
			continue;

		PathObjInfo info;
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)    // 是否是目录 
		{
			info.name = findData.cFileName;
			info.isFolder = true;
			restInfo.push_back(info);

			cout << findData.cFileName << "\t<dir>\n";
		}
		else
		{
			info.name = findData.cFileName;
			info.isFolder = false;
			restInfo.push_back(info);

			size.LowPart = findData.nFileSizeLow;
			size.HighPart = findData.nFileSizeHigh;

			cout << findData.cFileName << "\t" << size.QuadPart << " bytes\n";
		}
	} while (FindNextFile(hFind, &findData));
	cout << "Done!\n";


#endif

	return restInfo;
}



map<string, vector<PathObjInfo>> pathCache;

void AssetTree(string path)
{
	auto iter = pathCache.find(path);
	if (iter != pathCache.end())
	{
		//        cout<<"cache path find"<<endl;
		auto infs = pathCache[path];
		vector<PathObjInfo>::iterator iter;
		for (iter = infs.begin(); iter != infs.end(); iter++)
		{
			auto t = *iter;
			if (t.isFolder)
			{
				if (t.name == ".." || t.name == ".")
				{

				}
				else
				{
					string s = string(path) + "/" + t.name;
					if (ImGui::TreeNode(t.name.c_str()))
					{
						//ImGui::Text("%s", t.name.c_str());
						AssetTree(s);
						ImGui::TreePop();
					}
				}
			}
			else
			{
				ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
				node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
				int tempIndex = 9, node_clicked;
				ImGui::TreeNodeEx((void*)(intptr_t)tempIndex, node_flags, t.name.c_str());
				
				int ClickMouse = ImGui::IsItemClicked();			
				if (ClickMouse)
				{
					string fpath = path + "/" + t.name;				
					Debug::Log(string("Select: ")+ path + "/" + t.name+"\n");

					if ((t.name.find(".glsl")!= string::npos)
						|| (t.name.find(".hlsl") != string::npos)
						|| (t.name.find(".fs") != string::npos)
						|| (t.name.find(".vs") != string::npos)
						)
					{
						auto screen = Global<Context>().GetSubsystem<ScreenSystem>();
						auto codeEditor = screen->GetSubWidget<CodeEditor>();
						auto txt = Global<Context>().GetSubsystem<FileSystem>()->GetFileContent(fpath);

						codeEditor->fileToEdit = fpath;
						ImGui::SetClipboardText(txt.c_str());
						codeEditor->editor.SetText("");
						codeEditor->editor.Paste();
						ImGui::SetClipboardText("");
						codeEditor->Show();
					}
					else if ((t.name.find(".png") != string::npos)
						|| (t.name.find(".jpg") != string::npos)
						|| (t.name.find(".PNG") != string::npos)
						|| (t.name.find(".JPG") != string::npos)
						|| (t.name.find(".tga") != string::npos)
						|| (t.name.find(".TGA") != string::npos)
						)
					{
						auto screen = Global<Context>().GetSubsystem<ScreenSystem>();
						auto previewer = screen->GetSubWidget<Preview>();
						previewer->PreviewTexture(fpath);
						previewer->Show();

					}



						

				}

				if (ImGui::IsItemClicked(1))
				{
					ImGui::OpenPopup("my_file_popup");
				}

				if (ImGui::BeginPopup("my_file_popup"))
				{
					MenuFile();
					ImGui::EndPopup();
				}

			}
		}
	}
	else
	{
		//        cout<<"cache path can't find "<< path <<endl;
		auto res = getPathFileOrFolderinfo(path);
		pathCache.insert(pair<string, vector<PathObjInfo>>(path, res));
	}
}

void MenuFile()
{
	ImGui::MenuItem("(dummy menu)", NULL, false, false);
	if (ImGui::MenuItem("New")) {}
	if (ImGui::MenuItem("Open", "Ctrl+O")) {}
	if (ImGui::BeginMenu("Open Recent"))
	{
		ImGui::MenuItem("fish_hat.c");
		ImGui::MenuItem("fish_hat.inl");
		ImGui::MenuItem("fish_hat.h");
		if (ImGui::BeginMenu("More.."))
		{
			ImGui::MenuItem("Hello");
			ImGui::MenuItem("Sailor");
			if (ImGui::BeginMenu("Recurse.."))
			{
				MenuFile();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem("Save", "Ctrl+S")) {}
	if (ImGui::MenuItem("Save As..")) {}
	ImGui::Separator();
	if (ImGui::BeginMenu("Options"))
	{
		static bool enabled = true;
		ImGui::MenuItem("Enabled", "", &enabled);
		ImGui::BeginChild("child", ImVec2(0, 60), true);
		for (int i = 0; i < 10; i++)
			ImGui::Text("Scrolling Text %d", i);
		ImGui::EndChild();
		static float f = 0.5f;
		static int n = 0;
		static bool b = true;
		ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
		ImGui::InputFloat("Input", &f, 0.1f);
		ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
		ImGui::Checkbox("Check", &b);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Colors"))
	{
		float sz = ImGui::GetTextLineHeight();
		for (int i = 0; i < ImGuiCol_COUNT; i++)
		{
			const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
			ImVec2 p = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
			ImGui::Dummy(ImVec2(sz, sz));
			ImGui::SameLine();
			ImGui::MenuItem(name);
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Disabled", false)) // Disabled
	{
		IM_ASSERT(0);
	}
	if (ImGui::MenuItem("Checked", NULL, true)) {}
	if (ImGui::MenuItem("Quit", "Alt+F4")) {}
}

void AssetTreeL(string path)
{
	string rightContent = "";
	auto iter = pathCache.find(path);
	if (iter != pathCache.end())
	{
		//        cout<<"cache path find"<<endl;
		auto infs = pathCache[path];
		vector<PathObjInfo>::iterator iter;
		for (iter = infs.begin(); iter != infs.end(); iter++)
		{
			auto t = *iter;
			if (t.isFolder)
			{
				if (t.name == ".." || t.name == ".")
				{

				}
				else
				{
					string current = string(path) + "/" + t.name;
					if (ImGui::TreeNodeEx(t.name.c_str()))
					{
						//ImGui::Text("%s", t.name.c_str());
						//AssetTree(s);
						AssetTreeL(current);
						
						ImGui::TreePop();
					}
					if (ImGui::IsItemClicked())
					{
						//AssetTreeR(current);
						rightContent = current;
						std::cout<<" ------------- rightContent: "<< rightContent <<std::endl;
					}
				}
			}
			else
			{
				//ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
				//node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
				//int tempIndex = 9, node_clicked;
				//ImGui::TreeNodeEx((void*)(intptr_t)tempIndex, node_flags, t.name.c_str());
				//if (ImGui::IsItemClicked())
				//{
				//	string fpath = path + "/" + t.name;
				//	cout << "选中文件: " << path << "/" + t.name << endl;
				//	//               fileToEdit = fpath;
				//	//               string contentText = GetFileContent(fileToEdit);
				//	//               //ImGui::SetClipboardText(contentText.c_str());
				//	//               editor.SetText("");
				//	//               //editor.Paste();
				//	//               //ImGui::SetClipboardText("");
				//				   //editor.SetText(contentText);
				//}

				//ImGui::NextColumn();
				//ImGui::Text(t.name.c_str());
				//ImGui::NextColumn();
			}
			//AssetTreeR(rightContent);
		}
	}
	else
	{
		//        cout<<"cache path can't find "<< path <<endl;
		auto res = getPathFileOrFolderinfo(path);
		pathCache.insert(pair<string, vector<PathObjInfo>>(path, res));
	}
}

void AssetTreeR(string path)
{
	auto iter = pathCache.find(path);
	if (iter != pathCache.end())
	{
		//        cout<<"cache path find"<<endl;
		auto infs = pathCache[path];
		vector<PathObjInfo>::iterator iter;
		for (iter = infs.begin(); iter != infs.end(); iter++)
		{
			auto t = *iter;
			if (t.isFolder)
			{
				//if (t.name == ".." || t.name == ".")
				//{

				//}
				//else
				//{
				//	string s = string(path) + "/" + t.name;
				//	if (ImGui::TreeNode(t.name.c_str()))
				//	{
				//		//ImGui::Text("%s", t.name.c_str());
				//		AssetTree(s);
				//		ImGui::TreePop();
				//	}
				//}
				ImGui::Text(t.name.c_str());
			}
			else
			{
				//ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
				//node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
				//int tempIndex = 9, node_clicked;
				//ImGui::TreeNodeEx((void*)(intptr_t)tempIndex, node_flags, t.name.c_str());
				//if (ImGui::IsItemClicked())
				//{
				//	string fpath = path + "/" + t.name;
				//	cout << "选中文件: " << path << "/" + t.name << endl;
				//	//               fileToEdit = fpath;
				//	//               string contentText = GetFileContent(fileToEdit);
				//	//               //ImGui::SetClipboardText(contentText.c_str());
				//	//               editor.SetText("");
				//	//               //editor.Paste();
				//	//               //ImGui::SetClipboardText("");
				//				   //editor.SetText(contentText);
				//}

				
				ImGui::Text(t.name.c_str());
			
			}
		}
	}
	else
	{
		//        cout<<"cache path can't find "<< path <<endl;
		auto res = getPathFileOrFolderinfo(path);
		pathCache.insert(pair<string, vector<PathObjInfo>>(path, res));
	}
}

void TmingEngine::Project::End()
{

}


std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}


#ifdef __APPLE__
void listFiles(const char* path, std::vector<std::string>& files, std::vector<string> filters)
{
	struct dirent* dirp;
	DIR* dir = opendir(path);
	while ((dirp = readdir(dir)) != nullptr) {
		if (dirp->d_type == DT_REG)
		{
			// cout<< "File: "<<dirp->d_name<<endl;

			string s = string(path) + "/" + string(dirp->d_name);
			auto ext = split(dirp->d_name, '.');
			//cout <<"."<< *(ext.end()-1) << endl;
			vector<string>::iterator it, all;
			string value = "." + *(ext.end() - 1);
			string alv = ".*";
			all = find(filters.begin(), filters.end(), alv);
			it = find(filters.begin(), filters.end(), value);
			if (it != filters.end() || all != filters.end())
			{
				files.push_back(s);
			}
		}
		else if (dirp->d_type == DT_DIR)
		{
			auto s = dirp->d_name;
			if (string(s) != "." && string(s) != "..")
			{
				// cout<< "Fold: "<<dirp->d_name<<endl;
				string s = string(path) + "/" + dirp->d_name;
				listFiles(s.c_str(), files, filters);
			}
		}
	}
}

#else

void listFiles(const char* dir, std::vector<std::string>& files, std::vector<string> filters)
{

	char dirNew[200];
	strcpy(dirNew, dir);
	strcat(dirNew, "\\*.*");

	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dirNew, &findData);
	if (handle == -1)
		return;

	do
	{
		if (findData.attrib & _A_SUBDIR)
		{
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;

			strcpy(dirNew, dir);
			strcat(dirNew, "\\");
			strcat(dirNew, findData.name);

			listFiles(dirNew, files, filters);
		}
		else
		{
			string s = string(dir) + "\\" + string(findData.name);
			auto ext = split(findData.name, '.');


			vector<string>::iterator it, all;
			string value = "." + *(ext.end() - 1);
			string alv = ".*";

			all = find(filters.begin(), filters.end(), alv);
			it = find(filters.begin(), filters.end(), value);
			if (it != filters.end() || all != filters.end())
			{
				files.push_back(s);
			}
		}
	} while (_findnext(handle, &findData) == 0);

	_findclose(handle);
}

#endif

std::vector<std::string> TmingEngine::Project::FileFilter(const char* dir, std::vector<std::string> filefilters)
{
	std::vector<string> res;
	listFiles(dir, res, filefilters);
	return res;
}


