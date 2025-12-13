# Tugas Besar Struktur Data - Aplikasi Pemutar Musik (Konsol)

Aplikasi pemutar musik berbasis konsol yang mendukung dua peran pengguna: **Admin** (mengelola library lagu) dan **User** (mencari lagu, memutar lagu, serta mengelola playlist).  
Proyek ini dibuat untuk menerapkan materi Struktur Data seperti **ADT, pointer, Singly Linked List (SLL), dan Doubly Linked List (DLL)**.

---

## Identitas
- Nama  : SAFWAN HASBI ASFAHANI
- NIM   : 103052300023
- Kelas : DS 47-02
- Nama  : RAFIF SHIDQI APRIANDO
- NIM   : 103052300104
- Kelas : DS 47-02
- Nama  : HAFIZ VAINAKY
- NIM   : 103052300065
- Kelas : DS 47-02
- Mata Kuliah: Struktur Data

---

## Fitur Utama

### Admin
1. Menambah lagu ke library
2. Melihat semua lagu di library
3. Mengubah data lagu di library
4. Menghapus lagu di library  
   - Jika lagu dihapus dari library, lagu juga ikut terhapus dari semua playlist user (sinkronisasi).

### User
1. Mencari lagu di library (ID / judul / artis)
2. Memutar dan menghentikan lagu (play/stop)
3. Membuat playlist
4. Menambahkan lagu ke playlist
5. Menghapus lagu dari playlist
6. Melihat isi playlist
7. Next/Prev lagu:
   - Jika memutar dari playlist: mengikuti urutan lagu di playlist
   - Jika memutar dari library: memutar lagu “mirip” (prioritas artis sama, lalu genre sama, kemudian fallback)

---

## Struktur Data yang Digunakan

1. **ADT Lagu (Record/Struct)**
   - Menyimpan data: id, judul, artis, genre, album, tahun, durasi.

2. **Doubly Linked List (DLL) — Library Lagu**
   - Alasan: mendukung navigasi dua arah (next/prev) pada library.

3. **Singly Linked List (SLL) — Lagu dalam Playlist**
   - Alasan: playlist bersifat linear dan cukup ditelusuri satu arah.

4. **Singly Linked List (SLL) — Daftar Playlist**
   - Menyimpan beberapa playlist berdasarkan nama.

5. **Pointer Sharing (Sinkronisasi)**
   - Node lagu di playlist menyimpan pointer ke node lagu di library.
   - Dampak: update lagu di library otomatis tercermin pada playlist. Jika lagu dihapus, node referensi di playlist ikut dihapus.

---

## Struktur Folder

- `src/` : kode program (C++)
- `docs/` : laporan tahap 1–3 (PDF)
- `screenshots/` : bukti uji coba

---

## Cara Menjalankan (Compile & Run)

### Prasyarat
- Compiler C++ (contoh: MinGW-w64 / g++)

### Compile
Masuk ke folder project, lalu compile dari terminal:

```bash
g++ src/main.cpp src/library.cpp src/playlist.cpp -o Tubes_Strukdat.exe
