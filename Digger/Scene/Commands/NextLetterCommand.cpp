#include "NextLetterCommand.h"

dae::NextLetterCommand::NextLetterCommand(TextComponent* text, int maxLength)
    : m_text(text)
    , m_maxLength(maxLength)
{
}

void dae::NextLetterCommand::Execute()
{
    std::string name{ m_text->GetText() };

    if (name.size() < static_cast<size_t>(m_maxLength))
    {
        name += 'A'; //next letter
        m_text->SetText(name);
    }
}
