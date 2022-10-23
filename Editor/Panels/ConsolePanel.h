#include "Panel.h"
namespace DT
{
	class ConsolePanel : public Panel
	{
	public:
		void Update(Engine &engine) override;
	};
}