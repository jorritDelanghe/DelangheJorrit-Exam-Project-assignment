#include "ConfirmNameCommand.h"
#include"Scene/ScoreBoard/HighScoreBoardManager.h"


dae::ConfirmNameCommand::ConfirmNameCommand(TextComponent* text, HighScoreBoardManager* highScoreManager, int score)
    : m_text(text)
    , m_highScoreManager(highScoreManager)
    , m_score(score)
{
}

void dae::ConfirmNameCommand::Execute()
{
    m_highScoreManager->AddHighScore(m_text->GetText(), m_score);
}
