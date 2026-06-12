#include "ChangeLetterCommand.h"

dae::ChangeLetterCommand::ChangeLetterCommand(TextComponent* text, int m_amountToGoToNext)
	:m_text(text),
	m_amountToGoToNext(m_amountToGoToNext)
{
}

void dae::ChangeLetterCommand::Execute()
{
	ChangeLetter();
}

void dae::ChangeLetterCommand::ChangeLetter()
{
	const char firstLetter{ 'A' };
	std::string highScoreName{m_text->GetText()};

	if (highScoreName.empty())
	{
		highScoreName += firstLetter;
	}
	//change last letter name
	char currentLetter{ highScoreName.back() };
	currentLetter += static_cast<char>(m_amountToGoToNext);

   if (currentLetter < 'A')
   {
	   currentLetter = 'Z';
   }
   if (currentLetter > 'Z')
   {
	   currentLetter = 'A';
   }
   highScoreName.back() = currentLetter;
   m_text->SetText(highScoreName);
}
