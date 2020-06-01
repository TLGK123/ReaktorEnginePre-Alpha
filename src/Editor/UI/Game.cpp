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

#include "Game.hpp"
TmingEngine::Game::~Game()
{
}

void TmingEngine::Game::Begin()
{
	gameWidth = 500;
	gameHeight = 500;
	SoftRender();
}

void TmingEngine::Game::Update()
{
    bool p_open = true;
    ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Game", &p_open))
    {
        ImGui::End();
        return;
    }
    ImTextureID my_tex_id = (void *)imageId;
    float my_tex_w = gameWidth;
    float my_tex_h = gameHeight;
    
    ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);

    //----------------------------------------------------------------- -1 -1  Image reversal
    ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
    ImGui::End();
}


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = std::abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {
		if (steep) {
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color);
		}
		error2 += derror2;
		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}
void line(ImVec2 x, ImVec2 y , TGAImage& image, TGAColor color)
{
	line(x.x,x.y,y.x,y.y,image,color);
}

void triangle(ImVec2 t0, ImVec2 t1, ImVec2 t2, TGAImage& image, TGAColor color) {
	line(t0, t1, image, color);
	line(t1, t2, image, color);
	line(t2, t0, image, color);
}

void TmingEngine::Game::End()
{

}


void TmingEngine::Game::SoftRender()
{

	glGenTextures(1, &imageId);

	glBindTexture(GL_TEXTURE_2D, imageId);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	TGAImage image(gameWidth, gameHeight, TGAImage::RGB);
	

	ImVec2 t0[3] = { ImVec2(10, 70),   ImVec2(50, 160),  ImVec2(70, 80) };
	ImVec2 t1[3] = { ImVec2(180, 50),  ImVec2(150, 1),   ImVec2(70, 180) };
	ImVec2 t2[3] = { ImVec2(180, 150), ImVec2(120, 160), ImVec2(130, 180) };
	triangle(t0[0], t0[1], t0[2], image, red);
	triangle(t1[0], t1[1], t1[2], image, white);
	triangle(t2[0], t2[1], t2[2], image, green);


	image.flip_horizontally();

	unsigned char* data = image.buffer();
	width = image.get_width();
	height = image.get_height();
	nrChannels = image.get_bytespp();

	if (data)
	{
		try
		{
			if (nrChannels == 4)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
			else if (nrChannels == 3)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else if (nrChannels == 1)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				int c = nrChannels;
			}

			glGenerateMipmap(GL_TEXTURE_2D);
		}
		catch (const std::exception&)
		{

		}

	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	
	image.clear();
}

void MessageCallback(const asSMessageInfo* msg, void* param)
{
    const char* type = "ERR ";
    if (msg->type == asMSGTYPE_WARNING)
        type = "WARN";
    else if (msg->type == asMSGTYPE_INFORMATION)
        type = "INFO";

    printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

int CompileScript(asIScriptEngine* engine)
{
    int r;

    // We will load the script from a file on the disk.
    FILE* f = fopen(TmingEngine::FileSystem::getPath("Data/EngineScript/script.as").c_str(), "rb");
    if (f == 0)
    {
        cout << "Failed to open the script file 'script.as'." << endl;
        return -1;
    }

    // Determine the size of the file	
    fseek(f, 0, SEEK_END);
    int len = ftell(f);
    fseek(f, 0, SEEK_SET);

    // On Win32 it is possible to do the following instead
    // int len = _filelength(_fileno(f));

    // Read the entire file
    string script;
    script.resize(len);
    size_t c = fread(&script[0], len, 1, f);
    fclose(f);

    if (c == 0)
    {
        cout << "Failed to load script file." << endl;
        return -1;
    }

    // Add the script sections that will be compiled into executable code.
    // If we want to combine more than one file into the same script, then 
    // we can call AddScriptSection() several times for the same module and
    // the script engine will treat them all as if they were one. The script
    // section name, will allow us to localize any errors in the script code.
    asIScriptModule* mod = engine->GetModule(0, asGM_ALWAYS_CREATE);
    r = mod->AddScriptSection("script", &script[0], len);
    if (r < 0)
    {
        cout << "AddScriptSection() failed" << endl;
        return -1;
    }

    // Compile the script. If there are any compiler messages they will
    // be written to the message stream that we set right after creating the 
    // script engine. If there are no errors, and no warnings, nothing will
    // be written to the stream.
    r = mod->Build();
    if (r < 0)
    {
        cout << "Build() failed" << endl;
        return -1;
    }

    // The engine doesn't keep a copy of the script sections after Build() has
    // returned. So if the script needs to be recompiled, then all the script
    // sections must be added again.

    // If we want to have several scripts executing at different times but 
    // that have no direct relation with each other, then we can compile them
    // into separate script modules. Each module use their own namespace and 
    // scope, so function names, and global variables will not conflict with
    // each other.

    return 0;
}

void LineCallback(asIScriptContext* ctx, DWORD* timeOut)
{
    // If the time out is reached we abort the script


    // It would also be possible to only suspend the script,
    // instead of aborting it. That would allow the application
    // to resume the execution where it left of at a later 
    // time, by simply calling Execute() again.
}

// Function implementation with native calling convention
void PrintString(string& str)
{
    cout << str;
}

// Function implementation with generic script interface
void PrintString_Generic(asIScriptGeneric* gen)
{
    string* str = (string*)gen->GetArgAddress(0);
    cout << *str;
}

// Function wrapper is needed when native calling conventions are not supported
void timeGetTime_Generic(asIScriptGeneric* gen)
{

}

void ConfigureEngine(asIScriptEngine* engine)
{
    int r;

    // Register the script string type
    // Look at the implementation for this function for more information  
    // on how to register a custom string type, and other object types.
    RegisterStdString(engine);

    if (!strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY"))
    {
        // Register the functions that the scripts will be allowed to use.
        // Note how the return code is validated with an assert(). This helps
        // us discover where a problem occurs, and doesn't pollute the code
        // with a lot of if's. If an error occurs in release mode it will
        // be caught when a script is being built, so it is not necessary
        // to do the verification here as well.
        r = engine->RegisterGlobalFunction("void Print(string &in)", asFUNCTION(PrintString), asCALL_CDECL); assert(r >= 0);

    }
    else
    {
        // Notice how the registration is almost identical to the above. 
        r = engine->RegisterGlobalFunction("void Print(string &in)", asFUNCTION(PrintString_Generic), asCALL_GENERIC); assert(r >= 0);

    }


    // It is possible to register the functions, properties, and types in 
    // configuration groups as well. When compiling the scripts it then
    // be defined which configuration groups should be available for that
    // script. If necessary a configuration group can also be removed from
    // the engine, so that the engine configuration could be changed 
    // without having to recompile all the scripts.
}

int TmingEngine::Game::AngleScriptRender()
{
    int r;

    // Create the script engine
    asIScriptEngine* engine = asCreateScriptEngine();
    if (engine == 0)
    {
        cout << "Failed to create script engine." << endl;
        return -1;
    }

    // The script compiler will write any compiler messages to the callback.
    engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

    // Configure the script engine with all the functions, 
    // and variables that the script should be able to use.
    ConfigureEngine(engine);

    // Compile the script code
    r = CompileScript(engine);
    if (r < 0)
    {
        engine->Release();
        return -1;
    }

    // Create a context that will execute the script.
    asIScriptContext* ctx = engine->CreateContext();
    if (ctx == 0)
    {
        cout << "Failed to create the context." << endl;
        engine->Release();
        return -1;
    }

    // We don't want to allow the script to hang the application, e.g. with an
    // infinite loop, so we'll use the line callback function to set a timeout
    // that will abort the script after a certain time. Before executing the 
    // script the timeOut variable will be set to the time when the script must 
    // stop executing. 
    DWORD timeOut;
    r = ctx->SetLineCallback(asFUNCTION(LineCallback), &timeOut, asCALL_CDECL);
    if (r < 0)
    {
        cout << "Failed to set the line callback function." << endl;
        ctx->Release();
        engine->Release();
        return -1;
    }

    // Find the function for the function we want to execute.
    asIScriptFunction* func = engine->GetModule(0)->GetFunctionByDecl("float calc(float, float)");
    if (func == 0)
    {
        cout << "The function 'float calc(float, float)' was not found." << endl;
        ctx->Release();
        engine->Release();
        return -1;
    }

    // Prepare the script context with the function we wish to execute. Prepare()
    // must be called on the context before each new script function that will be
    // executed. Note, that if you intend to execute the same function several 
    // times, it might be a good idea to store the function returned by 
    // GetFunctionByDecl(), so that this relatively slow call can be skipped.
    r = ctx->Prepare(func);
    if (r < 0)
    {
        cout << "Failed to prepare the context." << endl;
        ctx->Release();
        engine->Release();
        return -1;
    }

    // Now we need to pass the parameters to the script function. 
    ctx->SetArgFloat(0, 3.14159265359f);
    ctx->SetArgFloat(1, 2.71828182846f);

    // Set the timeout before executing the function. Give the function 1 sec
    // to return before we'll abort it.


    // Execute the function
    cout << "Executing the script." << endl;
    cout << "---" << endl;
    r = ctx->Execute();
    cout << "---" << endl;
    if (r != asEXECUTION_FINISHED)
    {
        // The execution didn't finish as we had planned. Determine why.
        if (r == asEXECUTION_ABORTED)
            cout << "The script was aborted before it could finish. Probably it timed out." << endl;
        else if (r == asEXECUTION_EXCEPTION)
        {
            cout << "The script ended with an exception." << endl;

            // Write some information about the script exception
            asIScriptFunction* func = ctx->GetExceptionFunction();
            cout << "func: " << func->GetDeclaration() << endl;
            cout << "modl: " << func->GetModuleName() << endl;
            cout << "sect: " << func->GetScriptSectionName() << endl;
            cout << "line: " << ctx->GetExceptionLineNumber() << endl;
            cout << "desc: " << ctx->GetExceptionString() << endl;
        }
        else
            cout << "The script ended for some unforeseen reason (" << r << ")." << endl;
    }
    else
    {
        // Retrieve the return value from the context
        float returnValue = ctx->GetReturnFloat();
        cout << "The script function returned: " << returnValue << endl;
    }

    // We must release the contexts when no longer using them
    ctx->Release();

    // Shut down the engine
    engine->ShutDownAndRelease();

    return 0;
}
