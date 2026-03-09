#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include "CacheTestComponent.h"
#include <chrono>
#include <algorithm>
#include <numeric>

namespace dae
{
    struct transform
    {
        float matrix[16] =
        {
            1,0,0,0
            ,0,1,0,0
            ,0,0,1,0
            ,0,0,0,1
        };
    };
    class GameObject3D
    {
    public:
        transform local;
        int id{};
    };
    class GameObject3DAlternative
    {
    public: 
        int id{};
        //transform is stored somewhere else to not load in 68 bytes into the cache, but just 4 for the id
    };
    template<typename Fn>
    static std::vector<float> RunCachTimeTest(Fn loopfn, int numSamples)
    {
        using clock = std::chrono::high_resolution_clock;
        std::vector<float> times;
        constexpr int total = 11;
        times.reserve(total);
        std::vector<long long>samples;
		numSamples = std::max(3, numSamples); //need at least 3 samples to be able to remove the min and max outliers
       
        for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
        {
           samples.clear();
		   samples.reserve(numSamples);
            for (int index{}; index < numSamples; ++index)
            {
                const auto start = clock::now();
                loopfn(stepsize);
                const auto end = clock::now();
                samples.push_back( std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
            }
             //sort and remove outliers
			std::sort(samples.begin(), samples.end());
            samples.erase(samples.begin()); //delete min outlier
			samples.pop_back(); //delete max outlier
           
            //average
			long long average = std::accumulate(samples.begin(), samples.end(), 0LL) / static_cast<long long>(samples.size());
            times.push_back(static_cast<float>(average));
        }
        return times;
    }
    CacheTestComponent::CacheTestComponent(GameObject* pOwner)
	    :Component(pOwner)
    {
    }
    void CacheTestComponent::Render()const
    {
        //exercise1
        ImGui::Begin("Excersie 1 - int buffer");
        ImGui::SliderInt("Sample Count", &m_numSamplesExc1, 1, 50);
      
        if (ImGui::Button("Trash the cache"))
        {
            RunExceriseOne();
        }
        if (!m_timingsExc1.empty())
        {
            const float maxValue = *std::max_element(m_timingsExc1.begin(), m_timingsExc1.end());
            ImGui::PlotLines("##exc1", m_timingsExc1.data(), static_cast<int>(m_timingsExc1.size()),
                0, nullptr, 0.0f, maxValue, ImVec2(400, 120));
        }
        ImGui::End();
        //excerise2
        ImGui::Begin("exercise 2 - struct buffer");
        ImGui::InputInt("Sample Count", &m_numSamplesExc2);
        if (ImGui::Button("Trash The cash with GameObject3D"))
        {
			RunExerciseTwo();   
        }
        if (ImGui::Button("Trash The cash with GameObject3D alternative"))
        {
			RunExerciseTwoAlternative();    
        }
        if (!m_timingsExc2.empty())
        {
            ImGui::PlotLines("##exc2", m_timingsExc2.data(), static_cast<int>(m_timingsExc2.size()),
				0, nullptr, 0.0f, *std::max_element(m_timingsExc2.begin(), m_timingsExc2.end()), ImVec2(400, 120));
        }
        if(!m_timingsExc2Alternative.empty())
        {
            ImGui::PlotLines("##exc2alt", m_timingsExc2Alternative.data(), static_cast<int>(m_timingsExc2Alternative.size()),
                0, nullptr, 0.0f, *std::max_element(m_timingsExc2Alternative.begin(), m_timingsExc2Alternative.end()), ImVec2(400, 120));
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

            }, m_numSamplesExc1);
        delete[] arr;
    }

    void CacheTestComponent::RunExerciseTwo() const
    {
        constexpr int size = 1 << 22;
        GameObject3D* arr = new GameObject3D[size]();
        m_timingsExc2 = RunCachTimeTest([&](int stepSize)
            {
                for (int i{}; i < size; i += stepSize)
                {
					arr[i].id *= 2;
                }
            }, m_numSamplesExc2);

        delete[]arr;
    }

    void CacheTestComponent::RunExerciseTwoAlternative() const
    {
        constexpr int size = 1 << 22;
        GameObject3DAlternative* arr = new GameObject3DAlternative[size]();
        m_timingsExc2Alternative = RunCachTimeTest([&](int stepSize)
            {
                for (int i{}; i < size; i += stepSize)
                {
                    arr[i].id *= 2;
                }
            }, m_numSamplesExc2);

        delete[]arr;
    }
}
