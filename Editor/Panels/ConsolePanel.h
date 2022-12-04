#pragma once

#include <Panels/Panel.h>

namespace DT
{
	class ConsolePanel : public Panel
	{
	public:
		inline std::string GetWindowName() override { return "Console"; }

		void Update(Engine &engine) override;
	};
}