#include "DemoMenu.h"


typedef void (*SimpleFunc)();

struct EntryPoint
{
	const char * name;
	SimpleFunc  fun;

};

EntryPoint * entry;

void pf()
{
	printf("hello 123\n");
	Debug::Log("Open 1 Demo\n");
	
}

void pf2()
{
	printf("hello 456\n");
	Debug::Log("Open 2 Demo\n");
}

EntryPoint g_testEntries[]
{
	{"Hello",pf},
	{"Hello2",pf2}
};

static bool sTestEntriesGetName(void*, int idx, const char** out_name)
{
	*out_name = g_testEntries[idx].name;
	return true;
}

void TmingEngine::DemoMenu::Begin()
{
	bool p_open = true;
	//ImGui::SetNextWindowPos(ImVec2(200, 10));
	ImGui::SetNextWindowSize(ImVec2(200, 560), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("DemoMenu", &p_open))
	{
		ImGui::End();
		return;
	}

	ImGui::PushAllowKeyboardFocus(false); // Disable TAB

	ImGui::PushItemWidth(-1.0f);

	ImGui::Text("Test");
	if (ImGui::Combo("##Test", &testIndex, sTestEntriesGetName, NULL, testCount, testCount))
	{
		
		entry = g_testEntries + testIndex;
		entry->fun();
		testSelection = testIndex;
	}
	ImGui::Separator();

	ImGui::Text("Vel Iters");
	ImGui::PopAllowKeyboardFocus();
	ImGui::End();
}

void TmingEngine::DemoMenu::Update()
{
}

void TmingEngine::DemoMenu::End()
{
}