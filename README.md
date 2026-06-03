# Balatro-Like Poker Roguelike

Game poker roguelike berbasis terminal (CLI) yang dikembangkan menggunakan bahasa C++ (Pure Object-Oriented Programming). Terinspirasi erat dari mekanik utama game Balatro, di mana pemain membangun mesin skor dinamis melalui kartu acak, serta membelanjakan koin untuk meningkatkan level kombinasi kartu (*hand type*) melalui Toko (*Shop*).

---

## 🚀 Fitur Utama Project

1. **Card & Deck System**:
   * Pengacakan dek standar 52 kartu menggunakan generator acak berbasis waktu.
   * Draw kartu otomatis ke tangan pemain (*Hand State*) dengan kapasitas maksimal 8 kartu.
2. **Data-Driven Scoring System**:
   * Evaluasi kombinasi kartu dinamis menggunakan *Chain of Responsibility Pattern* (Checkers).
   * Perhitungan skor berdasarkan tabel data konfiguratif `HandScoreTable` (chips & mult) ketimbang hardcoding.
   * Objek hasil penilaian yang bersifat immutable (`PlayedHandResult`).
3. **Polymorphic Blind System**:
   * Rintangan musuh berbasis kelas abstrak polimorfis `BlindRule`.
   * Turunan kelas mandiri: `SmallBlind` (target 300), `BigBlind` (target 800), dan `BossBlind` (target 1600), yang berskala secara dinamis mengikuti pengali Ante.
   * `BlindManager` yang mengelola siklus blind aktif pemain.
4. **Round State Management**:
   * Pelacakan sisa giliran bermain (*hands remaining*), sisa pembuangan kartu (*discards remaining*), dan akumulasi skor dalam satu ronde ronde berjalan.
5. **Interactive CLI Loop**:
   * Input teks terintegrasi: pemain dapat memilih kartu berdasarkan indeks (0-7), mengeksekusi aksi bermain/buang, melihat status ronde, dan mengakses Toko untuk membeli upgrade level kombinasi kartu.

---

## 📁 Struktur Folder & Arsitektur

Proyek terbagi secara ketat ke dalam dua domain utama:

```text
src/
├── main.cpp
├── test_main.cpp                   # Rangkaian Tes Unit TDD
│
├── system/                         # DOMAIN SYSTEM (Core Engine)
│   ├── card/                       # Card, Deck, HandState
│   ├── evaluation/                 # PokerHandEvaluator, Checkers
│   ├── blind/                      # BlindRule, Small/Big/BossBlind, BlindManager
│   ├── run/                        # GameManager (CLI Loop), RoundState
│   └── scoring/                    # HandScoreTable, ScoringRule, PlayedHandResult
│
└── mechanic/                       # DOMAIN MECHANIC (Game Feel & Input)
    ├── selection/                  # ChosenHand, SelectionValidator
    └── reward/                     # RewardRule
```

---

## 🧪 Strategi TDD & Pengujian Unit

Kami menerapkan pendekatan **Test-Driven Development (TDD)** untuk menjamin kestabilan dan kebenaran logika bisnis domain secara terisolasi. 

Detail rancangan kasus uji (*test cases*) dan panduan menjalankan rangkaian tes mandiri dapat diakses pada dokumen berikut:
* **📖 [TDD.md - Test Driven Development Document](./TDD.md)**

---

## 🛠️ Cara Mengompilasi dan Menjalankan Game

Pastikan compiler C++ Anda mendukung standar **C++17** atau yang lebih baru.

### Menggunakan GCC / G++ (MinGW/Linux/macOS)
```bash
# Kompilasi kode game utama
g++ -std=c++17 -o balatro.exe src/main.cpp src/system/card/Deck.cpp src/system/card/HandState.cpp src/system/scoring/HandScoreTable.cpp src/system/scoring/ScoringRule.cpp src/system/blind/SmallBlind.cpp src/system/blind/BigBlind.cpp src/system/blind/BossBlind.cpp src/system/blind/BlindManager.cpp src/system/run/RoundState.cpp src/mechanic/selection/ChosenHand.cpp src/mechanic/selection/SelectionValidator.cpp src/system/evaluation/PokerHandEvaluator.cpp src/system/evaluation/PokerHandChecker.cpp src/system/evaluation/checkers/*.cpp

# Jalankan game
./balatro.exe
```

### Menggunakan Compiler MSVC (Developer Command Prompt / Visual Studio)
```cmd
# Kompilasi kode game utama
cl /EHsc /std:c++17 /Fe:balatro.exe src/main.cpp src/system/card/Deck.cpp src/system/card/HandState.cpp src/system/scoring/HandScoreTable.cpp src/system/scoring/ScoringRule.cpp src/system/blind/SmallBlind.cpp src/system/blind/BigBlind.cpp src/system/blind/BossBlind.cpp src/system/blind/BlindManager.cpp src/system/run/RoundState.cpp src/mechanic/selection/ChosenHand.cpp src/mechanic/selection/SelectionValidator.cpp src/system/evaluation/PokerHandEvaluator.cpp src/system/evaluation/PokerHandChecker.cpp src/system/evaluation/checkers/*.cpp

# Jalankan game
balatro.exe
```
