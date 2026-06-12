#pragma once
#include "Command.h"
#include "TextComponent.h"
namespace dae
{
    class ChangeLetterCommand final : public Command
    {
    public:
       ChangeLetterCommand(TextComponent* text, int m_amountToGoToNext);
       virtual void Execute() override;

    private:
        TextComponent* m_text{nullptr};
        int m_amountToGoToNext{};
        std::string m_highScoreName;

        void ChangeLetter();
    };

}