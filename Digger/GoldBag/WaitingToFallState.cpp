#include "WaitingToFallState.h"
#include "FallingState.h"

dae::WaitingToFallState::WaitingToFallState(float maxTimeToWait, float fallSpeed)
	:m_maxTimeToWait(maxTimeToWait)
	, m_fallSpeed(fallSpeed)
{
}

dae::GoldBagState* dae::WaitingToFallState::Update(GoldBagComponent* , float deltaTime)
{
    m_timerTunnelUnderGoldBag += deltaTime;

    if (m_timerTunnelUnderGoldBag > m_maxTimeToWait)
    {
        m_timerTunnelUnderGoldBag = 0.f;
        return new FallingState(m_fallSpeed);
    }
    return nullptr;
}
