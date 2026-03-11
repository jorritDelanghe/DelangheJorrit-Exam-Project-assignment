#pragma once
#include "Singleton.h"
#include "Command.h"
#include <memory>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		bool ProcessInput();
		enum class TriggerType
		{
			Isdown //keeps being triggered
			,IsDownThisFrame
			,IsUpThisFrame
		};
		void BindCommand(unsigned int button,TriggerType trigger, std::unique_ptr<Command> pCommand);
		void UnbindCommand(unsigned int button);

		class InputManagerImpl;
	private:
		std::unique_ptr<InputManagerImpl> m_pInputManagerImpl;
	};
	

}
