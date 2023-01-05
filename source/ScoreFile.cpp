#include "ScoreFile.hpp"

auto ScoreFile::getScores() -> std::vector<std::string>
{
    std::vector<std::string> ret;
    std::fstream file;
    file.open(SCORE_FILE_PATH, std::ios::in);
    std::string temp_string;
    if(!file)
    {
        return ret; // File might not be created yet.
    }
    while(file >> temp_string && ret.size() <= 4)
    {
        // Read the number.
        ret.push_back(temp_string);
    }
    return ret;
}

void ScoreFile::addScore(int score)
{
    std::vector<int> lines;
    std::fstream file;
    file.open(SCORE_FILE_PATH, std::ios::in | std::ios::app);
    int temp_int;

    lines.push_back(score);

    while(file >> temp_int)
    {
        lines.push_back(temp_int);
    }
    file.close();
    if(lines.size() > 0)
    {
        std::sort(lines.begin(), lines.end());
        std::reverse(lines.begin(), lines.end());
    }
    file.open(SCORE_FILE_PATH, std::ios::out | std::ios::trunc);
    for(auto& value : lines)
    {
        file << value << std::endl;
    }
}
