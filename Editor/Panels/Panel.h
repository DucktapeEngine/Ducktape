#pragma once

#include <Core/Engine.h>
#include <Core/ImGui.h>

namespace DT
{
	constexpr float DEG2RAD = 0.0174533f;

	class Panel
	{
	public:
		bool isOpen = false;

		virtual inline std::string GetWindowName() { return "Unnamed Window"; }
		virtual void Start(ContextPtr &ctx) {}
		virtual void Update(ContextPtr &ctx) {}
		virtual void Destroy(ContextPtr &ctx) {}
	};
}