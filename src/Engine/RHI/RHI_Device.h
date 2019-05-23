#pragma once

//= INCLUDES ==================
#include "RHI_Definition.h"
#include "../Core/EngineDefs.h"
#include <string>
#include <vector>
//=============================

namespace TmingEngine
{
	namespace Math
	{ 
		class Vector4;
		class Rectangle;
	}

	struct DisplayMode
	{
		DisplayMode() = default;
		DisplayMode(const unsigned int width, const unsigned int height, const unsigned int refresh_rate_numerator, const unsigned int refresh_rate_denominator)
		{
			this->width						= width;
			this->height					= height;
			this->refreshRateNumerator		= refresh_rate_numerator;
			this->refreshRateDenominator	= refresh_rate_denominator;
			this->refreshRate				= static_cast<float>(refresh_rate_numerator) / static_cast<float>(refresh_rate_denominator);
		}

		unsigned int width					= 0;
		unsigned int height					= 0;
		unsigned int refreshRateNumerator	= 0;
		unsigned int refreshRateDenominator = 0;
		float refreshRate					= 0;
	};

	struct DisplayAdapter
	{
		DisplayAdapter(const std::string& name, const unsigned int memory, const unsigned int vendor_id, void* data)
		{
			this->name		= name;
			this->memory	= memory;
			this->vendorID	= vendor_id;
			this->data		= data;
		}

		bool IsNvidia() const	{ return vendorID == 0x10DE || name.find("NVIDIA") != std::string::npos; }
		bool IsAmd() const		{ return vendorID == 0x1002 || vendorID == 0x1022 || name.find("AMD") != std::string::npos; }
		bool IsIntel() const	{ return vendorID == 0x163C || vendorID == 0x8086 || vendorID == 0x8087 || name.find("Intel") != std::string::npos;}

		std::string name		= "Unknown";
		unsigned int vendorID	= 0;
		unsigned int memory		= 0;
		void* data				= nullptr;
	};

	class ENGINE_CLASS RHI_Device
	{
	public:
		RHI_Device();
		~RHI_Device();

		//= API ===================================================================================
		bool ProfilingCreateQuery(void** query, RHI_Query_Type type) const;
		bool ProfilingQueryStart(void* query_object) const;
		bool ProfilingGetTimeStamp(void* query_object) const;
		float ProfilingGetDuration(void* query_disjoint, void* query_start, void* query_end) const;
		void ProfilingReleaseQuery(void* query_object);
		unsigned int ProfilingGetGpuMemory();
		unsigned int ProfilingGetGpuMemoryUsage();
		//=========================================================================================

		//= ADAPTERS ============================================================================================================================		
		void AddDisplayMode(unsigned int width, unsigned int height, unsigned int refresh_rate_numerator, unsigned int refresh_rate_denominator);
		bool GetDidsplayModeFastest(DisplayMode* display_mode);
		void AddAdapter(const std::string& name, unsigned int memory, unsigned int vendor_id, void* adapter);
		void SetPrimaryAdapter(const DisplayAdapter* primary_adapter);
		const std::vector<DisplayAdapter>& GetAdapters() const	{ return m_displayAdapters; }
		const DisplayAdapter* GetPrimaryAdapter()				{ return m_primaryAdapter; }
		//=======================================================================================================================================

		auto IsInitialized() const	{ return m_initialized; }
		auto GetContext() const		{ return m_rhi_context; }

	private:	
		bool m_initialized						= false;
		RHI_Context* m_rhi_context				= nullptr;
		const DisplayAdapter* m_primaryAdapter	= nullptr;
		std::vector<DisplayMode> m_displayModes;
		std::vector<DisplayAdapter> m_displayAdapters;	
	};
}
