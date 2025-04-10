#include "song.hpp"
#include "recommender.hpp"
using namespace std;

int main()
{
    vector<Song> songs = loadSongs("dataset.csv");

    string genre, mood;
    int tempo;

    cout << "----------------------------" << endl;
    cout << "MUSIC RECOMMENDATION" << endl;
    cout << "----------------------------" << endl;
    cout << "Enter song genre (Pop/Rock/Ballad/Rap/etc.): ";
    getline(cin, genre);
    cout << "Enter mood (Happy/Sad/Excited/melancholic/etc.): ";
    getline(cin, mood);
    cout << "Enter tempo (0-200): ";
    cin >> tempo;

    Song inputSong = {-1, "User Input", "You", genre, mood, tempo};

    auto recommendations = recommendSongs(inputSong, songs);

    cout << "\nTop 5 Recommendations:\n";
    for (const auto &s : recommendations)
    {
        cout << s.title << " by " << s.artist << " [" << s.genre << ", " << s.mood << ", Tempo: " << s.tempo << "]\n";
    }

    return 0;
}
