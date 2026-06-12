#pragma once
#include <vector>
#include <string>
namespace dae
{
	struct ScoreRecord
	{
		int score{};
		std::string name{};
	};
	class HighScoreBoardManager final
	{
	public:
		explicit HighScoreBoardManager(const std::string& filePath);
		~HighScoreBoardManager();

		HighScoreBoardManager(const HighScoreBoardManager& other) = delete;
		HighScoreBoardManager(HighScoreBoardManager&& other) = delete;
		HighScoreBoardManager& operator= (const HighScoreBoardManager& other) = delete;
		HighScoreBoardManager& operator= ( HighScoreBoardManager&& other) = delete;

		bool AddHighScore(const std::string& name, int score);
		bool CheckIfHighScore(int score) const;
	private:
		void LoadFile(const std::string& filePath);
		void SaveFile();
		void SortHighScores();

		static constexpr int m_maxScoresList{ 10 };
		std::string m_filePath{};
		std::vector<ScoreRecord> m_highScores{};
	};
}