## Identitas Kelompok

**Mata Kuliah** : Struktur Data  

1. **Safwan Hasbi Asfahani**  
   NIM   : 103052300023  
   Kelas : DS 47-02  

2. **Rafif Shidqi Apriando**  
   NIM   : 103052300104  
   Kelas : DS 47-02  

3. **Hafiz Vainaky**  
   NIM   : 103052300065  
   Kelas : DS 47-02  

---

## Fitur Utama

### Peran Admin
- Menambahkan lagu ke dalam library
- Melihat seluruh lagu di library
- Mengubah data lagu
- Menghapus lagu dari library
- Sinkronisasi otomatis:
  Lagu yang dihapus dari library juga terhapus dari seluruh playlist User

### Peran User
- Mencari lagu berdasarkan ID, judul, atau artis
- Memutar dan menghentikan lagu (play / stop)
- Membuat playlist
- Menambahkan lagu ke playlist
- Menghapus lagu dari playlist
- Melihat isi playlist
- Navigasi **Next / Prev**:
  - Mode playlist → mengikuti urutan playlist
  - Mode library → memutar lagu mirip (prioritas artis sama, lalu genre sama, kemudian fallback)

---

## Struktur Data yang Digunakan

### 1. ADT Lagu (Struct)
Menyimpan data lagu berupa:
- ID
- Judul
- Artis
- Genre
- Album
- Tahun rilis
- Durasi

### 2. Doubly Linked List (DLL) – Library Lagu
Digunakan sebagai struktur utama penyimpanan lagu pada library.  
Mendukung navigasi dua arah (next / prev) dan mempermudah proses penambahan serta penghapusan data lagu.

### 3. Singly Linked List (SLL) – Playlist
Digunakan untuk menyimpan daftar playlist dan lagu-lagu di dalam playlist.  
Struktur ini dipilih karena bersifat linear dan cukup ditelusuri satu arah.

### 4. Pointer Sharing (Sinkronisasi Data)
Node lagu pada playlist menyimpan pointer ke node lagu di library.  
Dengan pendekatan ini:
- Perubahan data lagu di library otomatis tercermin di playlist
- Lagu yang dihapus dari library ikut terhapus dari playlist

---

## Struktur File Project

Tubes_Strukdat/
├── main.cpp
├── music.h
├── music.cpp
└── README.md


Keterangan:
- `main.cpp` : program utama dan menu aplikasi
- `music.h`  : definisi struktur data dan prototipe fungsi
- `music.cpp`: implementasi fungsi-fungsi aplikasi

---
