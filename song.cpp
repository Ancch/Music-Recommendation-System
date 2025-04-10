#include "song.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

unordered_map<string, int> genreMap = {
    {"Pop", 0}, {"Rock", 1}, {"Ballad", 2}, {"Synthpop", 3}, {"Folk", 4}, {"Alternative", 5}, {"Disco", 6}, {"Hip Hop", 7}, {"Rap", 8}};

unordered_map<string, int> moodMap = {
    {"Happy", 0}, {"Sad", 1}, {"Excited", 2}, {"Calm", 3}, {"Angry", 4}, {"Romantic", 5}, {"Nostalgic", 6}, {"Dramatic", 7}, {"Aggresive", 8}, {"chill", 9}, {"Melancholic", 10}, {"Uplifting", 11}};

vector<double> Song::getFeatureVector() const
{
    double genreVal = static_cast<double>(genreMap[genre]);
    double moodVal = static_cast<double>(moodMap[mood]);
    double tempoVal = tempo / 200.0; // normalize (max tempo ~200)

    return {genreVal, moodVal, tempoVal};
}

vector<Song> loadSongs(const string &filename)
{
    vector<Song> songs;
    ifstream file(filename);
    string line;

    getline(file, line); // skip header

    while (getline(file, line))
    {
        stringstream ss(line);
        string item;
        Song s;

        vector<string> fields;
        while (getline(ss, item, ','))
        {
            fields.push_back(item);
        }

        if (fields.size() != 6)
        {
            cerr << "Skipping invalid line: " << line << endl;
            continue;
        }

        try
        {
            s.id = stoi(fields[0]);
            s.title = fields[1];
            s.artist = fields[2];
            s.genre = fields[3];
            s.mood = fields[4];
            s.tempo = stoi(fields[5]);
        }
        catch (const exception &e)
        {
            cerr << "Error parsing line: " << line << "\n"
                 << "Reason: " << e.what() << endl;
            continue;
        }

        songs.push_back(s);
    }

    return songs;
}
