#ifndef MUSIC_H
#define MUSIC_H

#include <string>
using namespace std;

// ADT LAGU (DLL)

struct Lagu {
    int id;
    string judul;
    string artis;
    string genre;
    string album;
    int tahun;
    string durasi;
};

typedef struct elmLagu *adrLagu;
struct elmLagu {
    Lagu info;
    adrLagu next;
    adrLagu prev;
};

struct ListLagu {
    adrLagu first;
    adrLagu last;
};

// Primitif DLL Library
void createListLagu(ListLagu &L);
bool listLaguKosong(const ListLagu &L);
adrLagu alokasiLagu(const Lagu &x);
void dealokasiLagu(adrLagu &p);
void insertLaguLast(ListLagu &L, adrLagu p);
adrLagu findLaguById(const ListLagu &L, int id);
void viewLagu(const ListLagu &L);
void deleteNodeLagu(ListLagu &L, adrLagu &p);
void updateDataLagu(adrLagu p);

// PLAYLIST (SLL lagu + list playlist)

typedef struct elmPlaylistSong *adrPSong;
struct elmPlaylistSong {
    adrLagu lagu;        // pointer ke node DLL library
    adrPSong next;
};

typedef struct elmPlaylist *adrPlaylist;
struct elmPlaylist {
    string namaPlaylist;
    adrPSong headSong;
    adrPlaylist next;
};

struct ListPlaylist {
    adrPlaylist first;
};

// Primitif ListPlaylist
void createListPlaylist(ListPlaylist &LP);
adrPlaylist alokasiPlaylist(const string &nama);
void insertPlaylistLast(ListPlaylist &LP, adrPlaylist P);
adrPlaylist findPlaylistByName(const ListPlaylist &LP, const string &nama);
void viewAllPlaylists(const ListPlaylist &LP);

// Primitif lagu dalam playlist
bool isSongInPlaylist(adrPlaylist PL, adrLagu lagu);
void addSongToPlaylist(adrPlaylist PL, adrLagu lagu);
bool removeSongFromPlaylist(adrPlaylist PL, int idLagu);
void viewSongsInPlaylist(adrPlaylist PL);

// Sinkronisasi hapus lagu dari semua playlist
void removeSongFromAllPlaylists(ListPlaylist &LP, adrLagu target);

// QUEUE (Up Next) FIFO

struct QNode {
    adrLagu lagu;
    QNode *next;
};

struct QueueLagu {
    QNode *front;
    QNode *rear;
};

void createQueue(QueueLagu &Q);
bool isQueueEmpty(const QueueLagu &Q);
void enqueue(QueueLagu &Q, adrLagu lagu);
adrLagu dequeue(QueueLagu &Q);
void viewQueue(const QueueLagu &Q);
void removeSongFromQueue(QueueLagu &Q, adrLagu target);

#endif

