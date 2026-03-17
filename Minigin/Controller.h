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
		#if _WIN32
		class ControllerXInputImpl;
		std::unique_ptr<ControllerXInputImpl> m_pControllerXInputImpl;
		#else
		class ControllerSdlImpl;
		std::unique_ptr<ControllerSdlImpl> m_pControllerSDLImpl;
		#endif
	};

}