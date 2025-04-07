#include "song.hpp"
#include "recommender.hpp"

int main()
{
    std::vector<Song> songs = loadSongs("dataset.csv");

    std::string genre, mood;
    int tempo;

    std::cout << "Enter song genre (Pop/Rock/Ballad/Rap/etc.): ";
    std::getline(std::cin, genre);
    std::cout << "Enter mood (Happy/Sad/Excited/melancholic/etc.): ";
    std::getline(std::cin, mood);
    std::cout << "Enter tempo (0-200): ";
    std::cin >> tempo;

    Song inputSong = {-1, "User Input", "You", genre, mood, tempo};

    auto recommendations = recommendSongs(inputSong, songs);

    std::cout << "\nTop 5 Recommendations:\n";
    for (const auto &s : recommendations)
    {
        std::cout << s.title << " by " << s.artist << " [" << s.genre << ", " << s.mood << ", Tempo: " << s.tempo << "]\n";
    }

    return 0;
}
