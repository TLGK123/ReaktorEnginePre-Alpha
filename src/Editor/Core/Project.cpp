#include "Project.h"

std::vector<string> filters;
std::vector<std::string> files;

TmingEngine::Project::~Project()
{
}


void TmingEngine::Project::Begin()
{
    string s = "";
    string str[] ={".*"};
    std::vector<string> fi(str,str+1);
    //string currentPath =FileSystem::getPath(s);
    string currentPath = "/Users/blue/Desktop/GitHub/LISP";
    FileFilter(currentPath.c_str(),fi);
    vector<string>::iterator iter;
    cout <<endl;
    for (iter = files.begin(); iter != files.end(); iter++)
    {
        //cout << *iter << endl;
        string s = *iter;
        cout  <<"––––––"<< *iter <<endl;
        ;
    }
}

void TmingEngine::Project::Update()
{
	bool p_open = true;
	ImGui::SetNextWindowSize(ImVec2(350, 560), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Project", &p_open))
	{
		ImGui::End();
		return;
	}


	if (ImGui::TreeNode("Basic trees"))
	{
		for (int i = 0; i < 5; i++)
			if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", i))
			{
				ImGui::Text("blah blah");
				ImGui::SameLine();
				if (ImGui::SmallButton("button")) {};
				ImGui::TreePop();
			}
		ImGui::TreePop();
	}

	ImGui::Text("this is project view");

	ImGui::End();
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
void listFiles(const char * path)
{
    struct dirent * dirp;
    DIR * dir = opendir(path);
    while ((dirp = readdir(dir)) != nullptr) {
        if (dirp->d_type == DT_REG)
        {
            // cout<< "File: "<<dirp->d_name<<endl;
            
            string s = string(path) + "/" + string(dirp->d_name);
            auto ext = split(dirp->d_name, '.');
            //cout <<"."<< *(ext.end()-1) << endl;
            vector<string>::iterator it ,all;
            string value = "." + *(ext.end() - 1);
            string alv = ".*";
            all = find(filters.begin(), filters.end(), alv);
            it = find(filters.begin(), filters.end(), value);
            if (it != filters.end()|| all !=filters.end())
            {
                files.push_back(s);
            }
        }
        else if (dirp->d_type == DT_DIR)
        {
            auto s = dirp->d_name;
            if (string(s) != "."&&string(s) != "..")
            {
                // cout<< "Fold: "<<dirp->d_name<<endl;
                string s = string(path) + "/" + dirp->d_name;
                listFiles(s.c_str());
            }
        }
    }
}
#else

void listFiles(const char * dir)
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
            
            listFiles(dirNew);
        }
        else
        {
            string s = string(dir) + "\\" + string(findData.name);
            auto ext = split(findData.name, '.');
            
            
            vector<string>::iterator it;
            string value = "." + *(ext.end() - 1);
            it = find(filters.begin(), filters.end(), value);
            if (it != filters.end())
            {
                files.push_back(s);
            }
        }
    } while (_findnext(handle, &findData) == 0);
    
    _findclose(handle);
}


#endif

std::vector<std::string> TmingEngine::Project:: FileFilter(const char * dir , std::vector<std::string> filefilters)
{
    filters = filefilters;
    files.clear();
    listFiles(dir);
    return files;
}


