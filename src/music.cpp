#include "music.h"
#include <iostream>
using namespace std;

// DLL Library
void createListLagu(ListLagu &L) {
    L.first = NULL;
    L.last  = NULL;
}

bool listLaguKosong(const ListLagu &L) {
    return (L.first == NULL);
}

adrLagu alokasiLagu(const Lagu &x) {
    adrLagu p = new elmLagu;
    p->info = x;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

void dealokasiLagu(adrLagu &p) {
    delete p;
    p = NULL;
}

void insertLaguLast(ListLagu &L, adrLagu p) {
    if (listLaguKosong(L)) {
        L.first = L.last = p;
    } else {
        p->prev = L.last;
        L.last->next = p;
        L.last = p;
    }
}

adrLagu findLaguById(const ListLagu &L, int id) {
    adrLagu p = L.first;
    while (p != NULL && p->info.id != id) {
        p = p->next;
    }
    return p;
}

void viewLagu(const ListLagu &L) {
    if (listLaguKosong(L)) {
        cout << "Library kosong.\n";
        return;
    }
    cout << "===== DAFTAR LAGU DI LIBRARY =====\n";
    adrLagu p = L.first;
    while (p != NULL) {
        cout << "ID      : " << p->info.id << "\n";
        cout << "Judul   : " << p->info.judul << "\n";
        cout << "Artis   : " << p->info.artis << "\n";
        cout << "Genre   : " << p->info.genre << "\n";
        cout << "Album   : " << p->info.album << "\n";
        cout << "Tahun   : " << p->info.tahun << "\n";
        cout << "Durasi  : " << p->info.durasi << "\n";
        cout << "---------------------------\n";
        p = p->next;
    }
}

void deleteNodeLagu(ListLagu &L, adrLagu &p) {
    if (p == NULL) return;

    if (p == L.first && p == L.last) {
        L.first = L.last = NULL;
    } else if (p == L.first) {
        L.first = p->next;
        if (L.first) L.first->prev = NULL;
    } else if (p == L.last) {
        L.last = p->prev;
        if (L.last) L.last->next = NULL;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }

    dealokasiLagu(p);
}

void updateDataLagu(adrLagu p) {
    if (p == NULL) return;

    // buang newline sisa dari input sebelumnya (cin >>)
    cin.ignore(10000, '\n');

    cout << "Update data lagu ID " << p->info.id << "\n";

    string temp;

    cout << "Judul  (" << p->info.judul  << ") : ";
    getline(cin, temp);
    if (temp != "") p->info.judul = temp;

    cout << "Artis  (" << p->info.artis  << ") : ";
    getline(cin, temp);
    if (temp != "") p->info.artis = temp;

    cout << "Genre  (" << p->info.genre  << ") : ";
    getline(cin, temp);
    if (temp != "") p->info.genre = temp;

    cout << "Album  (" << p->info.album  << ") : ";
    getline(cin, temp);
    if (temp != "") p->info.album = temp;

    cout << "Tahun  (" << p->info.tahun  << ") : ";
    getline(cin, temp);
    if (temp != "") {
        bool ok = true;
        for (int i = 0; i < (int)temp.length(); i++) {
            if (temp[i] < '0' || temp[i] > '9') { ok = false; break; }
        }
        if (ok) p->info.tahun = stoi(temp);
        else cout << "Input tahun tidak valid, tahun tidak diubah.\n";
    }

    cout << "Durasi (" << p->info.durasi << ") : ";
    getline(cin, temp);
    if (temp != "") p->info.durasi = temp;

    cout << "Data lagu berhasil diupdate.\n";
}

// Playlist list
void createListPlaylist(ListPlaylist &LP) {
    LP.first = NULL;
}

adrPlaylist alokasiPlaylist(const string &nama) {
    adrPlaylist P = new elmPlaylist;
    P->namaPlaylist = nama;
    P->headSong = NULL;
    P->next = NULL;
    return P;
}

void insertPlaylistLast(ListPlaylist &LP, adrPlaylist P) {
    if (LP.first == NULL) {
        LP.first = P;
    } else {
        adrPlaylist Q = LP.first;
        while (Q->next != NULL) Q = Q->next;
        Q->next = P;
    }
}

adrPlaylist findPlaylistByName(const ListPlaylist &LP, const string &nama) {
    adrPlaylist P = LP.first;
    while (P != NULL && P->namaPlaylist != nama) P = P->next;
    return P;
}

void viewAllPlaylists(const ListPlaylist &LP) {
    if (LP.first == NULL) {
        cout << "Belum ada playlist.\n";
        return;
    }
    cout << "===== DAFTAR PLAYLIST =====\n";
    adrPlaylist P = LP.first;
    while (P != NULL) {
        cout << "- " << P->namaPlaylist << "\n";
        P = P->next;
    }
}

// Lagu dalam playlist
bool isSongInPlaylist(adrPlaylist PL, adrLagu lagu) {
    adrPSong S = PL->headSong;
    while (S != NULL) {
        if (S->lagu == lagu) return true;
        S = S->next;
    }
    return false;
}

void addSongToPlaylist(adrPlaylist PL, adrLagu lagu) {
    if (PL == NULL || lagu == NULL) return;

    if (isSongInPlaylist(PL, lagu)) {
        cout << "Lagu sudah ada di playlist.\n";
        return;
    }

    adrPSong S = new elmPlaylistSong;
    S->lagu = lagu;
    S->next = NULL;

    if (PL->headSong == NULL) {
        PL->headSong = S;
    } else {
        adrPSong Q = PL->headSong;
        while (Q->next != NULL) Q = Q->next;
        Q->next = S;
    }
    cout << "Lagu berhasil ditambahkan ke playlist.\n";
}

bool removeSongFromPlaylist(adrPlaylist PL, int idLagu) {
    if (PL == NULL || PL->headSong == NULL) return false;

    adrPSong S = PL->headSong;
    adrPSong prev = NULL;

    while (S != NULL && S->lagu->info.id != idLagu) {
        prev = S;
        S = S->next;
    }
    if (S == NULL) return false;

    if (prev == NULL) PL->headSong = S->next;
    else prev->next = S->next;

    delete S;
    return true;
}

void viewSongsInPlaylist(adrPlaylist PL) {
    if (PL == NULL) {
        cout << "Playlist tidak ditemukan.\n";
        return;
    }
    cout << "===== LAGU DI PLAYLIST \"" << PL->namaPlaylist << "\" =====\n";
    if (PL->headSong == NULL) {
        cout << "(kosong)\n";
        return;
    }
    adrPSong S = PL->headSong;
    int i = 1;
    while (S != NULL) {
        cout << i << ". " << S->lagu->info.judul
             << " - " << S->lagu->info.artis << "\n";
        S = S->next;
        i++;
    }
}

void removeSongFromAllPlaylists(ListPlaylist &LP, adrLagu target) {
    adrPlaylist PL = LP.first;
    while (PL != NULL) {
        adrPSong S = PL->headSong;
        adrPSong prev = NULL;
        while (S != NULL) {
            if (S->lagu == target) {
                adrPSong del = S;
                if (prev == NULL) {
                    PL->headSong = S->next;
                    S = PL->headSong;
                } else {
                    prev->next = S->next;
                    S = prev->next;
                }
                delete del;
            } else {
                prev = S;
                S = S->next;
            }
        }
        PL = PL->next;
    }
}

// Queue Up Next

void createQueue(QueueLagu &Q) {
    Q.front = Q.rear = NULL;
}

bool isQueueEmpty(const QueueLagu &Q) {
    return (Q.front == NULL);
}

void enqueue(QueueLagu &Q, adrLagu lagu) {
    if (lagu == NULL) return;

    QNode *p = new QNode;
    p->lagu = lagu;
    p->next = NULL;

    if (isQueueEmpty(Q)) {
        Q.front = Q.rear = p;
    } else {
        Q.rear->next = p;
        Q.rear = p;
    }
}

adrLagu dequeue(QueueLagu &Q) {
    if (isQueueEmpty(Q)) return NULL;

    QNode *p = Q.front;
    adrLagu out = p->lagu;

    Q.front = Q.front->next;
    if (Q.front == NULL) Q.rear = NULL;

    delete p;
    return out;
}

void viewQueue(const QueueLagu &Q) {
    cout << "===== UP NEXT =====\n";
    if (isQueueEmpty(Q)) {
        cout << "(kosong)\n";
        return;
    }
    QNode *p = Q.front;
    int i = 1;
    while (p != NULL) {
        cout << i++ << ". " << p->lagu->info.judul
             << " - " << p->lagu->info.artis << "\n";
        p = p->next;
    }
}

void removeSongFromQueue(QueueLagu &Q, adrLagu target) {
    if (target == NULL) return;

    QNode *p = Q.front;
    QNode *prev = NULL;

    while (p != NULL) {
        if (p->lagu == target) {
            QNode *del = p;

            if (prev == NULL) Q.front = p->next;
            else prev->next = p->next;

            if (del == Q.rear) Q.rear = prev;

            p = (prev == NULL) ? Q.front : prev->next;
            delete del;
        } else {
            prev = p;
            p = p->next;
        }
    }
}

