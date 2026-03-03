#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include "CacheTestComponent.h"
#include <chrono>

namespace dae
{



    template<typename Fn>
    static std::vector<float> RunCachTimeTest(Fn loopfn, int numSamples)
    {
        using clock = std::chrono::high_resolution_clock;
        std::vector<float> times;
        times.reserve(numSamples);

        for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
        {
            long long total{};
            for (int index{}; index < numSamples; ++index)
            {
                const auto start = clock::now();
                loopfn(stepsize);
                const auto end = clock::now();
                total += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            }
            const auto average = static_cast<float>(total / numSamples);
            times.push_back(average);
        }
        return times;
    }
    CacheTestComponent::CacheTestComponent(GameObject* pOwner)
	    :Component(pOwner)
    {
    }
    void CacheTestComponent::Update(float)
    {
    
    }
    void CacheTestComponent::Render()const
    {
        ImGui::Begin("Cache");
        ImGui::SliderInt("Sample Count", &m_numSamples, 1, 50);

        //exercise1
        ImGui::SeparatorText("Excersie 1 - int buffer");
        if (ImGui::Button("Run##exc1"))
        {
            RunExceriseOne();
        }
        if (!m_timingsExc1.empty())
        {
            const float maxValue = *std::max_element(m_timingsExc1.begin(), m_timingsExc1.end());
            ImGui::PlotLines("##exc1Plot", m_timingsExc1.data(), static_cast<int>(m_timingsExc1.size()),
                0, nullptr, 0.0f, maxValue, ImVec2(400, 120));
            int step = 1;
            for (float t : m_timingsExc1)
            {
                ImGui::Text("Step %4d: %.0f us", step, t);
                step *= 2;
            }
        }
        ImGui::End();
    }

    void CacheTestComponent::RunExceriseOne() const
    {
        constexpr int size = 1 << 25; //1 bit shift positive over 25 bits
        int* arr = new int[size]();

        m_timingsExc1 = RunCachTimeTest([&](int stepSize)
            {
                for (int i = 0; i < size; i += stepSize)
                {
                    arr[i] *= 2;
                }

            }, m_numSamples);
        delete[] arr;
    }

    void CacheTestComponent::RunExerciseTwo()
    {
    }

    void CacheTestComponent::RunExerciseTwoAlternative()
    {

    }
}
