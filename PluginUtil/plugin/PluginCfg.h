#pragma once

#include <PluginDefine.h>

namespace Liar
{
	enum LiarMeshExportType
	{
		INGORE_CHIRLD,
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
		bool posNormalize
	};
}

