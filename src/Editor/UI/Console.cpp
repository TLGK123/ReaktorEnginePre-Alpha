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
            Debug::Log(InputBuf);
			printf("\n");
            string s = string(InputBuf);
            //Scheme_init();
            //FILE *  file_demo;
            //file_demo = fopen("demo.txt", "w+");
            //fputs(s.c_str(), file_demo);
            //fclose(file_demo);
            //file_demo = fopen("demo.txt", "r");
            //FILE *  evalOut =fopen("evalOut.txt", "w+");
            //file_demo = fopen("stdlib.scm", "r");
            //fgets(InputBuf, 255, (FILE*)file_demo);
            //Schem_eval_out(stdin,stdout);
            //fclose(evalOut);
            //evalOut =fopen("evalOut.txt", "r");
            //fgets(ResualtBuf, 255, (FILE*)evalOut);
            //Buf.append("\n");
            //Buf.append(ResualtBuf);
            //fclose(file_demo);
            //fclose(evalOut);
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
