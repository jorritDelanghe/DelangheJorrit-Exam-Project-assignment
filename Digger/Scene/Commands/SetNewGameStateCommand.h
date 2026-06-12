#pragma once
#pragma once

#include "Command.h"

namespace dae
{
	class DiggerSceneManager;
	class SetNewGameStateCommand final : public Command
	{
	public:
		explicit SetNewGameStateCommand(DiggerSceneManager* sceneManager); //no reference can not be reseated
		virtual ~SetNewGameStateCommand() noexcept override = default;

		SetNewGameStateCommand(const SetNewGameStateCommand& other) = delete;
		SetNewGameStateCommand(SetNewGameStateCommand&& other) = delete;
		SetNewGameStateCommand& operator= (const SetNewGameStateCommand& other) = delete;
		SetNewGameStateCommand& operator= (SetNewGameStateCommand&& other) = delete;

		virtual void Execute() override;

	private:
		DiggerSceneManager* m_sceneManager;
	};

}