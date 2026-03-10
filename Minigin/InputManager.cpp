#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include "InputManager.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Xinput.h" //not in the header so I get pimple, needs things in windows.h always put under windows.h
namespace dae
{
	class InputManager::InputManagerImpl 
	{

	public:
		struct ControllerBinding
		{
			unsigned int button{};
			InputManager::TriggerType triggerType{};
			std::unique_ptr<Command> command{};
		};
		std::vector<ControllerBinding> m_controllerBindings{};

		void BindCommand(unsigned int button, TriggerType triggerType, std::unique_ptr<Command> pCommand)
		{
			m_controllerBindings.emplace_back(
				ControllerBinding{
					button
					,triggerType
					,std::move(pCommand) });
		}
		void ProcessBindings()
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

	InputManager::InputManager()
		:m_pInputManagerImpl{std::make_unique<InputManagerImpl>()}
	{

	}
	bool InputManager::ProcessInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				return false;
			}
			if (e.type == SDL_EVENT_KEY_DOWN) {
			
			}
			if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			
			}
			// etc...
			//process event for IMGUI
			//ImGui_ImplSDL3_ProcessEvent(&e);
		}
		m_pInputManagerImpl->UpdateXInput();
		m_pInputManagerImpl->ProcessBindings();
		return true;
	}

	void InputManager::BindCommand(unsigned int button, TriggerType trigger, std::unique_ptr<Command> pCommand)
	{
		m_pInputManagerImpl->BindCommand(button, trigger, std::move(pCommand));
	}

}
