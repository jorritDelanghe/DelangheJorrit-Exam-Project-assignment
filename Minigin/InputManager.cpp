#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include "InputManager.h"
#include "Controller.h"
namespace dae
{
	class InputManager::InputManagerImpl 
	{
	public:
		InputManagerImpl()
		{
			constexpr int numControllers{ 1 };
			for (int index{}; index < numControllers; ++index)
			{
				m_Controllers.emplace_back(std::make_unique<Controller>(index));
			}
		}
		struct KeyBoardBinding
		{
			SDL_Scancode key{};
			TriggerType trigger{};
			std::unique_ptr<Command> command{};
		};
		struct ControllerBinding
		{
			unsigned int button{};
			InputManager::TriggerType triggerType{};
			std::unique_ptr<Command> command{};
			int controllerIndex{ 0 };
		};
		std::vector<ControllerBinding> m_controllerBindings{};
		std::vector<KeyBoardBinding> m_keyBoardBindings{};

		void UpdateControllers()
		{
			for (auto& controller : m_Controllers)
			{
				controller->Update();
			}
		}
		void BindControllerCommand(unsigned int button, TriggerType triggerType, std::unique_ptr<Command> pCommand)
		{
			m_controllerBindings.emplace_back(
				ControllerBinding{
					button
					,triggerType
					,std::move(pCommand) });
		}
		void BindKeyBoardCommand(SDL_Scancode key , TriggerType triggerType, std::unique_ptr<Command>pCommand)
		{
			m_keyBoardBindings.emplace_back(
				KeyBoardBinding{
					key
					,triggerType
				,std::move(pCommand)
				});
		}
		void UnBindControllerCommand(unsigned int button)
		{
			std::erase_if(m_controllerBindings,
				[button](const ControllerBinding& binding)
				{
					return(button == binding.button);
				});
		}
		void UnBindKeyBoardCommand(SDL_Scancode key)
		{
			std::erase_if(m_keyBoardBindings,
				[key](const KeyBoardBinding& binding)
				{
					return key == binding.key;
				});
		}
		void ProcessControllerBindings()
		{
			for (auto& controllerBinding : m_controllerBindings)
			{
				if (controllerBinding.controllerIndex >= static_cast<int>(m_controllerBindings.size())) continue;
				auto& controller = m_Controllers[controllerBinding.controllerIndex];

				switch (controllerBinding.triggerType)
				{
				case TriggerType::IsDownThisFrame:
					
						if (controller->IsDownThisFrame(controllerBinding.button))
						{
							controllerBinding.command->Execute();
						}		
					break;
				case TriggerType::IsUpThisFrame:
					
						if (controller->IsUpThisFrame(controllerBinding.button))
						{
							controllerBinding.command->Execute();
						}
					
					break;
				case TriggerType::Isdown:
					
						if (controller->IsDown(controllerBinding.button))
						{
							controllerBinding.command->Execute();
						}
					
					break;
				}
			}
		}
		void ProcessKeyBoardBindings(SDL_Scancode key, TriggerType trigger)
		{
			for (auto& binding : m_keyBoardBindings)
			{
				if (binding.key == key && binding.trigger == trigger)
				{
					binding.command->Execute();
				}
			}
		}
		void ProcessHeldKeys(const bool*pKeyBoardState)
		{
			for (auto& binding : m_keyBoardBindings)
			{

				if (binding.trigger == TriggerType::Isdown)
				{
					if (pKeyBoardState[binding.key])
					{
						binding.command->Execute();
					}
				}
			}
		}
	private:
		std::vector<std::unique_ptr<Controller>> m_Controllers{};
	
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
			if (e.type == SDL_EVENT_KEY_DOWN) 
			{
				m_pInputManagerImpl->ProcessKeyBoardBindings(
					e.key.scancode, 
					TriggerType::IsDownThisFrame);
			}
			if (e.type == SDL_EVENT_KEY_UP)
			{
				m_pInputManagerImpl->ProcessKeyBoardBindings(
					e.key.scancode,
					TriggerType::IsUpThisFrame
				);
			}
			if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
			{
			}
			// etc...
			//process event for IMGUI
			//ImGui_ImplSDL3_ProcessEvent(&e);
		}
		//keyboard
		SDL_PumpEvents();
		const bool* pKeyBoardState = SDL_GetKeyboardState(nullptr);
		m_pInputManagerImpl->ProcessHeldKeys(pKeyBoardState);
		//controller
		m_pInputManagerImpl->UpdateControllers();
		m_pInputManagerImpl->ProcessControllerBindings();
		return true;
	}
	InputManager::~InputManager() = default;
	void InputManager::BindControllerCommand(unsigned int button, TriggerType trigger, std::unique_ptr<Command> pCommand)
	{
		m_pInputManagerImpl->BindControllerCommand(button, trigger, std::move(pCommand));
	}

	void InputManager::UnbindControllerCommand(unsigned int button)
	{
		m_pInputManagerImpl->UnBindControllerCommand(button);
	}

	void InputManager::BindKeyboardCommand(SDL_Scancode key, TriggerType trigger, std::unique_ptr<Command> pCommand)
	{
		m_pInputManagerImpl->BindKeyBoardCommand(key, trigger,std::move(pCommand));
	}

	void InputManager::UnbindKeyboardCommand(SDL_Scancode key)
	{
		m_pInputManagerImpl->UnBindKeyBoardCommand(key);
	}

}
