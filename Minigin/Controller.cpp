#include "Controller.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Xinput.h" //not in the header so I get pimple, needs things in windows.h always put under windows.h
#pragma comment(lib,"xinput.lib")
#endif
namespace dae
{
	class Controller::ControllerImpl
	{
	public:
		#ifdef _WIN32
		ControllerImpl(int controllerIndex)
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


	Controller::Controller(int controllerIndex)
		:m_pControllerImpl{std::make_unique<ControllerImpl>(controllerIndex)}
	{
	}
	Controller::~Controller() = default;
	void Controller::Update()
	{
		m_pControllerImpl->UpdateXInput();
	}

	bool Controller::IsDown(unsigned int button) const
	{
		return m_pControllerImpl->IsButtonPressed(button);
	}

	bool Controller::IsDownThisFrame(unsigned int button) const
	{
		return m_pControllerImpl->IsDownThisFrame(button);
	}

	bool Controller::IsUpThisFrame(unsigned int button) const
	{
		return m_pControllerImpl->IsUpThisFrame(button);
	}

#endif
}
