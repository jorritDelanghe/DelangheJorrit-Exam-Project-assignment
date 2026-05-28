#pragma once


namespace dae
{
	struct InputBinding
	{
		
	};
	class BaseScene
	{
	public:
		virtual~BaseScene() = default;
		virtual void LoadScene() = 0;
	};
}