#include "Project.h"

void AssetTree(string path);

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

	ImGui::BeginChild("left pane", ImVec2(200, 0), true);
	if (ImGui::TreeNode("Assets"))
	{
		auto current = FileSystem::getPath("");
		AssetTree(current);
		ImGui::TreePop();
	}

	ImGui::EndChild();
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

void SaveFile(string path, string content)
{
	ofstream fout(path);
	if (!fout)return;
	fout << content << endl;
	fout.close();
}

string GetFileContent(string f)
{
	string content;
	ifstream fin(f);
	string  s;
	while (getline(fin, s))
	{
		content += s + "\n";
	}
	fin.close();
	return content;
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
				if (ImGui::IsItemClicked())
				{
					string fpath = path + "/" + t.name;
					cout << "选中文件: " << path << "/" + t.name << endl;
					//               fileToEdit = fpath;
					//               string contentText = GetFileContent(fileToEdit);
					//               //ImGui::SetClipboardText(contentText.c_str());
					//               editor.SetText("");
					//               //editor.Paste();
					//               //ImGui::SetClipboardText("");
								   //editor.SetText(contentText);

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


