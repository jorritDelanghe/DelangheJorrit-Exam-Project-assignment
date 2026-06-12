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

	if (m_highScoreName.empty())
	{
		m_highScoreName += firstLetter;
	}
	//change last letter name
	char& currentLetter{ m_highScoreName.back() };
	currentLetter += m_amountToGoToNext;

   if (currentLetter < 'A')
   {
	   currentLetter = 'Z';
   }
   if (currentLetter > 'Z')
   {
	   currentLetter = 'A';
   }

   m_text->SetText(m_highScoreName);
}
