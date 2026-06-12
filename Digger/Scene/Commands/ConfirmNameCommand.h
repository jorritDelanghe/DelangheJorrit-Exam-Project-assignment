#pragma once
#include "Command.h"
#include "TextComponent.h"
namespace dae
{
    class HighScoreBoardManager;
    class ConfirmNameCommand final : public Command
    {
    public:
        ConfirmNameCommand(TextComponent* text, HighScoreBoardManager* highScoreManager, int score);
        virtual void Execute() override;

    private:
        TextComponent* m_text{ nullptr };
        HighScoreBoardManager* m_highScoreManager{ nullptr };
        int m_score{};
    };

}