#pragma once

#include "Command.h"

namespace dae
{
	class DiggerSceneManager;
	class SkipToNextLevelCommand final : public Command
	{
	public:
		explicit SkipToNextLevelCommand(DiggerSceneManager* sceneManager); //no reference can not be reseated
		virtual ~SkipToNextLevelCommand() noexcept override = default;

		SkipToNextLevelCommand(const SkipToNextLevelCommand& other) = delete;
		SkipToNextLevelCommand(SkipToNextLevelCommand&& other) = delete;
		SkipToNextLevelCommand& operator= (const SkipToNextLevelCommand& other) = delete;
		SkipToNextLevelCommand& operator= (SkipToNextLevelCommand&& other) = delete;

		virtual void Execute() override;

	private:
		DiggerSceneManager* m_sceneManager;
	};

}