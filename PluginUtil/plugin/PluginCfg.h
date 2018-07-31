#pragma once

#include <PluginDefine.h>

namespace Liar
{
	enum LiarMeshExportType
	{
		NORMAL_CHIRLD,
		INDEPENDENT_CHIRLD
	};

	class PluginCfg
	{
	public:
		PluginCfg();
		~PluginCfg();

	public:
		int meshExportType;
		bool posNormalize;
	};
}

