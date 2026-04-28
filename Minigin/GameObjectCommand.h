#pragma once
#include "Command.h"
#include <glm/glm.hpp>
namespace dae
{
	//gameobject
	class GameObjectCommand :public Command
	{
	public:
		explicit GameObjectCommand(GameObject* gameObject);
		virtual ~GameObjectCommand() noexcept override = default;

		GameObjectCommand(const GameObjectCommand& other) = delete;
		GameObjectCommand(GameObjectCommand&& other) = delete;
		GameObjectCommand& operator=(const GameObjectCommand& other) = delete;
		GameObjectCommand& operator=(GameObjectCommand&& other) = delete;

	protected:
		GameObject* GetGameObject()const;
	private:
		GameObject* m_pGameObject;
	};

	//die
	class DieCommand final: public GameObjectCommand
	{
	public:
		explicit DieCommand(GameObject* gameObject);
		virtual ~DieCommand() noexcept override = default;

		DieCommand(const DieCommand& other) = delete;
		DieCommand(DieCommand&& other) = delete;
		DieCommand& operator=(const DieCommand& other) = delete;
		DieCommand& operator=(DieCommand&& other) = delete;

		virtual void Execute()override;
	};
	//points command
	class GainPointsCommand final: public GameObjectCommand
	{
	public:
		explicit GainPointsCommand(GameObject* gameObject, int points);
		virtual~GainPointsCommand()noexcept override = default;

		GainPointsCommand(const GainPointsCommand& other) = delete;
		GainPointsCommand(GainPointsCommand&& other) = delete;
		GainPointsCommand& operator=(const GainPointsCommand& other) = delete;
		GainPointsCommand& operator=(GainPointsCommand&& other) = delete;

		virtual void Execute() override;
	private:
		int m_points{};
	};
}

