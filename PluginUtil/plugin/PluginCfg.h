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
		bool uvZY;

		bool exportPos;
		bool exportNormal;
		bool exportColor;
		bool exportUV;
	};
}

