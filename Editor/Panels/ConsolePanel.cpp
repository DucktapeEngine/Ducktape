#include <Panels/ConsolePanel.h>

namespace DT
{
	void ConsolePanel::Update(Engine &engine)
	{
		ImGui::Begin(GetWindowName().c_str(), &isOpen);

		ImGui::TextWrapped("%s", engine.debug.GetOut().c_str());
		ImGui::TextWrapped("%s", engine.debug.GetErr().c_str());

		ImGui::End();
	}
}