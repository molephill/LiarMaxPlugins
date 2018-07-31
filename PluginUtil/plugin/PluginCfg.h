#pragma once

#include <PluginDefine.h>

namespace Liar
{
	class PluginCfg
	{
	public:
		PluginCfg();
		~PluginCfg();

	public:
		bool posNormalize;
		bool revertZY;
		bool revertUV;
		bool singleExportModel;

		bool exportPos;
		bool exportNormal;
		bool exportColor;
		bool exportUV;
	};
}

