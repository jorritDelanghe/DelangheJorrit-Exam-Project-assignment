#include "Controller.h"
#if _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include "Xinput.h" //not in the header so I get pimple, needs things in windows.h always put under windows.h
	#pragma comment(lib,"xinput.lib")
#else
	#include <SDl3/SDL.h>
	#include <SDL3/SDL_gamepad.h>
#endif
namespace dae
{
#if _WIN32
	class Controller::ControllerXInputImpl final
	{
	public:
		explicit ControllerXInputImpl(int controllerIndex)
			:m_controllerIndex{ controllerIndex }
		{

		}
		void UpdateXInput()
		{
			CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE)); //copies values of states
			ZeroMemory(&m_currentState, sizeof(XINPUT_STATE)); //cleans memory state
			XInputGetState(m_controllerIndex, &m_currentState); //get new state

			auto buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons; //xor
			m_buttonsPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons; //and
			m_buttonsReleasedThisFrame = buttonChanges & (~m_currentState.Gamepad.wButtons); //and not

		}
		bool IsDownThisFrame(unsigned int button) const //unsinged because bitmasks are never negative
		{
			return m_buttonsPressedThisFrame & button;
		}
		bool IsUpThisFrame(unsigned int button) const
		{
			return m_buttonsReleasedThisFrame & button;
		}
		bool IsButtonPressed(unsigned int button) const
		{
			return m_currentState.Gamepad.wButtons & button;
		}
	private:
		XINPUT_STATE m_previousState{};
		XINPUT_STATE m_currentState{};
		int m_controllerIndex{ 0 }; //0 = first controller
		WORD m_buttonsPressedThisFrame{};
		WORD m_buttonsReleasedThisFrame{};
	};

#else
	class Controller::ControllerSdlImpl final
	{
	public: 
		explicit ControllerSdlImpl(int controllerIndex)
		{
			int count{ 0 };
			SDL_JoystickID* gamepads = SDL_GetGamepads(&count); //list of available gamepads
			if (gamepads && controllerIndex < count)
			{
				m_pGamePad = SDL_OpenGamepad(gamepads[controllerIndex]);
			}
			SDL_free(gamepads);

		}
		~ControllerSdlImpl()
		{
			if (m_pGamePad)
			{
				SDL_CloseGamepad(m_pGamePad);
			}
		}
		void Update()
		{
			m_previousButtons = m_currentButtons;
			m_currentButtons = 0;
			if (!m_pGamePad) return;

			for (int index{}; index < SDL_GAMEPAD_BUTTON_COUNT; ++index)
			{
				if (SDL_GetGamepadButton(m_pGamePad, static_cast<SDL_GamepadButton>(index))) //if button is pressed set current button
				{
					m_currentButtons |= (1u << index); //|= adds every button that is pressed to the total
				}
			}
			auto buttonChanges = m_currentButtons ^ m_previousButtons;
			m_buttonsPressedThisFrame = buttonChanges & m_currentButtons;
			m_buttonsReleasedThisFrame = buttonChanges & ~m_currentButtons;

		}
		bool IsDownThisFrame(unsigned int button) const
		{
			return m_buttonsPressedThisFrame & button;
		}
		bool IsUpThisFrame(unsigned int button)const
		{
			return m_buttonsReleasedThisFrame & button;
		}
		bool IsButtonPressed(unsigned int button) const
		{
			return m_currentButtons & button;
		}
	private:
		SDL_Gamepad* m_pGamePad{ nullptr };
		unsigned int m_previousButtons{};
		unsigned int m_currentButtons{};
		unsigned int m_buttonsPressedThisFrame{};
		unsigned int m_buttonsReleasedThisFrame{};
	};
#endif

	Controller::Controller(int controllerIndex)
#if _WIN32
		:m_pControllerXInputImpl{std::make_unique<ControllerXInputImpl>(controllerIndex)}
#else
		: m_pControllerSDLImpl{std::make_unique<ControllerSdlImpl>(controllerIndex) }
#endif
	{
	}
	Controller::~Controller() = default;
	void Controller::Update()
	{
#if _WIN32
		m_pControllerXInputImpl->UpdateXInput();
#else
		m_pControllerSDLImpl->Update();
#endif
	}

	bool Controller::IsDown(unsigned int button) const
	{
#if _WIN32
		return m_pControllerXInputImpl->IsButtonPressed(button);
#else
		return m_pControllerSDLImpl->IsButtonPressed(button);
#endif
	}

	bool Controller::IsDownThisFrame(unsigned int button) const
	{
#if _WIN32
		return m_pControllerXInputImpl->IsDownThisFrame(button);
#else
		return m_pControllerSDLImpl->IsDownThisFrame(button);
#endif
	}

	bool Controller::IsUpThisFrame(unsigned int button) const
	{
#if _WIN32
		return m_pControllerXInputImpl->IsUpThisFrame(button);
#else
		return m_pControllerSDLImpl->IsUpThisFrame(button);
#endif
	}
}
