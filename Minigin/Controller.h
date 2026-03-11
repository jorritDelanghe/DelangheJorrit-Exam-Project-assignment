#pragma once
#include <memory>
namespace dae
{
	class Controller
	{
	public:
		Controller(int controllerIndex);
		~Controller();

		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		void Update();
		bool IsDown(unsigned int button) const;
		bool IsDownThisFrame(unsigned int button) const;
		bool IsUpThisFrame(unsigned int button) const;

	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pControllerImpl;
	};

}