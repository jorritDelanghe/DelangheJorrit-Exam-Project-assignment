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

		virtual void Render()const override;

		//rule of 5
		CacheTestComponent(const CacheTestComponent& other) = delete;
		CacheTestComponent(CacheTestComponent&& other) = delete;
		CacheTestComponent& operator=(const CacheTestComponent& other) = delete;
		CacheTestComponent& operator= (CacheTestComponent&& other) = delete;


	private:
		void RunExceriseOne() const;
		void RunExerciseTwo() const;
		void RunExerciseTwoAlternative() const;

		mutable int m_numSamplesExc1{10};
		mutable int m_numSamplesExc2{10};
		mutable std::vector<float> m_timingsExc1;
		mutable std::vector<float> m_timingsExc2;
		mutable std::vector<float> m_timingsExc2Alternative;
	};

}