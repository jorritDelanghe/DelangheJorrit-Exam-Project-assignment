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
		void BindControllerCommand(unsigned int button,TriggerType trigger, std::unique_ptr<Command> pCommand);
		void UnbindControllerCommand(unsigned int button);
		void BindKeyboardCommand(SDL_Scancode key,TriggerType trigger, std::unique_ptr<Command> pCommand);
		void UnbindKeyboardCommand(SDL_Scancode key);

		class InputManagerImpl;
	private:
		std::unique_ptr<InputManagerImpl> m_pInputManagerImpl;
	};

	namespace GamepadButton
	{
		constexpr unsigned int DpadUp = 0x0001;
		constexpr unsigned int DpadDown = 0x0002;
		constexpr unsigned int DpadLeft = 0x0004;
		constexpr unsigned int DpadRight = 0x0008;
		constexpr unsigned int A = 0x1000;
		constexpr unsigned int B = 0x2000;
		constexpr unsigned int X = 0x4000;
		constexpr unsigned int Y = 0x8000;
	}
}
