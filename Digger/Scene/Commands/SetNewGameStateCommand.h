#pragma once
#pragma once

#include "Command.h"
#include <memory>
#include "Scene/GameState/GameState.h"
namespace dae
{
	class DiggerSceneManager;
	class SetNewGameStateCommand final : public Command
	{
	public:
		explicit SetNewGameStateCommand(DiggerSceneManager* sceneManager, std::unique_ptr<GameState> pGameState); //no reference can not be reseated
		virtual ~SetNewGameStateCommand() noexcept override = default;

		SetNewGameStateCommand(const SetNewGameStateCommand& other) = delete;
		SetNewGameStateCommand(SetNewGameStateCommand&& other) = delete;
		SetNewGameStateCommand& operator= (const SetNewGameStateCommand& other) = delete;
		SetNewGameStateCommand& operator= (SetNewGameStateCommand&& other) = delete;

		virtual void Execute() override;

	private:
		DiggerSceneManager* m_sceneManager{nullptr};
		std::unique_ptr<GameState> m_gameState{ nullptr };

	};

}