#include "HighScoreBoardManager.h"

#include <fstream>
#include <algorithm>
#include <windows.h>

dae::HighScoreBoardManager::HighScoreBoardManager(const std::string& filePath)
	: m_filePath(filePath)
{
	LoadFile(m_filePath);
	OutputDebugStringA(("size after load: " + std::to_string(m_highScores.size()) + "\n").c_str());
}

dae::HighScoreBoardManager::~HighScoreBoardManager()
{
}

bool dae::HighScoreBoardManager::CheckIfHighScore(int score) const
{
	if (m_highScores.empty()) return true;

	for (const auto& highScore : m_highScores)
	{
		if (highScore.score <= score)
		{
			return true;
		}
	}
	return false;
}

bool dae::HighScoreBoardManager::AddHighScore(const std::string& name, int score)
{
	if (CheckIfHighScore(score))
	{

		m_highScores.push_back(ScoreRecord{ score,name });
		SortHighScores();

		if (m_highScores.size() > m_maxScoresList)
		{
			m_highScores.pop_back(); //erase lowest number
		}
		OutputDebugStringA(("size before save: " + std::to_string(m_highScores.size()) + "\n").c_str());
		SaveFile();
		return true;
	}
	return false;
}

void dae::HighScoreBoardManager::LoadFile(const std::string& filePath)
{
	m_highScores.clear();
	m_highScores.reserve(m_maxScoresList);

	std::ifstream file(m_filePath);
	if (!file.is_open())
	{
		OutputDebugStringA(("Could not open file: " + filePath + "\n").c_str());
	}

	std::string name{};
	int score;

	while (file >> name >> score)
	{
		m_highScores.push_back(ScoreRecord{ score,name });
		OutputDebugStringA((name + std::to_string(score) + "\n").c_str());
	}
	
}

void dae::HighScoreBoardManager::SaveFile()
{
	std::ofstream file(m_filePath);

	for (const auto& scoreRecord : m_highScores)
	{
		file << scoreRecord.name << " " << scoreRecord.score << "\n";
	}
}

void dae::HighScoreBoardManager::SortHighScores()
{
	std::sort(m_highScores.begin(), m_highScores.end(), []
	(const ScoreRecord& highscore1, const ScoreRecord& highScore2)
		{
			return highscore1.score > highScore2.score;
		});
}
