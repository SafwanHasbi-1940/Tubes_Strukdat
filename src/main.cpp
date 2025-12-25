#include <iostream>
#include <string>
#include "music.h"
using namespace std;

// STATE PEMUTARAN
adrLagu currentSong = NULL;
adrPlaylist currentPlaylist = NULL;
adrPSong currentPlaylistSong = NULL;
bool isPlaying = false;
bool isPlaylistMode = false;

QueueLagu upNext;

// INPUT
int inputInt(const string &msg) {
    int x;
    cout << msg;
    cin >> x;
    return x;
}

string inputLine(const string &msg) {
    cout << msg;
    string s;
    getline(cin >> ws, s);
    return s;
}

// PEMUTARAN
void printCurrentSong() {
    if (!isPlaying || currentSong == NULL) {
        cout << "Tidak ada lagu yang sedang diputar.\n";
        return;
    }
    cout << "Sedang memutar: " << currentSong->info.judul
         << " - " << currentSong->info.artis
         << " [" << currentSong->info.durasi << "]";
    if (isPlaylistMode && currentPlaylist) {
        cout << " (Playlist: " << currentPlaylist->namaPlaylist << ")";
    } else {
        cout << " (Library)";
    }
    cout << "\n";
}

void stopSong() {
    if (!isPlaying) {
        cout << "Tidak ada lagu yang sedang diputar.\n";
        return;
    }
    cout << "Pemutaran dihentikan.\n";
    isPlaying = false;
    currentSong = NULL;
    currentPlaylist = NULL;
    currentPlaylistSong = NULL;
    isPlaylistMode = false;
}

void playFromLibrary(ListLagu &L) {
    int id = inputInt("Masukkan ID lagu yang ingin diputar: ");
    adrLagu p = findLaguById(L, id);
    if (p == NULL) {
        cout << "Lagu tidak ditemukan.\n";
        return;
    }
    currentSong = p;
    isPlaying = true;
    isPlaylistMode = false;
    currentPlaylist = NULL;
    currentPlaylistSong = NULL;
    printCurrentSong();
}

void playFromPlaylist(ListPlaylist &LP) {
    string nama = inputLine("Masukkan nama playlist: ");
    adrPlaylist PL = findPlaylistByName(LP, nama);
    if (PL == NULL) {
        cout << "Playlist tidak ditemukan.\n";
        return;
    }
    if (PL->headSong == NULL) {
        cout << "Playlist kosong.\n";
        return;
    }
    int id = inputInt("Masukkan ID lagu dalam playlist yang ingin diputar: ");
    adrPSong S = PL->headSong;
    while (S != NULL && S->lagu->info.id != id) S = S->next;

    if (S == NULL) {
        cout << "Lagu dengan ID tersebut tidak ada di playlist.\n";
        return;
    }
    currentSong = S->lagu;
    currentPlaylistSong = S;
    currentPlaylist = PL;
    isPlaying = true;
    isPlaylistMode = true;
    printCurrentSong();
}

// definisi “mirip”: artis sama > genre sama > fallback urutan biasa
adrLagu findSimilarNextInLibrary(ListLagu &L, adrLagu base) {
    if (base == NULL) return NULL;

    string artis = base->info.artis;
    string genre = base->info.genre;

    adrLagu p = base->next;
    while (p != NULL) { if (p->info.artis == artis) return p; p = p->next; }

    p = L.first;
    while (p != NULL && p != base) { if (p->info.artis == artis) return p; p = p->next; }

    p = base->next;
    while (p != NULL) { if (p->info.genre == genre) return p; p = p->next; }

    p = L.first;
    while (p != NULL && p != base) { if (p->info.genre == genre) return p; p = p->next; }

    if (base->next != NULL) return base->next;
    if (L.first != base) return L.first;
    return NULL;
}

adrLagu findSimilarPrevInLibrary(ListLagu &L, adrLagu base) {
    if (base == NULL) return NULL;

    string artis = base->info.artis;
    string genre = base->info.genre;

    adrLagu p = base->prev;
    while (p != NULL) { if (p->info.artis == artis) return p; p = p->prev; }

    p = L.last;
    while (p != NULL && p != base) { if (p->info.artis == artis) return p; p = p->prev; }

    p = base->prev;
    while (p != NULL) { if (p->info.genre == genre) return p; p = p->prev; }

    p = L.last;
    while (p != NULL && p != base) { if (p->info.genre == genre) return p; p = p->prev; }

    if (base->prev != NULL) return base->prev;
    if (L.last != base) return L.last;
    return NULL;
}

adrPSong findPrevSongInPlaylist(adrPlaylist PL, adrPSong node) {
    if (PL == NULL || PL->headSong == NULL || PL->headSong == node) return NULL;
    adrPSong p = PL->headSong;
    while (p->next != NULL && p->next != node) p = p->next;
    if (p->next == node) return p;
    return NULL;
}

void nextSong(ListLagu &L) {
    if (!isPlaying || currentSong == NULL) {
        cout << "Tidak ada lagu yang sedang diputar.\n";
        return;
    }
    if (isPlaylistMode && currentPlaylist != NULL) {
        if (currentPlaylistSong == NULL || currentPlaylistSong->next == NULL) {
            cout << "Tidak ada lagu selanjutnya di playlist.\n";
            return;
        }
        currentPlaylistSong = currentPlaylistSong->next;
        currentSong = currentPlaylistSong->lagu;
        printCurrentSong();
    } else {
        adrLagu nx = findSimilarNextInLibrary(L, currentSong);
        if (nx == NULL) { cout << "Tidak ada lagu berikutnya.\n"; return; }
        currentSong = nx;
        isPlaylistMode = false;
        currentPlaylist = NULL;
        currentPlaylistSong = NULL;
        printCurrentSong();
    }
}

void prevSong(ListLagu &L) {
    if (!isPlaying || currentSong == NULL) {
        cout << "Tidak ada lagu yang sedang diputar.\n";
        return;
    }
    if (isPlaylistMode && currentPlaylist != NULL) {
        adrPSong pv = findPrevSongInPlaylist(currentPlaylist, currentPlaylistSong);
        if (pv == NULL) { cout << "Tidak ada lagu sebelumnya di playlist.\n"; return; }
        currentPlaylistSong = pv;
        currentSong = currentPlaylistSong->lagu;
        printCurrentSong();
    } else {
        adrLagu pv = findSimilarPrevInLibrary(L, currentSong);
        if (pv == NULL) { cout << "Tidak ada lagu sebelumnya.\n"; return; }
        currentSong = pv;
        isPlaylistMode = false;
        currentPlaylist = NULL;
        currentPlaylistSong = NULL;
        printCurrentSong();
    }
}

// SEARCH
void searchSong(const ListLagu &L) {
    if (listLaguKosong(L)) {
        cout << "Library kosong.\n";
        return;
    }
    cout << "\nCari lagu berdasarkan:\n";
    cout << "1. ID\n";
    cout << "2. Judul (substring)\n";
    cout << "3. Artis (substring)\n";
    int pil = inputInt("Pilih: ");

    if (pil == 1) {
        int id = inputInt("Masukkan ID: ");
        adrLagu p = findLaguById(L, id);
        if (p == NULL) cout << "Lagu tidak ditemukan.\n";
        else cout << "Ditemukan: " << p->info.judul << " - " << p->info.artis << "\n";
    } else {
        string key = inputLine("Masukkan kata kunci: ");
        bool found = false;
        adrLagu p = L.first;
        while (p != NULL) {
            if ((pil == 2 && p->info.judul.find(key) != string::npos) ||
                (pil == 3 && p->info.artis.find(key) != string::npos)) {
                if (!found) cout << "Hasil:\n";
                found = true;
                cout << "ID " << p->info.id << " : "
                     << p->info.judul << " - " << p->info.artis << "\n";
            }
            p = p->next;
        }
        if (!found) cout << "Tidak ada lagu yang cocok.\n";
    }
}

// MENU 
void menuAdmin(ListLagu &L, ListPlaylist &LP) {
    int pil;
    do {
        cout << "\n===== MENU ADMIN =====\n";
        cout << "1. Tambah Lagu\n";
        cout << "2. Lihat Semua Lagu\n";
        cout << "3. Ubah Data Lagu\n";
        cout << "4. Hapus Lagu\n";
        cout << "0. Kembali\n";
        pil = inputInt("Pilih: ");

        if (pil == 1) {
            Lagu x;
            x.id     = inputInt("ID Lagu        : ");
            x.judul  = inputLine("Judul          : ");
            x.artis  = inputLine("Artis          : ");
            x.genre  = inputLine("Genre          : ");
            x.album  = inputLine("Album          : ");
            x.tahun  = inputInt("Tahun Rilis    : ");
            x.durasi = inputLine("Durasi (mm:ss) : ");

            if (findLaguById(L, x.id) != NULL) {
                cout << "ID sudah digunakan.\n";
            } else {
                adrLagu p = alokasiLagu(x);
                insertLaguLast(L, p);
                cout << "Lagu berhasil ditambahkan.\n";
            }
        } else if (pil == 2) {
            viewLagu(L);
        } else if (pil == 3) {
            int id = inputInt("Masukkan ID lagu yang akan diubah: ");
            adrLagu p = findLaguById(L, id);
            if (p == NULL) cout << "Lagu tidak ditemukan.\n";
            else updateDataLagu(p);
        } else if (pil == 4) {
            int id = inputInt("Masukkan ID lagu yang akan dihapus: ");
            adrLagu p = findLaguById(L, id);
            if (p == NULL) {
                cout << "Lagu tidak ditemukan.\n";
            } else {
                if (currentSong == p) {
                    cout << "Lagu sedang diputar, pemutaran dihentikan.\n";
                    stopSong();
                }
                removeSongFromAllPlaylists(LP, p);
                removeSongFromQueue(upNext, p);
                deleteNodeLagu(L, p);
                cout << "Lagu dihapus dari library, playlist, dan antrian.\n";
            }
        }
    } while (pil != 0);
}

void menuUser(ListLagu &L, ListPlaylist &LP) {
    int pil;
    do {
        cout << "\n===== MENU USER =====\n";
        cout << "1. Cari Lagu di Library\n";
        cout << "2. Lihat Semua Lagu di Library\n";
        cout << "3. Putar Lagu dari Library\n";
        cout << "4. Buat Playlist Baru\n";
        cout << "5. Lihat Semua Playlist\n";
        cout << "6. Lihat Lagu dalam Playlist\n";
        cout << "7. Tambah Lagu ke Playlist\n";
        cout << "8. Hapus Lagu dari Playlist\n";
        cout << "9. Putar Lagu dari Playlist\n";
        cout << "10. Next Lagu\n";
        cout << "11. Prev Lagu\n";
        cout << "12. Lihat Lagu Sedang Diputar\n";
        cout << "13. Stop Lagu\n";
        cout << "14. Tambah Lagu ke Up Next\n";
        cout << "15. Putar Lagu dari Up Next\n";
        cout << "16. Lihat Up Next\n";
        cout << "0. Kembali\n";
        pil = inputInt("Pilih: ");

        if (pil == 1) searchSong(L);
        else if (pil == 2) viewLagu(L);
        else if (pil == 3) playFromLibrary(L);
        else if (pil == 4) {
            string nama = inputLine("Nama playlist baru: ");
            if (findPlaylistByName(LP, nama) != NULL) cout << "Playlist sudah ada.\n";
            else {
                adrPlaylist P = alokasiPlaylist(nama);
                insertPlaylistLast(LP, P);
                cout << "Playlist berhasil dibuat.\n";
            }
        } else if (pil == 5) viewAllPlaylists(LP);
        else if (pil == 6) {
            string nama = inputLine("Nama playlist: ");
            adrPlaylist P = findPlaylistByName(LP, nama);
            if (P == NULL) cout << "Playlist tidak ditemukan.\n";
            else viewSongsInPlaylist(P);
        } else if (pil == 7) {
            string nama = inputLine("Nama playlist: ");
            adrPlaylist P = findPlaylistByName(LP, nama);
            if (P == NULL) cout << "Playlist tidak ditemukan.\n";
            else {
                int id = inputInt("ID lagu yang akan ditambahkan: ");
                adrLagu song = findLaguById(L, id);
                if (song == NULL) cout << "Lagu tidak ada di library.\n";
                else addSongToPlaylist(P, song);
            }
        } else if (pil == 8) {
            string nama = inputLine("Nama playlist: ");
            adrPlaylist P = findPlaylistByName(LP, nama);
            if (P == NULL) cout << "Playlist tidak ditemukan.\n";
            else {
                int id = inputInt("ID lagu yang akan dihapus dari playlist: ");
                if (removeSongFromPlaylist(P, id)) cout << "Lagu dihapus dari playlist.\n";
                else cout << "Lagu tidak ditemukan di playlist.\n";
            }
        } else if (pil == 9) {
            playFromPlaylist(LP);
        } else if (pil == 10) {
            nextSong(L);
        } else if (pil == 11) {
            prevSong(L);
        } else if (pil == 12) {
            printCurrentSong();
        } else if (pil == 13) {
            stopSong();
        } else if (pil == 14) {
            int id = inputInt("ID lagu untuk dimasukkan Up Next: ");
            adrLagu song = findLaguById(L, id);
            if (song == NULL) cout << "Lagu tidak ditemukan.\n";
            else { enqueue(upNext, song); cout << "Masuk antrian.\n"; }
        } else if (pil == 15) {
            adrLagu song = dequeue(upNext);
            if (song == NULL) cout << "Antrian kosong.\n";
            else {
                currentSong = song;
                isPlaying = true;
                isPlaylistMode = false;
                currentPlaylist = NULL;
                currentPlaylistSong = NULL;
                printCurrentSong();
            }
        } else if (pil == 16) {
            viewQueue(upNext);
        }
    } while (pil != 0);
}

int main() {
    ListLagu library;
    ListPlaylist playlists;

    createListLagu(library);
    createListPlaylist(playlists);
    createQueue(upNext);

    int pilih;
    do {
        cout << "\n===== APLIKASI PEMUTAR MUSIK (KONSOL) =====\n";
        cout << "1. Masuk sebagai Admin\n";
        cout << "2. Masuk sebagai User\n";
        cout << "0. Keluar\n";
        pilih = inputInt("Pilih: ");

        if (pilih == 1) menuAdmin(library, playlists);
        else if (pilih == 2) menuUser(library, playlists);

    } while (pilih != 0);

    cout << "Terima kasih.\n";
    return 0;
}

