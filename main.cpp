#include <iostream>
#include <string.h>
using namespace std;

class Song {
private:
    char *songName;
    char *artist;
    float rating;
    int time;

    void copy_song (const Song &other) {
        this->songName = new char [::strlen(other.songName) + 1];
        ::strcpy(this->songName, other.songName);
        this->artist = new char [strlen(other.artist) + 1];
        ::strcpy(this->artist, other.artist);
        this->rating = other.rating;
        this->time = other.time;
    }
public:
    Song(char *songName = "", char *artist = "", float rating = 0.0, int time = 0) {
        this->songName = new char [::strlen(songName) + 1];
        ::strcpy(this->songName, songName);
        this->artist = new char [strlen(artist) + 1];
        ::strcpy(this->artist, artist);
        this->rating = rating;
        this->time = time;
    }

    Song(const Song &other) {
        copy_song(other);
    }

    Song &operator= (const Song &other) {
        if (this == &other) { return *this; }
        delete [] songName;
        delete [] artist;
        copy_song(other);
        return *this;
    }

    ~Song() { delete [] songName; delete [] artist; }

    char *getSongName() const {
        return songName;
    }

    void setSongName(char *ssongName) {
        Song::songName = ssongName;
    }

    char *getArtist() const {
        return artist;
    }

    void setArtist(char *aartist) {
        Song::artist = aartist;
    }

    float getRating() const {
        return rating;
    }

    void setRating(float rrating) {
        Song::rating = rrating;
    }

    int getTime() const {
        return time;
    }

    void setTime(int ttime) {
        Song::time = ttime;
    }

    friend ostream &operator<<(ostream &os, const Song &song) {
        os << song.songName << " " << song.artist << " " << song.time << " " << song.rating << endl;
        return os;
    }

    bool operator==(const Song &rhs) const {
        return songName == rhs.songName &&
               artist == rhs.artist &&
               rating == rhs.rating &&
               time == rhs.time;
    }

    bool operator< (Song &other) {
        return time < other.time;
    }
};

class Playlist {
private:
    char *playlistName;
    int n;
    Song *songs;

    void copy_playlist(const Playlist &other) {
        this->playlistName = new char [::strlen(other.playlistName) + 1];
        strcpy(this->playlistName, other.playlistName);
        this->n = other.n;
        this->songs = new Song[other.n];
        for (int i = 0; i < other.n; ++i) {
            this->songs[i] = other.songs[i];
        }
    }
public:
    Playlist(char *playlistName = "", int n = 0, Song *songs = nullptr) {
        this->playlistName = new char [::strlen(playlistName) + 1];
        strcpy(this->playlistName, playlistName);
        this->n = n;
        this->songs = new Song[n];
        for (int i = 0; i < n; ++i) {
            this->songs[i] = songs[i];
        }
    }

    Playlist(const Playlist &other) {
        copy_playlist(other);
    }

    Playlist &operator= (const Playlist &other) {
        if (this == &other) { return *this; }
        delete [] playlistName;
        delete [] songs;
        copy_playlist(other);
        return *this;
    }

    ~Playlist() { delete [] playlistName; delete [] songs; }

    char *getPlaylistName() const {
        return playlistName;
    }

    void setPlaylistName(char *pplaylistName) {
        Playlist::playlistName = pplaylistName;
    }

    int getN() const {
        return n;
    }

    void setN(int nn) {
        Playlist::n = nn;
    }

    Song *getSongs() const {
        return songs;
    }

    void setSongs(Song *ssongs) {
        Playlist::songs = ssongs;
    }

    Playlist &operator+= (Song song) {
        Song *tmp = new Song [n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = songs[i];
        }
        tmp[n++] = song;
        delete [] songs;

        songs = new Song[n];
        for (int i = 0; i < n; ++i) {
            songs[i] = tmp[i];
        }
        delete [] tmp;

        return *this;
    }

    Playlist &operator-= (Song song) {
        int counter = 0;
        Song *tmp = new Song [n - 1];

        for (int i = 0; i < n; ++i) {
            tmp[counter++] = songs[i];
        }
        delete [] songs;
        songs = new Song[counter];
        for (int i = 0; i < counter; ++i) {
            songs[i] = tmp[i];
        }
        n--;
        delete [] tmp;

        return *this;
    }

    friend ostream &operator<<(ostream &os, const Playlist &playlist) {
        os << playlist.playlistName << endl;
        for (int i = 0; i < playlist.n; ++i) {
            cout << playlist.songs[i];
        }
        return os;
    }

    void sortSongs() {
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1 ; ++j) {
                if (songs[j].getTime() < songs[j + 1].getTime()) {
                    Song tmp = songs[j];
                    songs[j] = songs[j + 1];
                    songs[j + 1] = tmp;
                }
            }
        }
    }
};

int main() {
    int testCase;

    cin>>testCase;

    if(testCase==1){
        cout<<"TESTING SONG CLASS CONSTRUCTORS"<<endl;

        Song song = Song("Cornfield Chase", "Hans Zimmer" , 4.9,126);

        cout<<song;

        cout<<"TESTING SONG CLASS OPERATORS"<<endl;

        Song song1 = Song("Cornfield Chase", "Hans Zimmer" ,4.9 ,126 );
        if(song==song1){
            cout<<song;
        }
        else{
            cout<<"Ne se isti pesnite";
        }
    }
    else if(testCase==2){
        cout<<"TESTING SONG CLASS CONSTRUCTORS"<<endl;

        Song song = Song("Cornfield Chase", "Hans Zimmer" , 4.9, 126);

        cout<<song;

        cout<<"TESTING SONG CLASS OPERATORS"<<endl;

        Song song1 = Song("Cornfield Chase", "Hans Zimmer" , 4.9, 128);
        if(song==song1){
            cout<<song;
        }
        else{
            cout<<"Ne se isti pesnite";
        }
    }
    else if(testCase==3){
        Playlist playlist("MyPlaylist");
        int n;
        cin>>n;

        for (int i=0;i<n;i++)
        {
            char name[100];
            char artist[100];
            float rating;
            int duration;

            cin >> name;
            cin >> artist;
            cin >> rating;
            cin >> duration;

            Song s=Song(name, artist, rating, duration);

            //dodavanje na pesna
            playlist+=s;

        }

        cout<<"TESTING PLAYLIST OPERATOR +="<<endl;

        cout<<playlist;
    }
    else if(testCase==4){
        Playlist playlist("RapPlaylist");
        int n;
        cin>>n;

        for (int i=0;i<n;i++)
        {
            char name[100];
            char artist[100];
            float rating;
            int duration;

            cin >> name;
            cin >> artist;
            cin >> rating;
            cin >> duration;

            Song s=Song(name, artist, rating, duration);

            //dodavanje na pesna
            playlist+=s;

        }

        cout<<"TESTING PLAYLIST OPERATOR -="<<endl;

        char name[100];
        char artist[100];
        float rating;
        int duration;

        cin >> name;
        cin >> artist;
        cin >> rating;
        cin >> duration;

        Song s=Song(name, artist, rating, duration);

        //brishenje na pesna
        playlist-=s;

        cout<<playlist;
    }
    else if(testCase==5){
        Playlist playlist("PopPlaylist");
        int n;
        cin>>n;

        for (int i=0;i<n;i++)
        {
            char name[100];
            char artist[100];
            float rating;
            int duration;

            cin >> name;
            cin >> artist;
            cin >> rating;
            cin >> duration;

            Song s=Song(name, artist, rating, duration);

            //dodavanje na pesna
            playlist+=s;

        }

        cout<<"TESTING SORT METHOD"<<endl;

        playlist.sortSongs();
        cout<<playlist;
    }


    return 0;
}