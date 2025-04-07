#pragma once
#include "song.hpp"
#include <algorithm>

inline double cosineSimilarity(const std::vector<double> &a, const std::vector<double> &b)
{
    double dot = 0.0, normA = 0.0, normB = 0.0;
    for (size_t i = 0; i < a.size(); ++i)
    {
        dot += a[i] * b[i];
        normA += a[i] * a[i];
        normB += b[i] * b[i];
    }
    return dot / (sqrt(normA) * sqrt(normB) + 1e-10);
}

inline std::vector<Song> recommendSongs(const Song &input, const std::vector<Song> &allSongs, int topN = 5)
{
    std::vector<std::pair<double, Song>> scored;

    auto inputVec = input.getFeatureVector();

    for (const auto &song : allSongs)
    {
        double score = cosineSimilarity(inputVec, song.getFeatureVector());
        scored.push_back({score, song});
    }

    std::sort(scored.begin(), scored.end(), [](const auto &a, const auto &b)
              { return a.first > b.first; });

    std::vector<Song> result;
    for (int i = 0; i < std::min(topN, (int)scored.size()); ++i)
    {
        result.push_back(scored[i].second);
    }

    return result;
}
