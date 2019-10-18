//= INCLUDES ==================
#include "RHI_Device.h"
#include "../Core/Context.h"
#include "../Core/Settings.h"
#include "../Math/MathHelper.h"
#include <algorithm>
//=============================

//= NAMESPACES ================
using namespace std;
using namespace TmingEngine::Math;

//=============================

namespace TmingEngine
{
	void RHI_Device::AddDisplayMode(unsigned int width, unsigned int height, unsigned int refresh_rate_numerator, unsigned int refresh_rate_denominator)
	{
		auto& mode = m_displayModes.emplace_back(width, height, refresh_rate_numerator, refresh_rate_denominator);

		// Try to deduce the maximum frame rate based on how fast the monitor is
//        if (Settings::Get().GetFpsPolicy() == FPS_MonitorMatch)
//        {
//            Settings::Get().SetFpsLimit(Helper::Max(Settings::Get().GetFpsLimit(), mode.refreshRate));
//        }
	}

	bool RHI_Device::GetDidsplayModeFastest(DisplayMode* display_mode)
	{
		if (m_displayModes.empty())
			return false;

		display_mode = &m_displayModes[0];
		for (auto& mode : m_displayModes)
		{
			if (display_mode->refreshRate < mode.refreshRate)
			{
				display_mode = &mode;
			}
		}

		return true;
	}

	void RHI_Device::AddAdapter(const string& name, unsigned int memory, unsigned int vendor_id, void* adapter)
	{
		m_displayAdapters.emplace_back(name, memory, vendor_id, adapter);
		sort(m_displayAdapters.begin(), m_displayAdapters.end(), [](const DisplayAdapter& adapter1, const DisplayAdapter& adapter2)
		{
			return adapter1.memory > adapter2.memory;
		});

//	LOGF_INFO("%s (%d MB)", name.c_str(), memory);
	}

	void RHI_Device::SetPrimaryAdapter(const DisplayAdapter* primary_adapter)
	{
		if (!primary_adapter)
		{
 //           LOG_ERROR_INVALID_PARAMETER();
			return;
		}

		m_primaryAdapter = primary_adapter;
//		LOGF_INFO("%s (%d MB)", primary_adapter->name.c_str(), primary_adapter->memory);
	}
}
