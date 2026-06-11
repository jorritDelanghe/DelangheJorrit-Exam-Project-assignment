#include "EndScreenState.h"

dae::EndScreenState::EndScreenState(bool hasWon, int score)
	:m_hasWon(hasWon)
	,m_score(score)
{
}

void dae::EndScreenState::OnEnter(DiggerSceneManager* pDiggerSceneManager)
{
}

void dae::EndScreenState::OnExit(DiggerSceneManager* pDiggerSceneManager)
{
}
