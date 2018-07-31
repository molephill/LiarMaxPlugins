#include "PluginCfg.h"

namespace Liar
{
	PluginCfg::PluginCfg()
		:posNormalize(false), revertZY(true), revertUV(true), singleExportModel(false)
		, exportPos(true), exportNormal(true), exportColor(false), exportUV(true)
	{
	}


	PluginCfg::~PluginCfg()
	{
	}
}
