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


#include "Console.h"

namespace TmingEngine
{
	Console::~Console() {}

	void Console::Clear() { Buf.clear(); LineOffsets.clear(); }

    
    void Console::Begin()
    {
        
    }
    
    void Console::Update()
    {
        bool p_open =true;
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
        if (!ImGui::Begin("Console", &p_open))
        {
            ImGui::End();
            return;
        }
        if (ImGui::Button("Clear")) Clear();
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        Filter.Draw("Filter", -100.0f);
        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (copy) ImGui::LogToClipboard();
        

        
        if (ScrollToBottom)
            ImGui::SetScrollHereY(1.0f);
        ScrollToBottom = false;
        
        
        ImGui::Separator();
        // Command-line
        static char InputBuf[256] = "";
        static char ResualtBuf[256] = "";
        ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf));
        
        if (ImGui::Button("Command"))
        {
            //1.����Lua״̬  
            lua_State* L = luaL_newstate();
            if (L == NULL)
            {
                return;
            }

            //2.����Lua�ļ�  
            int bRet = luaL_loadfile(L,FileSystem::getPath("Data/EngineScript/hello.lua").c_str());
            if (bRet)
            {
                cout << "load file error" << endl;
                return;
            }

            //3.����Lua�ļ�  
            bRet = lua_pcall(L, 0, 0, 0);
            if (bRet)
            {
                cout << "pcall error" << endl;
                return;
            }

            //4.��ȡ����  
            lua_getglobal(L, "str");
            string str = lua_tostring(L, -1);
            cout << "str = " << str.c_str() << endl;        //str = I am so cool~  

            //5.��ȡtable  
            lua_getglobal(L, "tbl");
            lua_getfield(L, -1, "name");
            str = lua_tostring(L, -1);
            cout << "tbl:name = " << str.c_str() << endl; //tbl:name = shun  

            //6.��ȡ����  
            lua_getglobal(L, "add");        // ��ȡ������ѹ��ջ��  
            lua_pushnumber(L, 10);          // ѹ���һ������  
            lua_pushnumber(L, 20);          // ѹ��ڶ�������  
            int iRet = lua_pcall(L, 2, 1, 0);// ���ú�������������Ժ󣬻Ὣ����ֵѹ��ջ�У�2��ʾ����������1��ʾ���ؽ��������  
            if (iRet)                       // ���ó���  
            {
                const char* pErrorMsg = lua_tostring(L, -1);
                cout << pErrorMsg << endl;
                lua_close(L);
                return;
            }
            if (lua_isnumber(L, -1))        //ȡֵ���  
            {
                double fValue = lua_tonumber(L, -1);
                cout << "Result is " << fValue << endl;
            }

        }
        

        if (Filter.IsActive())
        {
            const char* buf_begin = Buf.begin();
            const char* line = buf_begin;
            for (int line_no = 0; line != NULL; line_no++)
            {
                const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
                if (Filter.PassFilter(line, line_end))
                    ImGui::TextUnformatted(line, line_end);
                line = line_end && line_end[1] ? line_end + 1 : NULL;
            }
        }
        else
        {
            ImGui::TextUnformatted(Buf.begin());
        }


        ImGui::EndChild();
        ImGui::End();
        
    }
    
 
    
    void Console::End()
    {
        
        
    }
    
	void Console::AddLog(const char* fmt, ...)
	{
		int old_size = Buf.size();
		va_list args;
		va_start(args, fmt);
		Buf.appendfv(fmt, args);
		va_end(args);
		for (int new_size = Buf.size(); old_size < new_size; old_size++)
			if (Buf[old_size] == '\n')
				LineOffsets.push_back(old_size);
		ScrollToBottom = true;
	}

	void Console::Draw(const char* title, bool* p_open = NULL)
	{

	}

}
