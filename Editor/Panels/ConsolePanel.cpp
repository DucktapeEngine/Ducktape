#include <Panels/ConsolePanel.h>

namespace DT
{
	void ConsolePanel::Update(ContextPtr &ctx)
	{
		ImGui::Begin(GetWindowName().c_str(), &isOpen);

		ImGui::TextWrapped("%s", ctx.debug->GetLog().c_str());
		ImGui::TextWrapped("%s", ctx.debug->GetErr().c_str());

		ImGui::End();
	}
}