#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

class Buku {
public:
    Buku(const string& judul, const string& penulis, int tahunTerbit, int jumlahTotal)
        : judul(judul), penulis(penulis), tahunTerbit(tahunTerbit), jumlahTotal(jumlahTotal), jumlahTersedia(jumlahTotal) {}

    const string& dapatkanJudul() const {
        return judul;
    }

    const string& dapatkanPenulis() const {
        return penulis;
    }

    int dapatkanTahunTerbit() const {
        return tahunTerbit;
    }

    int dapatkanJumlahTotal() const {
        return jumlahTotal;
    }

    int dapatkanJumlahTersedia() const {
        return jumlahTersedia;
    }

    void aturJumlahTersedia(int jumlah) {
        jumlahTersedia = jumlah;
    }

private:
    string judul;
    string penulis;
    int tahunTerbit;
    int jumlahTotal;
    int jumlahTersedia;
};

class Perpustakaan {
public:
    void tambahBuku(const Buku& buku) {
        for (auto& existingBuku : daftarBuku) {
            if (existingBuku.dapatkanJudul() == buku.dapatkanJudul()) {
                existingBuku.aturJumlahTersedia(existingBuku.dapatkanJumlahTersedia() + buku.dapatkanJumlahTersedia());
                cout << "Jumlah buku '" << buku.dapatkanJudul() << "' berhasil diperbarui.\n";
                return;
            }
        }

        daftarBuku.push_back(buku);
        cout << "Buku '" << buku.dapatkanJudul() << "' berhasil ditambahkan.\n";
    }

    void tampilkanDaftarBuku() const {
        cout << "Daftar Buku Tersedia:\n";
        for (const auto& buku : daftarBuku) {
            cout << "- Judul: " << buku.dapatkanJudul() << ", Penulis: " << buku.dapatkanPenulis()
                 << ", Tahun Terbit: " << buku.dapatkanTahunTerbit()
                 << ", Jumlah Tersedia: " << buku.dapatkanJumlahTersedia() << "\n";
        }
    }

    void cariBuku(const string& kriteria) const {
        cout << "Hasil Pencarian:\n";
        for (const auto& buku : daftarBuku) {
            if (buku.dapatkanJudul() == kriteria || buku.dapatkanPenulis() == kriteria) {
                cout << "- Judul: " << buku.dapatkanJudul() << ", Penulis: " << buku.dapatkanPenulis()
                     << ", Tahun Terbit: " << buku.dapatkanTahunTerbit()
                     << ", Jumlah Tersedia: " << buku.dapatkanJumlahTersedia() << "\n";
            }
        }
    }

    void pinjamBuku(const string& judul) {
        for (auto& buku : daftarBuku) {
            if (buku.dapatkanJudul() == judul && buku.dapatkanJumlahTersedia() > 0) {
                buku.aturJumlahTersedia(buku.dapatkanJumlahTersedia() - 1);
                cout << "Buku '" << judul << "' berhasil dipinjam.\n";
                return;
            }
        }
        cout << "Buku '" << judul << "' tidak tersedia untuk dipinjam.\n";
    }

    void kembalikanBuku(const string& judul) {
        for (auto& buku : daftarBuku) {
            if (buku.dapatkanJudul() == judul) {
                buku.aturJumlahTersedia(buku.dapatkanJumlahTersedia() + 1);
                cout << "Buku '" << judul << "' berhasil dikembalikan.\n";
                return;
            }
        }
        cout << "Buku '" << judul << "' bukan bagian dari koleksi perpustakaan.\n";
    }

    size_t size() const {
        return daftarBuku.size();
    }

    const Buku& dapatkanBuku(size_t indeks) const {
        return daftarBuku.at(indeks);
    }

    Buku& dapatkanBuku(size_t indeks) {
        return daftarBuku.at(indeks);
    }

private:
    vector<Buku> daftarBuku;
};

void tampilkanAnimasiSelamatDatang() {
    cout << "===== Selamat Datang di Sistem Informasi Perpustakaan =====\n";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "Inisialisasi sistem";
    for (int i = 0; i < 3; ++i) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << ".";
    }
    cout << "\n";
}

void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void tambahBuku(Perpustakaan* perpustakaan) {
    string judul, penulis;
    int tahunTerbit, jumlahTersedia;

    cout << "Masukkan judul buku: ";
    cin.ignore();
    getline(cin, judul);

    cout << "Masukkan penulis buku: ";
    getline(cin, penulis);

    cout << "Masukkan tahun terbit: ";
    cin >> tahunTerbit;

    cout << "Masukkan jumlah tersedia: ";
    cin >> jumlahTersedia;

    Buku buku(judul, penulis, tahunTerbit, jumlahTersedia);
    perpustakaan->tambahBuku(buku);
    cout << "Buku berhasil ditambahkan.\n";
}

void tampilkanDaftarBuku(const Perpustakaan* perpustakaan) {
    perpustakaan->tampilkanDaftarBuku();
}

void cariBuku(const Perpustakaan* perpustakaan) {
    string kriteria;
    cout << "Masukkan judul atau penulis buku: ";
    cin.ignore();
    getline(cin, kriteria);
    perpustakaan->cariBuku(kriteria);
}

void pinjamBuku(Perpustakaan* perpustakaan) {
    string judul;
    cout << "Masukkan judul buku yang akan dipinjam: ";
    cin.ignore();
    getline(cin, judul);

    bool bukuDitemukan = false;
    for (size_t i = 0; i < perpustakaan->size(); ++i) {
        if (perpustakaan->dapatkanBuku(i).dapatkanJudul() == judul && perpustakaan->dapatkanBuku(i).dapatkanJumlahTersedia() > 0) {
            perpustakaan->dapatkanBuku(i).aturJumlahTersedia(perpustakaan->dapatkanBuku(i).dapatkanJumlahTersedia() - 1);
            cout << "Buku '" << judul << "' berhasil dipinjam.\n";
            bukuDitemukan = true;
            break;
        }
    }

    if (!bukuDitemukan) {
        cout << "Buku '" << judul << "' tidak tersedia untuk dipinjam.\n";
    }
}

void kembalikanBuku(Perpustakaan* perpustakaan) {
    string judul;
    cout << "Masukkan judul buku yang akan dikembalikan: ";
    cin.ignore();
    getline(cin, judul);

    bool bukuDipinjam = false;
    for (size_t i = 0; perpustakaan->size(); ++i) {
        if (perpustakaan->dapatkanBuku(i).dapatkanJudul() == judul) {
            if (perpustakaan->dapatkanBuku(i).dapatkanJumlahTersedia() < perpustakaan->dapatkanBuku(i).dapatkanJumlahTotal()) {
                perpustakaan->dapatkanBuku(i).aturJumlahTersedia(perpustakaan->dapatkanBuku(i).dapatkanJumlahTersedia() + 1);
                cout << "Buku '" << judul << "' berhasil dikembalikan.\n";
                bukuDipinjam = true;
            } else {
                cout << "Jumlah buku '" << judul << "' sudah mencapai batas maksimum.\n";
            }
            break;
        }
    }

    if (!bukuDipinjam) {
        cout << "Anda belum meminjam buku '" << judul << "'.\n";
    }
}

int main() {
    tampilkanAnimasiSelamatDatang();

    Perpustakaan perpustakaan;

    int pilihan;

    do {
        cout << "\n===== Menu Perpustakaan =====\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilkan Daftar Buku\n";
        cout << "3. Cari Buku\n";
        cout << "4. Pinjam Buku\n";
        cout << "5. Kembalikan Buku\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        bersihkanLayar();

        switch (pilihan) {
            case 1:
                tambahBuku(&perpustakaan);
                break;
            case 2:
                tampilkanDaftarBuku(&perpustakaan);
                break;
            case 3:
                cariBuku(&perpustakaan);
                break;
            case 4:
                pinjamBuku(&perpustakaan);
                break;
            case 5:
                kembalikanBuku(&perpustakaan);
                break;
            case 0:
                cout << "Terima kasih telah menggunakan program.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }

    } while (pilihan != 0);

    return 0;
}
