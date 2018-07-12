#pragma once

#include <vector>
#include <PluginDefine.h>

#ifdef PLUGINS
#include <triobj.h>
#endif // !PLUGINS


namespace Liar
{
	class LiarPoint3
	{
	public:
		LiarPoint3() :x(0.0f), y(0.0f), z(0.0f) {};

	public:
		float x;
		float y;
		float z;

#ifdef PLUGINS
		void ParseMaxColor(Color color)
		{
			x = color.r;
			y = color.g;
			z = color.b;
		}

		void ParseMaxPoint3(Point3 point)
		{
			x = point.x;
			y = point.y;
			z = point.z;
		}

		void ParseMaxPoint3(Point3 point, bool zy)
		{
			if (zy)
			{
				x = point.x;
				y = point.z;
				z = point.y;
			}
			else
			{
				ParseMaxPoint3(point);
			}
		}
#endif // PLUGINS

	};

	class LiarPoint2
	{
	public:
		LiarPoint2() :x(0.0f), y(0.0f) {};

	public:
		float x;
		float y;

#ifdef PLUGINS
	void ParseMaxPoint2(Point2 point)
	{
		x = point.x;
		y = point.y;
	}

	void ParseMaxPoint3(Point3 point)
	{
		x = point.x;
		y = point.y;
	}

	void ParseMaxPoint2(Point2 point, bool delV)
	{
		if (delV)
		{
			x = point.x;
			y = 1 - point.y;
		}
		else
		{
			ParseMaxPoint2(point);
		}
	}

	void ParseMaxPoint3(Point3 point, bool delV)
	{
		if (delV)
		{
			x = point.x;
			y = 1 - point.y;
		}
		else
		{
			ParseMaxPoint3(point);
		}
	}
#endif // PLUGINS

	};

	class LiarVertexBuffer
	{
	public:
		LiarVertexBuffer();
		~LiarVertexBuffer();

	public:
		Liar::LiarPoint3* position;
		Liar::LiarPoint3* normal;
		Liar::LiarPoint3* color;
		Liar::LiarPoint2* uv;

#ifdef PLUGINS
	public:
		void ParseMesh(Mesh*, int, bool zy = true);
#endif // PLUGINS

	};
}

