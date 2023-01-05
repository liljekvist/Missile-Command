#pragma once
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

class ScoreFile
{
    static constexpr char SCORE_FILE_PATH[] = "scores.txt";

  public:
    static auto getScores() -> std::vector<std::string>; // Reads the file if one exists
    static void addScore(int score); // appends a score to the score file
};
