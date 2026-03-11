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
		struct ControllerBinding
		{
			unsigned int button{};
			InputManager::TriggerType triggerType{};
			std::unique_ptr<Command> command{};
			int controllerIndex{ 0 };
		};
		std::vector<ControllerBinding> m_controllerBindings{};

		void UpdateControllers()
		{
			for (auto& controller : m_Controllers)
			{
				controller->Update();
			}
		}
		void BindCommand(unsigned int button, TriggerType triggerType, std::unique_ptr<Command> pCommand)
		{
			m_controllerBindings.emplace_back(
				ControllerBinding{
					button
					,triggerType
					,std::move(pCommand) });
		}
		void UnBindCommand(unsigned int button)
		{
			std::erase_if(m_controllerBindings,
				[button](const ControllerBinding& binding)
				{
					return(button == binding.button);
				});
		}
		void ProcessBindings()
		{
			for (auto& controllerBinding : m_controllerBindings)
			{
				if (controllerBinding.controllerIndex >= m_controllerBindings.size()) continue;
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
			if (e.type == SDL_EVENT_KEY_DOWN) {
			
			}
			if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			
			}
			// etc...
			//process event for IMGUI
			//ImGui_ImplSDL3_ProcessEvent(&e);
		}
		m_pInputManagerImpl->UpdateControllers();
		m_pInputManagerImpl->ProcessBindings();
		return true;
	}
	InputManager::~InputManager() = default;
	void InputManager::BindCommand(unsigned int button, TriggerType trigger, std::unique_ptr<Command> pCommand)
	{
		m_pInputManagerImpl->BindCommand(button, trigger, std::move(pCommand));
	}

	void InputManager::UnbindCommand(unsigned int button)
	{
		m_pInputManagerImpl->UnBindCommand(button);
	}

}
