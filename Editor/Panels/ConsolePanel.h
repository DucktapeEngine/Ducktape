#pragma once

#include <Panels/Panel.h>

namespace DT
{
	class ConsolePanel : public Panel
	{
	public:
		const char* GetWindowName() override;
		void Update(Engine &engine) override;
	private:
		const char* windowName = "Console";
	};
}