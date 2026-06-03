# Test-Driven Development (TDD) Document

Dokumen ini menjelaskan strategi pengujian, rancangan kasus uji (Test Cases), dan cara menjalankan rangkaian uji unit (*unit tests*) untuk proyek C++ Balatro-like ini. Rangkaian uji ini dikembangkan secara modular untuk memverifikasi fungsionalitas inti sebelum diintegrasikan ke dalam game loop utama.

---

## 📋 Struktur Pengujian

Kode pengujian utama diimplementasikan pada berkas [src/test_main.cpp](file:///C:/Users/FIsyah/Documents/GitHub/DP-Week3-043-053/src/test_main.cpp). Pengujian ini tidak bergantung pada pustaka eksternal (*dependency-free*) dan menggunakan makro `assert` standar C++ untuk memvalidasi invariants sistem.

Pengujian dibagi menjadi 5 rangkaian kasus uji utama:
1. **Deck & Drawing Verification** (Sistem Kartu)
2. **Hand Selection Validation** (Mekanisme Pemilihan)
3. **Data-Driven Scoring & Upgrades** (Sistem Penilaian Konfiguratif)
4. **Polymorphic Blinds & Scaling** (Sistem Musuh/Rintangan)
5. **Round State Tracking** (Akumulasi Ronde)

---

## 🎯 Spesifikasi Kasus Uji (Test Cases)

### 1. Rangkaian Uji: Deck & Drawing (`testDeckAndDrawing`)
Memastikan pembuatan deck 52 kartu valid dan perilaku menggambar kartu memenuhi batas aman.
* **TC-01-A (Draw Normal):** Mengambil 8 kartu awal dari deck standard.
  * *Ekspektasi:* Mengembalikan persis 8 kartu; sisa kartu di deck berkurang.
* **TC-01-B (Draw Habis):** Mengambil sisa kartu sampai habis.
  * *Ekspektasi:* Kartu terambil sepenuhnya; jumlah total kartu ditarik sama dengan 52.
* **TC-01-C (Draw Deck Kosong):** Menggambar kartu saat deck kosong.
  * *Ekspektasi:* Mengembalikan vector kosong (`empty()`), tidak mengalami crash.

### 2. Rangkaian Uji: Hand Selection (`testHandSelection`)
Memverifikasi fungsionalitas pencatatan indeks pilihan serta validitas batas-batas aturan permainan.
* **TC-02-A (Valid Selection):** Memilih 3 kartu dengan indeks valid.
  * *Ekspektasi:* Validator mengembalikan nilai `true`.
* **TC-02-B (No Duplicate):** Memasukkan indeks kartu yang sama dua kali.
  * *Ekspektasi:* Indeks duplikat diabaikan, ukuran kartu terpilih tetap sama.
* **TC-02-C (Deselection):** Menghapus salah satu kartu yang telah dipilih.
  * *Ekspektasi:* Kartu dihapus dari pilihan, jumlah pilihan berkurang.
* **TC-02-D (Max Selected Cards):** Memilih lebih dari 5 kartu (batas Balatro).
  * *Ekspektasi:* Validator mengembalikan nilai `false` (pilihan tidak valid).
* **TC-02-E (Index Out of Bounds):** Memasukkan indeks $\ge$ jumlah kartu di tangan.
  * *Ekspektasi:* Validator mendeteksi indeks di luar batas dan mengembalikan `false`.

### 3. Rangkaian Uji: Data-Driven Scoring & Upgrades (`testScoringSystem`)
Memastikan data tabel scoring di-load dengan benar dan planet card upgrade bekerja sesuai formula penambahan chip/mult.
* **TC-03-A (Default Values):** Membaca base score dari `HandScoreTable` untuk High Card dan Royal Flush.
  * *Ekspektasi:* High Card = 10 chips / 1 mult. Royal Flush = 100 chips / 8 mult.
* **TC-03-B (Planet Card Upgrade):** Melakukan upgrade level kartu High Card dari level 1 ke level 2.
  * *Ekspektasi:* Level menjadi 2; base chips bertambah 10 (menjadi 20); base mult bertambah 1 (menjadi 2).

### 4. Rangkaian Uji: Polymorphic Blinds (`testPolymorphicBlinds`)
Memastikan perilaku blind bersifat polimorfis, memiliki nama dan target yang tepat berdasarkan Ante.
* **TC-04-A (Small Blind Target):** Menguji `SmallBlind` pada Ante 1.
  * *Ekspektasi:* Nama = "Small Blind", Target Score = 300. Skor 299 mengembalikan `false` (kalah), skor 300 mengembalikan `true` (menang).
* **TC-04-B (Big Blind Target):** Menguji `BigBlind` pada Ante 1.
  * *Ekspektasi:* Nama = "Big Blind", Target Score = 800. Skor 800 mengembalikan `true`.
* **TC-04-C (Boss Blind Target & Ante Scaling):** Menguji `BossBlind` pada Ante 2.
  * *Ekspektasi:* Nama = "Boss Blind", Target Score bertambah sesuai ante ($1600 \times 2 = 3200$). Skor 3200 mengembalikan `true`.

### 5. Rangkaian Uji: Round State (`testRoundState`)
Memverifikasi pelacakan siklus game ronde utama.
* **TC-05-A (Usage tracking):** Mengurangi hands dan discards.
  * *Ekspektasi:* Sisa hands/discards berkurang 1 setiap kali digunakan.
* **TC-05-B (Score Accumulation):** Menambahkan skor dari pemutaran beberapa hands.
  * *Ekspektasi:* Skor ronde terakumulasi secara kumulatif.
* **TC-05-C (Reset):** Mereset ronde.
  * *Ekspektasi:* Semua stats (hands, discards, score) kembali ke nilai awal yang didefinisikan.

---

## 🛠️ Cara Mengompilasi dan Menjalankan Tes

Untuk melakukan pengujian unit secara manual melalui baris perintah (*command line*), Anda dapat mengompilasi berkas tes bersama dengan berkas-berkas sumber domain yang bersangkutan.

### Menggunakan Compiler GCC / G++ (MinGW/Linux/macOS)
```bash
g++ -std=c++17 -o test_runner.exe src/test_main.cpp src/system/card/Deck.cpp src/system/card/HandState.cpp src/system/scoring/HandScoreTable.cpp src/system/scoring/ScoringRule.cpp src/system/blind/SmallBlind.cpp src/system/blind/BigBlind.cpp src/system/blind/BossBlind.cpp src/system/blind/BlindManager.cpp src/system/run/RoundState.cpp src/mechanic/selection/ChosenHand.cpp src/mechanic/selection/SelectionValidator.cpp src/system/evaluation/PokerHandEvaluator.cpp src/system/evaluation/PokerHandChecker.cpp src/system/evaluation/checkers/*.cpp
./test_runner.exe
```

### Menggunakan Compiler MSVC (Developer Command Prompt / Visual Studio)
```cmd
cl /EHsc /std:c++17 /Fe:test_runner.exe src/test_main.cpp src/system/card/Deck.cpp src/system/card/HandState.cpp src/system/scoring/HandScoreTable.cpp src/system/scoring/ScoringRule.cpp src/system/blind/SmallBlind.cpp src/system/blind/BigBlind.cpp src/system/blind/BossBlind.cpp src/system/blind/BlindManager.cpp src/system/run/RoundState.cpp src/mechanic/selection/ChosenHand.cpp src/mechanic/selection/SelectionValidator.cpp src/system/evaluation/PokerHandEvaluator.cpp src/system/evaluation/PokerHandChecker.cpp src/system/evaluation/checkers/*.cpp
test_runner.exe
```

---

## 🔗 Hubungan Dokumen
* Kembali ke [README.md](./README.md)
