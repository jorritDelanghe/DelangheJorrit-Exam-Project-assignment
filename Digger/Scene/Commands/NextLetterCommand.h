#pragma once
#include "Command.h"
#include "TextComponent.h"
namespace dae
{
    class NextLetterCommand final : public Command
    {
    public:
        NextLetterCommand(TextComponent* text, int maxLength = 3);
        virtual void Execute() override;

    private:
        TextComponent* m_text{ nullptr };
        int m_maxLength{};
    };
}