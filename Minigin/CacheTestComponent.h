#pragma once
#include "Component.h"
#include <vector>

namespace dae
{
	class CacheTestComponent final: public Component
	{
	public:
		explicit CacheTestComponent(GameObject* pOwner);
		virtual ~CacheTestComponent() override = default;

		virtual void Update(float deltaTime) override;
		virtual void Render()const override;

		//rule of 5
		CacheTestComponent(const CacheTestComponent& other) = delete;
		CacheTestComponent(CacheTestComponent&& other) = delete;
		CacheTestComponent& operator=(const CacheTestComponent& other) = delete;
		CacheTestComponent& operator= (CacheTestComponent&& other) = delete;


	private:
		void RunExceriseOne() const;
		void RunExerciseTwo();
		void RunExerciseTwoAlternative();

		mutable int m_numSamples{10};
		mutable std::vector<float> m_timingsExc1;
		mutable std::vector<float> m_timingsExc2;
		mutable std::vector<float> m_timingsExc2Alternative;
	};

}