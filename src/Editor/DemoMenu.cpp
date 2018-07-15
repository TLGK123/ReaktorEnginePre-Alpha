#include "DemoMenu.h"

static bool sTestEntriesGetName(void*, int idx, const char** out_name)
{
	//*out_name = g_testEntries[idx].name;
	return true;
}

void TmingEngine::DemoMenu::Begin()
{
	bool p_open = true;
	//ImGui::SetNextWindowPos(ImVec2(200, 10));
	ImGui::SetNextWindowSize(ImVec2(200, 560), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("DemoMenu1", &p_open))
	{
		ImGui::End();
		return;
	}

	ImGui::PushAllowKeyboardFocus(false); // Disable TAB

	ImGui::PushItemWidth(-1.0f);

	ImGui::Text("Test");
	//if (ImGui::Combo("##Test", &testIndex, sTestEntriesGetName, NULL, testCount, testCount))
	//{
	//	delete test;
	//	entry = g_testEntries + testIndex;
	//	test = entry->createFcn();
	//	testSelection = testIndex;
	//}
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