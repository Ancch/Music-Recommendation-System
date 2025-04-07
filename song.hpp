#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>

struct Song
{
    int id;
    std::string title;
    std::string artist;
    std::string genre;
    std::string mood;
    int tempo;

    std::vector<double> getFeatureVector() const;
};

inline std::unordered_map<std::string, int> genreMap = {
    {"Pop", 0}, {"Rock", 1}, {"Ballad", 2}, {"Synthpop", 3}, {"Folk", 4}, {"Alternative", 5}, {"Disco", 6}, {"Hip Hop", 7}, {"Rap", 8}};

inline std::unordered_map<std::string, int> moodMap = {
    {"Happy", 0}, {"Sad", 1}, {"Excited", 2}, {"Calm", 3}, {"Angry", 4}, {"Romantic", 5}, {"Nostalgic", 6}, {"Dramatic", 7}, {"Aggresive", 8}, {"chill", 9}, {"Melancholic", 10}, {"Uplifting", 11}};

inline std::vector<double> Song::getFeatureVector() const
{
    double genreVal = static_cast<double>(genreMap[genre]);
    double moodVal = static_cast<double>(moodMap[mood]);
    double tempoVal = tempo / 200.0; // normalize (max tempo ~200)

    return {genreVal, moodVal, tempoVal};
}

inline std::vector<Song> loadSongs(const std::string &filename)
{
    std::vector<Song> songs;
    std::ifstream file(filename);
    std::string line;

    getline(file, line); // skip header

    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string item;
        Song s;

        std::vector<std::string> fields;
        while (getline(ss, item, ','))
        {
            fields.push_back(item);
        }

        if (fields.size() != 6)
        {
            std::cerr << "Skipping invalid line: " << line << std::endl;
            continue;
        }

        try
        {
            s.id = std::stoi(fields[0]);
            s.title = fields[1];
            s.artist = fields[2];
            s.genre = fields[3];
            s.mood = fields[4];
            s.tempo = std::stoi(fields[5]);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error parsing line: " << line << "\n"
                      << "Reason: " << e.what() << std::endl;
            continue;
        }

        songs.push_back(s);
    }

    return songs;
}
