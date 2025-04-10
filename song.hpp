#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

struct Song
{
    int id;
    string title;
    string artist;
    string genre;
    string mood;
    int tempo;

    vector<double> getFeatureVector() const;
};

extern unordered_map<string, int> genreMap;
extern unordered_map<string, int> moodMap;

vector<Song> loadSongs(const string &filename);