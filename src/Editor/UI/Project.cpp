#include "Project.h"

void AssetTree(string path);

TmingEngine::Project::~Project()
{
}

TextEditor editor;
string fileToEdit = "ImGuiColorTextEdit/TextEditor.cpp";

void TmingEngine::Project::Begin()
{
//    string s = "";
//    string str[] ={".*"};
//    std::vector<string> fi(str,str+1);
//    string currentPath =FileSystem::getPath(s);
//    auto files = FileFilter(currentPath.c_str(),fi);
//    vector<string>::iterator iter;
//    cout <<endl;
//    for (iter = files.begin(); iter != files.end(); iter++)
//    {
//        string s = *iter;
//        cout  <<*iter <<endl;
//        ;
//    }
    
    
    auto lang = TextEditor::LanguageDefinition::CPlusPlus();
    static const char* ppnames[] = { "NULL", "PM_REMOVE",
        "ZeroMemory", "DXGI_SWAP_EFFECT_DISCARD", "D3D_FEATURE_LEVEL", "D3D_DRIVER_TYPE_HARDWARE", "WINAPI","D3D11_SDK_VERSION", "assert" };
    
    static const char* ppvalues[] = {
        "#define NULL ((void*)0)",
        "#define PM_REMOVE (0x0001)",
        "Microsoft's own memory zapper function\n(which is a macro actually)\nvoid ZeroMemory(\n\t[in] PVOID  Destination,\n\t[in] SIZE_T Length\n); ",
        "enum DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD = 0",
        "enum D3D_FEATURE_LEVEL",
        "enum D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE  = ( D3D_DRIVER_TYPE_UNKNOWN + 1 )",
        "#define WINAPI __stdcall",
        "#define D3D11_SDK_VERSION (7)",
        " #define assert(expression) (void)(                                                  \n"
        "    (!!(expression)) ||                                                              \n"
        "    (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) \n"
        " )"
    };
    
    for (int i = 0; i < sizeof(ppnames) / sizeof(ppnames[0]); ++i)
    {
        TextEditor::Identifier id;
        id.mDeclaration = ppvalues[i];
        lang.mPreprocIdentifiers.insert(std::make_pair(std::string(ppnames[i]), id));
    }
    
    static const char* identifiers[] = {
        "HWND", "HRESULT", "LPRESULT","D3D11_RENDER_TARGET_VIEW_DESC", "DXGI_SWAP_CHAIN_DESC","MSG","LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
        "ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
        "ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
        "IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "TextEditor" };

    static const char* idecls[] =
    {
        "typedef HWND_* HWND", "typedef long HRESULT", "typedef long* LPRESULT", "struct D3D11_RENDER_TARGET_VIEW_DESC", "struct DXGI_SWAP_CHAIN_DESC",
        "typedef tagMSG MSG\n * Message structure","typedef LONG_PTR LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
        "ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
        "ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
        "IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "class TextEditor" };
    
    for (int i = 0; i < sizeof(identifiers) / sizeof(identifiers[0]); ++i)
    {
        TextEditor::Identifier id;
        id.mDeclaration = std::string(idecls[i]);
        lang.mIdentifiers.insert(std::make_pair(std::string(identifiers[i]), id));
    }
    editor.SetLanguageDefinition(lang);

    TextEditor::ErrorMarkers markers;
    markers.insert(std::make_pair<int, std::string>(6, "Example error here:\nInclude file not found: \"TextEditor.h\""));
    markers.insert(std::make_pair<int, std::string>(41, "Another example error"));
    editor.SetErrorMarkers(markers);
    
    
    //    static const char* fileToEdit = "test.cpp";
    
    {
        std::ifstream t(fileToEdit);
        if (t.good())
        {
            std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
            editor.SetText(str);
        }
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
    
    ImGui::BeginChild("left pane", ImVec2(200, 0), true);
	if (ImGui::TreeNode("Assets"))
	{
        auto current = FileSystem::getPath("");
        AssetTree(current);
		ImGui::TreePop();
	}
    
    ImGui::EndChild();
  //  ImGui::End();
    ImGui::SameLine();
    ImGui::SameLine();
    
    ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
    
    auto cpos = editor.GetCursorPosition();
  //  ImGui::Begin("Text Editor Demo", nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
   // ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save"))
            {
                auto textToSave = editor.GetText();
                /// save text....
            }
            if (ImGui::MenuItem("Quit", "Alt-F4"))
            {
                return;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            bool ro = editor.IsReadOnly();
            if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
                editor.SetReadOnly(ro);
            ImGui::Separator();
            
            if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo()))
                editor.Undo();
            if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
                editor.Redo();
            
            ImGui::Separator();
            
            if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
                editor.Copy();
            if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection()))
                editor.Cut();
            if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection()))
                editor.Delete();
            if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
                editor.Paste();
            
            ImGui::Separator();
            
            if (ImGui::MenuItem("Select all", nullptr, nullptr))
                editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));
            
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Dark palette"))
                editor.SetPalette(TextEditor::GetDarkPalette());
            if (ImGui::MenuItem("Light palette"))
                editor.SetPalette(TextEditor::GetLightPalette());
            if (ImGui::MenuItem("Retro blue palette"))
                editor.SetPalette(TextEditor::GetRetroBluePalette());
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    
    ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
                editor.IsOverwrite() ? "Ovr" : "Ins",
                editor.CanUndo() ? "*" : " ",
                editor.GetLanguageDefinition().mName.c_str(), fileToEdit.c_str());
    
    editor.Render("TextEditor");
    ImGui::EndChild();
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
    struct dirent * dirp;
    DIR * dir = opendir(path.c_str());
    while ((dirp = readdir(dir)) != nullptr)
    {
        PathObjInfo info;
        if (dirp->d_type == DT_REG)
        {
            info.name = dirp->d_name;
            info.isFolder =false;
            restInfo.push_back(info);
        }
        else if (dirp->d_type == DT_DIR)
        {
            string temp = string(dirp->d_name);
            if (temp == "."|| temp =="..")
            {
                
            }
            else
            {
                info.name = dirp->d_name;
                info.isFolder =true;
                restInfo.push_back(info);
            }
        }
    }
    
    return restInfo;
}



string GetFileContent(string f)
{
    string content;
    ifstream fin(f);
    string  s;
    while (getline(fin, s))
    {
        content += s+"\n";
    }
    fin.close();
    return content;
}
//vector<string> GetFileContent(string f)
//{
//    vector<string> content;
//    ifstream fin(f);
//    string  s;
//    while (getline(fin, s))
//    {
//        content.push_back(s);
//    }
//    fin.close();
//    return content;
//}




map<string, vector<PathObjInfo>> pathCache;

void AssetTree(string path)
{
    auto iter = pathCache.find(path);
    if(iter != pathCache.end())
    {
//        cout<<"cache path find"<<endl;
        auto infs =pathCache[path];
        vector<PathObjInfo>::iterator iter;
        for (iter =infs.begin(); iter!=infs.end(); iter++)
        {
            auto t = *iter;
            if( t.isFolder )
            {
                if(t.name==".."||t.name==".")
                {
                    
                }else
                {
                    string s = string(path) + "/" + t.name;
                    if (ImGui::TreeNode(t.name.c_str()))
                    {
                     ImGui::Text("%s", t.name.c_str());
                     AssetTree(s);
                     ImGui::TreePop();
                    }
                }
            }
            else
            {
                ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
                int tempIndex = 9 ,node_clicked;
                ImGui::TreeNodeEx((void*)(intptr_t)tempIndex, node_flags,t.name.c_str());
                if (ImGui::IsItemClicked())
                {
                    string fpath = path+"/"+t.name;
                    cout<<"选中文件: "<<path<<"/"+t.name<<endl;
                    fileToEdit = fpath;
                    string contentText = GetFileContent(fileToEdit);
                    ImGui::SetClipboardText(contentText.c_str());
                    editor.SetText("");
                    editor.Paste();
                    ImGui::SetClipboardText("");

                }
            }
        }
    }
    else
    {
//        cout<<"cache path can't find "<< path <<endl;
        auto res = getPathFileOrFolderinfo(path);
        pathCache.insert(pair<string, vector<PathObjInfo>>(path,res));
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
void listFiles(const char * path , std::vector<std::string>&files, std::vector<string> filters)
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
                listFiles(s.c_str(),files,filters);
            }
        }
    }
}

#else

void listFiles(const char * dir, std::vector<std::string> & files,std::vector<string> filters)
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
            
            listFiles(dirNew,files,filters);
        }
        else
        {
            string s = string(dir) + "\\" + string(findData.name);
            auto ext = split(findData.name, '.');
            
            
            vector<string>::iterator it , all;
            string value = "." + *(ext.end() - 1);
			string alv = ".*";

			all = find(filters.begin(), filters.end(), alv);
            it = find(filters.begin(), filters.end(), value);
            if (it != filters.end()|| all != filters.end())
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
	std::vector<string> res;
    listFiles(dir, res, filefilters);
    return res;
}


