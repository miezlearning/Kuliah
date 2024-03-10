#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <windows.h> // Kebutuhan tampilan terminal simbol UNICODE atau ASCII
#include <chrono>
#include <thread>



using namespace std;

struct Menu {
    int id_menu;
    string nama;
    double harga;
    string kategori;
};


struct Cabang {
    int id_cabang;
    string nama_cabang;
    string username;
    string password;
    string role;
};

struct User {
    string username;
    string password;
    string role;
    int saldo;
};

int ID_Pesanan = 1; 

struct Pesanan {
    int orderID;
    string nama_pelanggan;
    int id_menu;
    int jumlah;
    double total_harga;
    bool dikonfirmasi;
    Pesanan* next;
};

// VARIABEL UNTUK TEXT WARNA

const string WARNA_RESET = "\033[37m";
const string WARNA_P = "\033[0m";
const string BOLD = "\033[1m";
const string WARNA_MERAH = "\033[31m";
const string WARNA_HIJAU = "\033[32m";
const string WARNA_KUNING = "\033[33m";
const string WARNA_BIRU = "\033[34m";
 
Pesanan* front = NULL;
Pesanan* rear = NULL;

int menuSize = 0;


Cabang* currentAdminCabang = NULL;
vector<User> users;
vector<Cabang> cabangs;
Menu* menu = NULL;

User* currentUser = NULL; 
	
// Daerah Fungsi Utama pada program.
void Fitur_bersihkan_layar() {
	system("cls");
}

void Fitur_pause_layar() {
	cout << "\n"<< WARNA_P <<"[BACK] : "<< WARNA_RESET+BOLD <<" Tekan enter untuk melanjutkan..." << WARNA_RESET  << endl;
    cin.ignore(1000, '\n');
    cin.get();
    Fitur_bersihkan_layar();
}


void enqueue(Pesanan** front, Pesanan** rear, Pesanan* pesanan) {
    if (*rear == NULL) {
        *front = pesanan;
    } else {
        (*rear)->next = pesanan;
    }
    *rear = pesanan;
}



void dequeue(Pesanan** front, Pesanan** rear) {
    if (*front == NULL) {
        cout << "Antrian kosong." << endl;
        return;
    }

    Pesanan* temp = *front;
    if (temp->nama_pelanggan == currentUser->username) {
        *front = (*front)->next;
        delete temp;

        if (*front == NULL) {
            *rear = NULL;
        }
    } else {
        cout << "[NULL] : Anda tidak memiliki pesanan dalam antrian." << endl;
    }
}
	
void File_Baca() {
    ifstream file("menu.txt");

    if (file.is_open()) {
        file >> menuSize;
        if (menu != NULL) {
            delete[] menu;
        }
        menu = new Menu[menuSize];

        for (int i = 0; i < menuSize; i++) {
            file >> menu[i].id_menu;
            file.ignore();  // Membaca karakter koma dan spasi
            getline(file, menu[i].nama, ',');
            getline(file, menu[i].kategori, ',');  // Membaca kategori
            file >> menu[i].harga;
        }
        file.close();
    } else {
        cout << "[ERROR] : Gagal membuka berkas menu.txt" << endl;
    }
}

void File_Simpan_Menu() {
    ofstream file("menu.txt");

    if (file.is_open()) {
        file << menuSize << endl;
        for (int i = 0; i < menuSize; i++) {
            file << menu[i].id_menu << ", " << menu[i].nama << ", " << menu[i].kategori << ", " << menu[i].harga << endl;
        }
        file.close();
    } else {
        cout << "[ERROR] : Gagal membuka berkas menu.txt" << endl;
    }
}

	
void File_Simpan_Pesanan(Pesanan* front) {
    ofstream file("pesanan.txt");

    if (file.is_open()) {
        Pesanan* Traversal = front;
        while (Traversal != NULL) {
            file << Traversal->orderID << " "
                 << Traversal->nama_pelanggan << " "
                 << Traversal->id_menu << " "
                 << Traversal->jumlah << " "
                 << Traversal->total_harga << " "
                 << Traversal->dikonfirmasi << endl;
            Traversal = Traversal->next;
        }
        file.close();
    } else {
        cout << "[ERROR] : Gagal membuka berkas pesanan.txt" << endl;
    }
}

// Akhir Daerah Fungsi Utama pada program.

// Daerah Searching Booyer moore untuk Kategori
int Searching_BM_Kategori(const string& text, const string& pattern) {
    int m = pattern.length();
    int n = text.length();

    int badchar[256];

    for (int i = 0; i < 256; i++)
        badchar[i] = -1;

    for (int i = 0; i < m; i++)
        badchar[(int)pattern[i]] = i;

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            return s; // Pencocokan ditemukan, kembalikan posisi awal
        } else {
            s += max(1, j - badchar[(int)text[s + j]]);
        }
    }

    return -1; // Pencocokan tidak ditemukan
}
// Akhir Daerah Searching Booyer moore untuk Kategori


//Daerah Sorting Merge Sort Untuk Harga

void merge(Menu arr[], int l, int m, int r, bool ascending) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Menu L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if ((ascending && L[i].harga <= R[j].harga) || (!ascending && L[i].harga >= R[j].harga)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Menu arr[], int l, int r, bool ascending) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m, ascending);
        mergeSort(arr, m + 1, r, ascending);

        merge(arr, l, m, r, ascending);
    }
}


// Akhir Daerah Merge Sort Untuk Harga


// Daerah Menu Pelanggan
Pesanan* Pesanan_Tambah(Pesanan** front, Pesanan** rear) {
    Pesanan* pesananBaru = new Pesanan();
    pesananBaru->orderID = ID_Pesanan;

    while (true) {
        cout << WARNA_KUNING << BOLD << "[TIPS] "<<WARNA_RESET << BOLD << "Masukkan angka 0 untuk kembali ke Menu Pelanggan: ";
        cout << "\n \u2022 Masukkan ID Menu >> ";
        if (cin >> pesananBaru->id_menu) {
            if (pesananBaru->id_menu == 0) {
                delete pesananBaru; // Hapus pesananBaru jika pengguna memilih kembali
                cout << WARNA_BIRU << BOLD <<  "[INFO] : " << WARNA_RESET << "Pembuatan pesanan dibatalkan." << endl;
                return NULL;
            }

            // Cek apakah ID menu valid
            Menu* menuToOrder = NULL;
            for (int i = 0; i < menuSize; i++) {
                if (menu[i].id_menu == pesananBaru->id_menu) {
                    menuToOrder = &menu[i];
                    break;
                }
            }

            if (menuToOrder == NULL) {
                cout << WARNA_MERAH << BOLD << "[ERROR] : "<< WARNA_RESET << BOLD << " Menu tidak ditemukan." << endl;
                return NULL;
            }

            // Input jumlah pesanan dengan validasi
            while (true) {
                cout << " \u2022 Masukkan jumlah pesanan >> ";
                if (cin >> pesananBaru->jumlah && pesananBaru->jumlah > 0) {
                    break;
                } else {
                    cout << WARNA_MERAH << BOLD << "[ERROR] : "<<WARNA_RESET<<"Masukkan jumlah pesanan dalam bentuk angka positif." << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
            }

            pesananBaru->total_harga = menuToOrder->harga * pesananBaru->jumlah;
            pesananBaru->dikonfirmasi = false;
            pesananBaru->nama_pelanggan = currentUser->username;
            pesananBaru->next = NULL;

            if (*front == NULL) {
                *front = pesananBaru;
                *rear = pesananBaru;
            } else {
                (*rear)->next = pesananBaru;
                *rear = pesananBaru;
            }

            File_Simpan_Pesanan(*front);

            ID_Pesanan++; // Tambahkan ID_Pesanan jika pesanan berhasil ditambahkan 
            cout << WARNA_HIJAU << BOLD << "[BERHASIL] : Pesanan berhasil ditambahkan ke antrian." << WARNA_RESET << endl;
            return pesananBaru;
        } else {
            cout << WARNA_MERAH << BOLD << "[ERROR] : Masukkan ID menu dalam bentuk angka."<<WARNA_RESET << BOLD << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}


void Pesanan_Tampilkan() {
    if (front == NULL) {
        cout << WARNA_P << BOLD << "[NULL] : " << WARNA_RESET << "Anda belum memiliki pesanan." << endl;
    } else {
        cout << "+---------------------------------------------------------------------------------------------------------------+" << endl;
        cout << "| " << setw(10) << "ID Pesanan" << " | " << setw(20) << "Nama Menu" << " | " << setw(15) << "Harga (Rp)" << " | "
             << setw(10) << "Jumlah" << " | " << setw(20) << "Total Harga (Rp)" << " | " << setw(15) << "Status" << "     |" << endl;
        cout << "+---------------------------------------------------------------------------------------------------------------+" << endl;

        Pesanan* Traversal = front;
        double totalHargaPesanan = 0;

        while (Traversal != NULL) {
            if (Traversal->nama_pelanggan == currentUser->username) {
                const Menu* menuToDisplay = NULL;
                for (int i = 0; i < menuSize; i++) {
                    if (menu[i].id_menu == Traversal->id_menu) {
                        menuToDisplay = &menu[i];
                        break;
                    }
                }

                totalHargaPesanan += Traversal->total_harga;
                cout << "| " << setw(10) << Traversal->orderID << " | " << setw(20) << menuToDisplay->nama << " | " << setw(15) << menuToDisplay->harga << " | "
                     << setw(10) << Traversal->jumlah << " | " << setw(20) << Traversal->total_harga << " | " << setw(10) << (Traversal->dikonfirmasi ? "Dikonfirmasi" : "Belum dikonfirmasi") << "|" << endl;
            }
            Traversal = Traversal->next;
        }

        if (totalHargaPesanan > 0) {
            cout << "+---------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "| " << setw(3) << "Total Harga Semua Pesanan:" << setw(5) << "Rp " << totalHargaPesanan << right << endl;
            cout << "+---------------------------------------------------------------------------------------------------------------+" << endl;
        } else {
            cout << WARNA_P << BOLD << "[NULL] : " << WARNA_RESET << "Anda belum memiliki pesanan." << endl;
        }
    }
}

void Pesanan_Pembayaran(Pesanan** front, Pesanan** rear) {
    if (*front == NULL) {
        cout << WARNA_P << BOLD << "[NULL] : " << WARNA_RESET << "Tidak ada pesanan untuk dibayar." << endl;
        return;
    }

    double totalHarga = 0;
    Pesanan* pesanan = *front;

    // Cek apakah ada pesanan yang perlu dibayar
    while (pesanan) {
        if (pesanan->dikonfirmasi && pesanan->nama_pelanggan == currentUser->username) {
            totalHarga += pesanan->total_harga;
        }
        pesanan = pesanan->next;
    }

    if (totalHarga > 0) {
        // Tampilkan struk pesanan sebelum pembayaran
        cout << WARNA_HIJAU << "===================================================================" << endl;
        cout << "            STRUK PESANAN           " << endl;
        cout << "===================================================================" << WARNA_RESET << endl;
        cout << BOLD << "ID Pesanan | Nama Menu        | Jumlah | Total Harga" << WARNA_RESET << endl;

        pesanan = *front;
        while (pesanan) {
            if (pesanan->dikonfirmasi && pesanan->nama_pelanggan == currentUser->username) {
                const Menu* menuToDisplay = NULL;
                for (int i = 0; i < menuSize; i++) {
                    if (menu[i].id_menu == pesanan->id_menu) {
                        menuToDisplay = &menu[i];
                        break;
                    }
                }

                cout << setw(10) << pesanan->orderID << left <<  " | " << setw(16) << left << menuToDisplay->nama  << " | "
                     << setw(6) << pesanan->jumlah << " | " << setw(12) << right << pesanan->total_harga << endl;
            }
            pesanan = pesanan->next;
        }

        cout << WARNA_HIJAU << "===================================================================" << endl;
        cout << "Total Harga Semua Pesanan: Rp " << totalHarga << WARNA_RESET << endl;

        cout << " \u2022 Konfirmasi pembayaran (Y/N) >> ";
        char konfirmasi;
        cin >> konfirmasi;

        if (konfirmasi == 'Y' || konfirmasi == 'y') {
            if (currentUser->saldo < totalHarga) {
                cout << WARNA_MERAH << "[ERROR] : " << WARNA_RESET << "Saldo tidak mencukupi untuk membayar pesanan." << endl;
            } else {
                // Bayar pesanan
                currentUser->saldo -= totalHarga;
                cout << WARNA_HIJAU << BOLD << "[BERHASIL] : " << WARNA_RESET << "Pembayaran berhasil. Sisa saldo Anda: Rp " << currentUser->saldo << endl;

                // Hapus pesanan yang sudah dibayar dan dikonfirmasi dari queue
                Pesanan* pesananToDequeue = *front;
                Pesanan* prevPesanan = NULL;

                while (pesananToDequeue) {
                    if (pesananToDequeue->dikonfirmasi && pesananToDequeue->nama_pelanggan == currentUser->username) {
                        if (prevPesanan == NULL) {
                            dequeue(front, rear);
                            pesananToDequeue = *front;
                        } else {
                            prevPesanan->next = pesananToDequeue->next;
                            delete pesananToDequeue;
                            pesananToDequeue = prevPesanan->next;
                        }
                    } else {
                        prevPesanan = pesananToDequeue;
                        pesananToDequeue = pesananToDequeue->next;
                    }
                }

                if (*front == NULL) {
                    *rear = NULL;
                }
            }
        } else {
            cout << "Pembayaran dibatalkan." << endl;
        }
    } else {
        cout << WARNA_P << BOLD << "[NULL] : " << WARNA_RESET << "Tidak ada pesanan yang perlu dibayar atau pesanan belum dikonfirmasi." << endl;
    }
}


void Menu_Tampilkan_Berdasarkan_Kategori(const string& kategori) {
    File_Baca();

    if (menuSize == 0) {
        cout << WARNA_P << "[NULL] : " << WARNA_RESET << "Tidak ada menu yang tersedia." << endl;
    } else {
        bool found = false;
        cout << "+-----+-----------------------+-------------+---------------------+" << endl;
        cout << "| ID  | Nama                  | Harga (Rp)  | Kategori            |" << endl;
        cout << "+-----+-----------------------+-------------+---------------------+" << endl;
        for (int i = 0; i < menuSize; i++) {
            if (Searching_BM_Kategori(menu[i].kategori, kategori) != -1) {
                found = true;
                cout << "| " << setw(2) << left << menu[i].id_menu << "  | " << right << setw(21) << menu[i].nama << " | " << setw(11) << right << menu[i].harga << " | " << setw(19) << menu[i].kategori << " |" << endl;
            }
        }

        if (!found) {
            cout << "Menu dengan kategori '" << kategori << "' tidak ditemukan." << endl;
        }

        cout << "+-----+-----------------------+-------------+---------------------+" << endl;
    }
}


void topUpSaldo() {
    int topUp_JumlahSaldo;
    cout << "\u2022 Masukkan jumlah top-up >>  Rp. ";
    cin >> topUp_JumlahSaldo;

    if (topUp_JumlahSaldo <= 15000) {
        currentUser->saldo += topUp_JumlahSaldo;
        cout << WARNA_HIJAU + BOLD << "[BERHASIL] : "<< WARNA_RESET + BOLD << " Top-up berhasil. Saldo Anda sekarang: Rp " << currentUser->saldo << endl;
    } else {
        cout << WARNA_MERAH +BOLD << "[ERROR] : "<< WARNA_RESET + BOLD << " Jumlah top-up tidak valid maksimal "<< WARNA_MERAH + BOLD << "15000. "<< WARNA_RESET + BOLD << " Silakan coba lagi." << endl;
    }
}



void Tampilan_Saldo() {
    int saldoChoice = 0;
    while (saldoChoice != 3) {
        cout << WARNA_BIRU + BOLD << "+-------------------------------+" << endl;
        cout << "|      MENU SALDO              |" << endl;
        cout << "+-------------------------------+" << WARNA_BIRU + BOLD << endl;
        cout << "| " <<WARNA_RESET + BOLD  << setw(15) << left << "1. Lihat Saldo" << WARNA_BIRU + BOLD  << "              |" << endl;
        cout << "| " <<WARNA_RESET + BOLD << setw(15) << left << "2. Top-up" << WARNA_BIRU + BOLD << "              |" << endl;
        cout << "| " <<WARNA_RESET + BOLD << setw(15) << left << "3. Kembali ke Menu Pelanggan" << WARNA_BIRU + BOLD << " |" << endl;
        cout << "+-------------------------------+" <<WARNA_RESET + BOLD << endl;
        cout << " \u2022 Pilihan >> ";

        // Validasi untuk memastikan input adalah angka
        if (cin >> saldoChoice) {
            switch (saldoChoice) {
                case 1:
                    Fitur_bersihkan_layar();
                    cout << WARNA_BIRU + BOLD << "+--------------------------+" << endl;
                    cout << "|      SALDO ANDA          |" << endl;
                    cout << "+--------------------------+" << endl;
                    cout << "|                          " << endl;
                    cout << "|    Rp " << setw(10) << right << currentUser->saldo << endl;
                    cout << "|                          " << endl;
                    cout << "+--------------------------+" << WARNA_RESET + BOLD << endl;
                    Fitur_pause_layar();
                    break;
                case 2:
                    Fitur_bersihkan_layar();
                    topUpSaldo();
                    Fitur_pause_layar();
                    break;
                case 3:
                    break; // Kembali ke Menu Pelanggan
                default:
                    cout << WARNA_MERAH << BOLD << "[ERROR] : " << WARNA_RESET << "Pilihan tidak valid. Silakan coba lagi." << endl;
                    Fitur_pause_layar();
                    break;
            }
        } else {
            cout << WARNA_MERAH << BOLD << "[ERROR] : " << WARNA_RESET << "Masukkan pilihan dalam bentuk angka." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

// Akhir Menu Pelanggan



// Daerah Menu Kasir 
void Pesanan_Konfirmasi(Pesanan** front) {
    if (*front == NULL) {
        cout << WARNA_P << BOLD << "[NULL] : "<<WARNA_RESET<<"Tidak ada pesanan yang perlu dikonfirmasi." << endl;
        return;
    }

    Pesanan* pesanan = *front;
    bool pesananDitemukan = false;

    while (pesanan != NULL && pesanan->dikonfirmasi) {
        pesanan = pesanan->next;
    }

    if (pesanan == NULL) {
        cout << WARNA_P << BOLD << "[NULL] : "<<WARNA_RESET<<"Tidak ada pesanan yang perlu dikonfirmasi." << endl;
        return;
    }

    cout << "+---------+------------------------+----------+--------+--------------+" << endl;
    cout << "| OrderID | Nama Pelanggan         | Menu ID  | Jumlah | Total Harga  |" << endl;
    cout << "+---------+------------------------+----------+--------+--------------+" << endl;

    cout << "|" << setw(8) << pesanan->orderID << " | " << setw(23) << pesanan->nama_pelanggan
         << " | " << setw(8) << pesanan->id_menu << " | " << setw(6) << pesanan->jumlah
         << " | Rp " << setw(11) << pesanan->total_harga << " |" << endl;
    cout << "+---------+------------------------+----------+--------+--------------+" << endl;

    char choice;
    cout << WARNA_KUNING << BOLD << "[KONFIRMASI] : "<< WARNA_RESET << " Apakah kamu yakin mengkonfirmasi pesanan ini "<< WARNA_P << BOLD << "(Y/N)? " << WARNA_RESET;
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        pesanan->dikonfirmasi = true;
        cout << WARNA_HIJAU << BOLD << "[BERHASIL] : Pesanan dengan ID " << pesanan->orderID << WARNA_HIJAU << BOLD <<  " berhasil dikonfirmasi." << WARNA_RESET << endl;

        // Simpan perubahan ke berkas
        ofstream file("pesanan.txt");
        if (file.is_open()) {
            Pesanan* Traversal = *front;
            while (Traversal != NULL) {
                file << Traversal->orderID << " "
                     << Traversal->nama_pelanggan << " "
                     << Traversal->id_menu << " "
                     << Traversal->jumlah << " "
                     << Traversal->total_harga << " "
                     << Traversal->dikonfirmasi << endl;
                Traversal = Traversal->next;
            }
            file.close();
        } else {
            cout << WARNA_MERAH << BOLD << "[ERROR] : Gagal membuka berkas pesanan.txt" << WARNA_RESET << endl;
        }
    } else {
        cout << WARNA_HIJAU << BOLD << "[BERHASIL] : "<< WARNA_RESET << " Konfirmasi pesanan dibatalkan." << endl;
    }
    
}


void Pesanan_Seluruh_Pelanggan() {
    if (front == NULL) {
        cout << WARNA_P << "[NULL] : " << WARNA_RESET << "Tidak ada pesanan yang belum dikonfirmasi." << endl;
    } else {
        Pesanan* current = front;
        cout << "+---------+----------------------+-------------+-----------------+" << endl;
        cout << "| OrderID | Nama Pelanggan      | ID Menu     | Jumlah Pesanan |" << endl;
        cout << "+---------+----------------------+-------------+-----------------+" << endl;
        while (current != NULL) {
            cout << "| " << setw(8) << left << current->orderID << " | " << setw(20) << left << current->nama_pelanggan
                 << " | " << setw(11) << left << current->id_menu << " | " << setw(15) << left << current->jumlah << " |" << endl;
            current = current->next;
        }
        cout << "+---------+----------------------+-------------+-----------------+" << endl;
    }
}

void Menu_Tampilkan() {
    File_Baca();

    if (menuSize == 0) {
        cout << WARNA_P << "[NULL] : " << WARNA_RESET << "Tidak ada menu yang tersedia." << endl;
        return;
    }

    // Tampilkan menu sebelum sorting
    cout << "+-----------------------------------------------------------------+" << endl;
    cout << "|                               MENU                              |" << endl;
    cout << "+-----+-----------------------+-------------+---------------------+" << endl;
    cout << "| ID  | Nama                  | Harga (Rp)  | Kategori            |" << endl;
    cout << "+-----+-----------------------+-------------+---------------------+" << endl;
    for (int i = 0; i < menuSize; i++) {
        cout << "| " << setw(2) << left << menu[i].id_menu << "  | " << right << setw(21) << menu[i].nama << " | "
             << setw(11) << right << menu[i].harga << " | " << setw(19) << menu[i].kategori << " |" << endl;
    }
    cout << "+-----+-----------------------+-------------+---------------------+" << endl;

    char konfirmasi;
    cout << "\nApakah Anda ingin mengurutkan menu? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        return;
    }

    int sortChoice;
    int attempt = 0;

    do {
        if (attempt > 0) {
            cout << BOLD << WARNA_MERAH << "[ERROR] : Pilihan tidak valid. Harap masukkan 1 atau 2." << WARNA_RESET << endl;
        }

        cout << "+--------------------------------+" << endl;
        cout << "|         URUTKAN MENU           |" << endl;
        cout << "+--------------------------------+" << endl;
        cout << "| 1. Ascending (Harga Terendah)  |" << endl;
        cout << "| 2. Descending (Harga Tertinggi)|" << endl;
        cout << "+--------------------------------+" << endl;
        cout << "\u2022 Pilihan >> ";
        cin >> sortChoice;

        if (cin.fail()) {
            cout << BOLD << WARNA_MERAH << "[ERROR] : Pilihan tidak valid. Harap masukkan 1 atau 2." << WARNA_RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        attempt++;
    } while (sortChoice != 1 && sortChoice != 2);

    bool ascending = (sortChoice == 1);

    Menu tempMenu[menuSize];
    for (int i = 0; i < menuSize; i++) {
        tempMenu[i] = menu[i];
    }

    mergeSort(tempMenu, 0, menuSize - 1, ascending);

    cout << "+-----------------------------------------------------------------+" << endl;
    cout << "|                           MENU SORTING                          |" << endl;
    cout << "+-----+-----------------------+-------------+---------------------+" << endl;
    cout << "| ID  | Nama                  | Harga (Rp)  | Kategori            |" << endl;
    cout << "+-----+-----------------------+-------------+---------------------+" << endl;
    for (int i = 0; i < menuSize; i++) {
        cout << "| " << setw(2) << left << tempMenu[i].id_menu << "  | " << right << setw(21) << tempMenu[i].nama << " | "
             << setw(11) << right << tempMenu[i].harga << " | " << setw(19) << tempMenu[i].kategori << " |" << endl;
    }
    cout << "+-----+-----------------------+-------------+---------------------+" << endl;
}







void Menu_Buat() {
    File_Baca(); // Memuat menu dari file menu.txt sebelum menambahkan menu baru

    cout << "\u2022 Masukkan nama menu baru >> ";
    cin.ignore();
    string nama;
    getline(cin >> ws, nama);

    // Validasi untuk memastikan nama menu tidak kosong
    while (nama.empty()) {
        cout << WARNA_MERAH << BOLD << "[ERROR] : "<<WARNA_RESET+BOLD <<" Nama menu tidak boleh kosong." << endl;
        cout << "\n \u2022 Masukkan nama menu baru >> ";
        getline(cin >> ws, nama);
    }

    cout << "Masukkan kategori menu: ";
    string kategori;
    getline(cin >> ws, kategori);

    // Validasi untuk memastikan kategori menu tidak kosong
    while (kategori.empty()) {
        cout << WARNA_MERAH << BOLD << "[ERROR] : "<<WARNA_RESET+BOLD <<" Kategori menu tidak boleh kosong." << endl;
        cout << "\n \u2022 Masukkan kategori menu >> ";
        getline(cin >> ws, kategori);
    }

    cout << "\u2022 Masukkan harga menu >> ";
    double harga;

    // Validasi untuk memastikan input harga adalah angka positif
    while (!(cin >> harga) || harga <= 0) {
        cout << WARNA_MERAH << BOLD <<  "[ERROR] : "<<WARNA_RESET+BOLD << " Masukkan harga menu dalam bentuk angka positif." << endl;
        cout << "\n \u2022 Masukkan harga menu >> ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    Menu* newMenu = new Menu[menuSize + 1];
    for (int i = 0; i < menuSize; i++) {
        newMenu[i] = menu[i];
    }

    newMenu[menuSize].id_menu = menuSize + 1;
    newMenu[menuSize].nama = nama;
    newMenu[menuSize].kategori = kategori;
    newMenu[menuSize].harga = harga;

    menuSize++;
    delete[] menu;
    menu = newMenu;

    File_Simpan_Menu();
    cout << WARNA_HIJAU << BOLD << "[BERHASIL] : "<< WARNA_RESET << BOLD << " Menu baru  "<<WARNA_HIJAU << BOLD << "berhasil ditambahkan."<< WARNA_RESET << BOLD  << endl;
}


void Menu_Ubah() {
    File_Baca(); // Memuat menu dari file menu.txt sebelum mengubah menu
    Menu_Tampilkan();
    
    cout << "\n";
    cout << WARNA_KUNING << BOLD << "[TIPS] "<<WARNA_RESET << BOLD << "Ketik angka 0 untuk kembali ke menu kasir." << endl;
    int idToUpdate;

    // Validasi untuk memastikan input ID adalah angka positif
    while (true) {
        cout << "\n \u2022 Masukkan ID menu yang ingin diubah >> ";
        if (cin >> idToUpdate && idToUpdate >= 0) {
            break;
        } else {
            cout << WARNA_MERAH << BOLD << "[ERROR] : Masukkan ID menu dalam bentuk angka positif."<<WARNA_RESET << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
	if (idToUpdate == 0) {
        cout << "Kembali ke menu kasir..." << endl;
        return;
    }
    for (int i = 0; i < menuSize; i++) {
        if (menu[i].id_menu == idToUpdate) {
            cout << " \u2022 Masukkan nama menu yang baru >>  ";
            cin.ignore();
            getline(cin, menu[i].nama);
            
            // Validasi untuk memastikan nama menu tidak kosong
            while (menu[i].nama.empty()) {
                cout << WARNA_MERAH+BOLD <<"[ERROR] : "<< WARNA_RESET << " Nama menu tidak boleh kosong." << endl;
                cout << " \u2022 Masukkan nama menu yang baru >>  ";
                getline(cin, menu[i].nama);
            }

            cout << " \u2022 Masukkan kategori menu yang baru >> ";
            getline(cin, menu[i].kategori);

            // Validasi untuk memastikan kategori menu tidak kosong
            while (menu[i].kategori.empty()) {
                cout << WARNA_MERAH << "[ERROR] : "<< WARNA_RESET << " Kategori menu tidak boleh kosong." << endl;
                cout << " \u2022 Masukkan kategori menu yang baru >> ";
                getline(cin, menu[i].kategori);
            }

            cout << "Masukkan harga menu yang baru: ";

            // Validasi untuk memastikan input harga adalah angka positif
            while (!(cin >> menu[i].harga) || menu[i].harga <= 0) {
                cout << WARNA_MERAH+BOLD << "[ERROR] : "<< WARNA_RESET << " Masukkan harga menu dalam bentuk angka positif." << endl;
                cout << " \u2022 Masukkan harga menu yang baru >> ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            File_Simpan_Menu();
            cout << WARNA_HIJAU << "[BERHASIL] : "<< WARNA_RESET << " Menu berhasil diubah." << endl;
            return;
        }
    }

	cout << WARNA_MERAH+BOLD << "[ERROR] : "<< WARNA_RESET << " Menu dengan ID " << idToUpdate << WARNA_MERAH << " tidak ditemukan." <<WARNA_RESET << endl;

}


void Menu_Hapus() {
    File_Baca(); 
	Menu_Tampilkan();
    int idToDelete;
    cout << " \u2022 Masukkan ID menu yang ingin dihapus >> ";
    cin >> idToDelete;

    int indexToDelete = -1;
    for (int i = 0; i < menuSize; i++) {
        if (menu[i].id_menu == idToDelete) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete != -1) {
        for (int i = indexToDelete; i < menuSize - 1; i++) {
            menu[i] = menu[i + 1];
        }
        menuSize--;

        // Berfungsi sebagai memperbarui ID menu lain ketika ada yang dihapus ID diantaranya.
        for (int i = indexToDelete; i < menuSize; i++) {
            menu[i].id_menu = i + 1;
        }

        Menu* newMenu = new Menu[menuSize];
        for (int i = 0; i < menuSize; i++) {
            newMenu[i] = menu[i];
        }
        delete[] menu;
        menu = newMenu;

        File_Simpan_Menu();
        cout << WARNA_HIJAU <<  "[BERHASIL] : Menu berhasil dihapus." <<WARNA_RESET << endl;
    } else {
        cout << WARNA_MERAH+BOLD << "[ERROR] : "<< WARNA_RESET << " Menu dengan ID " << idToDelete << WARNA_MERAH <<" tidak ditemukan." << WARNA_RESET << endl;
    }
}
//  Akhir Daerah Fungsi Menu Kasir



// Daerah Menu Admin
void Admin_LihatAkun_Pelanggan() {
    cout << WARNA_BIRU << "+------------------------------+" << endl;
    cout << "| "<<WARNA_RESET+BOLD <<" Daftar Akun Pelanggan: "<<WARNA_BIRU<<"     |" << endl;
    cout << "+------------------------------+" << endl;
    cout << "| " << WARNA_RESET+BOLD << setw(10) << left << "Username" << WARNA_BIRU << " |" << setw(10) << WARNA_RESET+BOLD <<  "Saldo" <<WARNA_BIRU <<"           |" << endl;
    cout << "+------------------------------+" << endl;
    for (const User& user : users) {
        if (user.role == "pelanggan") {
            cout << "| " << setw(10)  << left << WARNA_RESET+BOLD << user.username << setw(13) << WARNA_BIRU << " | " << WARNA_RESET+BOLD <<  right << "Rp " << user.saldo << WARNA_BIRU << endl;
        }
    }
    cout << "+------------------------------+"<< WARNA_RESET << endl;
}

void Admin_LihatAkun_Kasir() {
    cout << WARNA_BIRU << "+---------------------------+" << endl;
    cout << "| "<< WARNA_RESET+BOLD << " Daftar Akun Kasir: "<<WARNA_BIRU<<"      |" << endl;
    cout << "+---------------------------+" << endl;
    cout << "| " <<WARNA_RESET+BOLD << setw(20) << left << "Username" << WARNA_BIRU << "      |" << endl;
    cout << "+---------------------------+" << endl;
    for (const User& user : users) {
        if (user.role == "kasir") {
            cout << "| "<<WARNA_RESET+BOLD << setw(20) << left << user.username << WARNA_BIRU <<"      |" << endl;
        }
    }
    cout << "+---------------------------+"<< WARNA_RESET  << endl;
}


void Admin_LihatSeluruh_Akun() {
    cout << WARNA_BIRU << "+------------------------------------------------------------+" << endl;
    cout << WARNA_BIRU << "| "<<WARNA_RESET+BOLD<<" Daftar Semua Akun:                            "<<WARNA_BIRU<<"            |" << endl;
    cout << "+------------------------------------------------------------+" << endl;
    cout << "| " <<WARNA_RESET+BOLD << setw(20) << left << "Username" << WARNA_BIRU << " | " <<WARNA_RESET+BOLD << setw(10) << left << "Role" << WARNA_BIRU<< " | "<<WARNA_RESET+BOLD << setw(3) << right << "Saldo" <<WARNA_BIRU << endl;
    cout << "+------------------------------------------------------------+" << endl;
    for (const User& user : users) {
        cout << "| " << WARNA_RESET << setw(20) << left << user.username << WARNA_BIRU <<  " | " <<WARNA_RESET+BOLD << setw(10) << left << user.role <<WARNA_BIRU;
        if (user.role == "pelanggan") {
            cout << " | " <<WARNA_RESET+BOLD << setw(3) << right << "Rp " << user.saldo <<WARNA_BIRU << endl;
        } else {
            cout << " |" << WARNA_RESET+BOLD << setw(3) << right << "   Tidak Perlu Saldo "  << WARNA_BIRU << endl;
        }
    }
    cout << "+------------------------------------------------------------+" << WARNA_RESET << endl;
}


void Admin_Tampilan_LihatAkun() {
    int pilih;

    while (true) {
        Fitur_bersihkan_layar();
        cout << WARNA_BIRU << "+-----------------------------+" << endl;
        cout << "|  "<< WARNA_RESET+BOLD << "Pilihan Tampilan Akun:  "<< WARNA_BIRU <<"   |" << endl;
        cout << "+-----------------------------+" << endl;
        cout << "| " << WARNA_RESET << "1. Pelanggan              "<< WARNA_BIRU <<"  |" << endl;
        cout << "| " << WARNA_RESET << "2. Kasir                   "<< WARNA_BIRU <<" |" << endl;
        cout << "| " << WARNA_RESET << "3. Semua Akun              "<< WARNA_BIRU <<" |" << endl;
        cout << "| " << WARNA_RESET << "0. Kembali                 "<< WARNA_BIRU <<" |" << endl;
        cout << "+-----------------------------+"<< WARNA_RESET << endl;
        cout << " \u2022 Pilihan >> ";
        cin >> pilih;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << BOLD << WARNA_MERAH << "[ERROR] : Hanya angka!" << WARNA_RESET << endl;
            continue;
        }

        switch (pilih) {
            case 1:
                Fitur_bersihkan_layar();
                Admin_LihatAkun_Pelanggan();
                Fitur_pause_layar();
                break;
            case 2:
                Fitur_bersihkan_layar();
                Admin_LihatAkun_Kasir();
                Fitur_pause_layar();
                break;
            case 3:
                Fitur_bersihkan_layar();
                Admin_LihatSeluruh_Akun();
                Fitur_pause_layar();
                break;
            case 0:
                return;
                break;
            default:
                Fitur_bersihkan_layar();
                cout << BOLD << WARNA_MERAH << "[ERROR] : Pilihan tidak valid." << WARNA_RESET << endl;
                Fitur_pause_layar();
                break;
        }
    }
}


void Admin_Tambah_Akun() {
    User Pengguna_Baru;
     while (true) {
        cout << " \u2022 Masukkan Username baru >>  ";
        getline(cin >> ws, Pengguna_Baru.username);

        // Memeriksa jika username mengandung spasi atau kosong
        if (Pengguna_Baru.username.find(' ') == string::npos && !Pengguna_Baru.username.empty()) {
            break; // Kalau memenuhi syarat keluar dari perulangannya
        } else {
            cout << " [ERROR]: Username tidak boleh kosong atau mengandung spasi. Silakan coba lagi." << endl;
        }
    }

    bool username_ada = false;
    for (const User &user : users) {
        if (user.username == Pengguna_Baru.username) {
            username_ada = true;
            break;
        }
    }

    if (username_ada) {
        cout << WARNA_MERAH << "[ERROR] : "<< WARNA_RESET << " Username sudah digunakan. "<< WARNA_MERAH << "Tambahkan akun gagal."<< WARNA_RESET << endl;
        return;
    }

    cout << " \u2022 Masukkan Password baru >> ";
    cin >> Pengguna_Baru.password;
    
    do {
	    cout << "\u2022 Pilih role baru (pelanggan/kasir) >>  ";
	    cin >> Pengguna_Baru.role;

	
	    if (Pengguna_Baru.role == "pelanggan" || Pengguna_Baru.role == "kasir") {
	        cout << WARNA_HIJAU << "[BERHASIL] : "<< WARNA_RESET << " Role berhasil ditambahkan." << endl;
	    } else {
	        cout << WARNA_MERAH << "[ERROR] : "<< WARNA_RESET << " Pilih role yang "<<WARNA_HIJAU+BOLD <<" valid "<< WARNA_P+BOLD << "(pelanggan/kasir)." << WARNA_RESET << endl;
	    }
	} while (Pengguna_Baru.role != "pelanggan" && Pengguna_Baru.role != "kasir");

    if (Pengguna_Baru.role == "pelanggan") {
        cout << " \u2022 Masukkan saldo awal >>  Rp. ";
        cin >> Pengguna_Baru.saldo;
    } else {
        Pengguna_Baru.saldo = 0; 
    }

    users.push_back(Pengguna_Baru);
    cout << WARNA_HIJAU << BOLD << "[BERHASIL] : "<<WARNA_RESET << "Akun baru berhasil "<< WARNA_HIJAU << BOLD << "ditambahkan." <<WARNA_RESET<< endl;
}

void Admin_Edit_Akun() {
    Admin_LihatSeluruh_Akun();
    string Var_Edit_Akun;
    cout << "\n \u2022 Masukkan Username akun yang ingin diubah >> ";
    cin >> Var_Edit_Akun;

    bool found = false;
    for (User& user : users) {
        if (user.username == Var_Edit_Akun) {
            found = true;
            cout << WARNA_BIRU << "+-----------------------------+" << endl;
			cout << WARNA_BIRU << "| "<<WARNA_RESET+BOLD <<" Edit Akun " << user.username << ":" << endl;
			cout << WARNA_BIRU << "+-----------------------------+" << endl;
			cout << "| "<< WARNA_RESET+BOLD << "Pilih yang ingin diubah "<< WARNA_BIRU << "    |" << endl;
			cout << "+-----------------------------+" << endl;
			cout << "| "<< WARNA_RESET+BOLD <<"1. Password                "<< WARNA_BIRU <<" |" << endl;
			cout << "| "<< WARNA_RESET+BOLD <<"2. Role                    "<< WARNA_BIRU <<" |" << endl;
			if (user.role == "pelanggan") {
			    cout << "| "<< WARNA_RESET+BOLD <<"3. Saldo                   "<< WARNA_BIRU <<" |" << endl;
			}
			cout << "+-----------------------------+"<< WARNA_RESET << endl;
            cout << "\n \u2022 Pilihan >> ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "\n \u2022 Masukkan Password baru >> ";
                    cin >> user.password;
                    cout << WARNA_HIJAU << "[BERHASIL] : "<< WARNA_RESET << " Password berhasil "<<WARNA_HIJAU << BOLD << " diubah." << WARNA_RESET << endl;
                    break;
                case 2:
                    do {
					    cout << "\n \u2022 Pilih role baru (pelanggan/kasir) >>  ";
					    cin >> user.role;
		
					
					    if (user.role == "pelanggan" || user.role == "kasir") {
					        cout << WARNA_HIJAU << "[BERHASIL] : "<< WARNA_RESET << " Role berhasil diubah." << endl;
					    } else {
					        cout << WARNA_MERAH << "[ERROR] : "<< WARNA_RESET << " Pilih role yang "<<WARNA_HIJAU+BOLD <<" valid "<< WARNA_P+BOLD << "(pelanggan/kasir)." << WARNA_RESET << endl;
					    }
					} while (user.role != "pelanggan" && user.role != "kasir");
                    break;
                case 3:
                    if (user.role == "pelanggan") {
                        cout << "\n \u2022 Masukkan Saldo baru >>  Rp. ";
                        cin >> user.saldo;
                        cout << WARNA_HIJAU <<  "[BERHASIL] : " << WARNA_RESET << " Saldo berhasil  " <<WARNA_HIJAU+BOLD <<"diubah." << WARNA_RESET << endl;
                    } else {
                        cout << WARNA_MERAH+BOLD << "[ERROR] : "<< WARNA_RESET << " Akun ini bukan akun pelanggan, saldo tidak dapat diubah." << endl;
                    }
                    break;
                default:
                    cout << WARNA_MERAH+BOLD << "[ERROR] : "<< WARNA_RESET << " Pilihan tidak valid." << endl;
                    break;
            }
            break;
        }
    }

    if (!found) {
        cout << WARNA_MERAH+BOLD << "[ERROR] : "<< WARNA_RESET << " Akun dengan username " << Var_Edit_Akun << WARNA_MERAH+BOLD << " tidak ditemukan." << WARNA_RESET << endl;
    }
}

void Admin_Hapus_Akun() {
    Admin_LihatSeluruh_Akun();
    string Var_HapusAkun;
    cout << " \u2022 Masukkan username akun yang ingin dihapus >>  ";
    cin >> Var_HapusAkun;
    bool found = false;
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->username == Var_HapusAkun) {
            found = true;
            users.erase(it);
            cout << WARNA_HIJAU << "[BERHASIL] : " << WARNA_RESET << " Akun dengan username " << Var_HapusAkun <<  WARNA_HIJAU+BOLD << " berhasil dihapus." << endl;
            break;
        }
    }

    if (!found) {
        cout << WARNA_MERAH+BOLD << "[ERROR] : "<< WARNA_RESET << " Akun dengan username " << Var_HapusAkun << WARNA_MERAH+BOLD << " tidak ditemukan." << WARNA_RESET << endl;
    }
}

// Akhir Daerah Fungsi Menu Admin


// Daerah Menu Utama

void Fitur_SlideText(const string& teks) {
    for (char karakter : teks) {
        cout << karakter;
        cout.flush(); // Memastikan output langsung terlihat
        this_thread::sleep_for(chrono::milliseconds(1)); 
    }
    cout << endl; // Memberikan baris baru setelah selesai menampilkan slide
}





bool Tampilan_Pelanggan() {
    int VarInput_Pelanggan;

    while (true) {
        Fitur_bersihkan_layar();
        cout << WARNA_KUNING + BOLD << "+-------------------------+" << endl;
        Fitur_SlideText("| " + string(5, ' ') + "MENU PELANGGAN" + string(3, ' ') + "  |");
        cout << "+-------------------------+" << endl;
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m1. Lihat Pesanan\033[33m" + string(5, ' ') + " |");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m2. Tambah Pesanan\033[33m" + string(5, ' ') + "|");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m3. Cari Menu\033[33m" + string(9, ' ') + " |");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m4. Pembayaran\033[33m" + string(9, ' ') + "|");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m5. Pesanan\033[33m" + string(12, ' ') + "|");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m6. Saldo\033[33m" + string(13, ' ') + " |");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m0. Logout\033[33m" + string(13, ' ') + "|");
        cout << "+-------------------------+" << WARNA_RESET + BOLD << endl;
        cout << "\n \u2022 Pilihan >> ";
        cin >> VarInput_Pelanggan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << BOLD << WARNA_MERAH << "[ERROR] : Hanya angka!" << WARNA_RESET << endl;
            continue;
        }

        switch (VarInput_Pelanggan) {
            case 1:
                Fitur_bersihkan_layar();
                Pesanan_Tampilkan();
                Fitur_pause_layar();
                break;
            case 2:
            	{
                Fitur_bersihkan_layar();
                Menu_Tampilkan();
                Pesanan* pesananBaru = Pesanan_Tambah(&front, &rear);
                Fitur_pause_layar();
                break;
            }
            case 3:
                {
                    Fitur_bersihkan_layar();
                    string kategori;
                    
                    cout << WARNA_KUNING << BOLD << "[TIPS] "<<WARNA_RESET << BOLD << "Cari menu hanya 2 kategori [Minuman/Makanan] untuk saat ini." << endl;
                    cout << "\u2022 Masukkan kategori menu yang dicari >>  ";
                    cin.ignore(1000, '\n');
                    getline(cin, kategori);
                    Menu_Tampilkan_Berdasarkan_Kategori(kategori);
                    cout << "\n"<< WARNA_P <<"[BACK] : "<< WARNA_RESET+BOLD <<" Tekan enter untuk melanjutkan..." << WARNA_RESET  << endl;
				    cin.get();
				    Fitur_bersihkan_layar();
                    break;
                }
            case 4:
            	Fitur_bersihkan_layar();
                Pesanan_Pembayaran(&front, &rear);
                Fitur_pause_layar();
                break;
            case 5:
                Fitur_bersihkan_layar();
                Pesanan_Pembayaran(&front, &rear);
                Fitur_pause_layar();
                break;
            case 6:
                Fitur_bersihkan_layar();
                Tampilan_Saldo();
                Fitur_pause_layar();
                break;
            case 0:
                {
                    string pilih_logout;
                    cout << WARNA_KUNING + BOLD << "[KONFIRMASI] : " << WARNA_RESET + BOLD << " Apakah Anda yakin ingin Logout (Y/N)?";
                    cin >> pilih_logout;
                    if (pilih_logout == "y" || pilih_logout == "Y") {
                        Fitur_pause_layar();
                        currentUser = NULL; // Logout pengguna
                        return true; // Kembalikan true saat logout
                    } else {
                        Fitur_pause_layar();
                        continue;
                    }
                    break;
                }
            default:
                cout << BOLD << WARNA_MERAH << "[ERROR] : Pilihan tidak valid. Silakan coba lagi." << WARNA_RESET << endl;
                Fitur_pause_layar();
                break;
        }
    }

    return false; // Kembalikan false saat pengguna kembali ke menu utama
}


bool Tampilan_Kasir() {
    int VarInput_Kasir;

    while (true) {
        Fitur_bersihkan_layar();
        cout << WARNA_HIJAU + BOLD << "+------------------------------+" << endl;
        Fitur_SlideText("| " + string(8, ' ') + "MENU KASIR\033[32m" + string(10, ' ') + " |");
        cout << "+------------------------------+" << endl;
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m1. Konfirmasi Pesanan\033[32m" + string(4, ' ') + "  |");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m2. Lihat Menu\033[32m" + string(8, ' ') + "      |");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m3. Tambah Menu\033[32m" + string(7, ' ') + "      |");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m4. Edit Menu\033[32m" + string(9, ' ') + "      |");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m5. Hapus Menu\033[32m" + string(8, ' ') + "      |");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m6. Lihat Pesanan\033[32m" + string(6, ' ') + "     |");  
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m0. Logout\033[32m" + string(10, ' ') + "        |");
        cout << "+------------------------------+" << WARNA_RESET + BOLD << endl;
        cout << "\n \u2022 Pilihan >> ";
        cin >> VarInput_Kasir;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << BOLD << WARNA_MERAH << "[ERROR] : Hanya angka!" << WARNA_RESET << endl;
            continue;
        }

        switch (VarInput_Kasir) {
            case 1:
                Pesanan_Konfirmasi(&front);
                Fitur_pause_layar();
                break;
            case 2:
                Menu_Tampilkan();
                Fitur_pause_layar();
                break;
            case 3:
                Menu_Buat();
                Fitur_pause_layar();
                break;
            case 4:
                Menu_Ubah();
                Fitur_pause_layar();
                break;
            case 5:
                Menu_Hapus();
                Fitur_pause_layar();
                break;
            case 6:
                Fitur_bersihkan_layar();
                Pesanan_Seluruh_Pelanggan();  // Menambahkan fungsi untuk menampilkan pesanan
                Fitur_pause_layar();
                break;
            case 0:
                {
                    string pilih_logout;
                    cout << WARNA_KUNING + BOLD << "[KONFIRMASI] : " << WARNA_RESET + BOLD << " Apakah Anda yakin ingin Logout (Y/N)?";
                    cin >> pilih_logout;
                    if (pilih_logout == "y" || pilih_logout == "Y") {
                        Fitur_pause_layar();
                        currentUser = NULL; // Logout pengguna
                        return true; // Kembalikan true saat logout
                    } else {
                        Fitur_pause_layar();
                        continue;
                    }
                    break;
                }
            default:
                cout << BOLD << WARNA_MERAH << "[ERROR] : Pilihan tidak valid. Silakan coba lagi." << WARNA_RESET << endl;
                Fitur_pause_layar();
                break;
        }
    }

    return false; // Kembalikan false saat pengguna kembali ke menu utama
}




bool Tampilan_Admin() {
    int VarInput_Admin;

    while (true) {
        Fitur_bersihkan_layar();
        cout << BOLD << WARNA_BIRU << "+-------------------------+" << endl;
        Fitur_SlideText("| " + string(5, ' ') + "MENU ADMIN\033[34m" + string(9, ' ') + "|");
        cout << "+-------------------------+" << endl;
        Fitur_SlideText("| " + string(2, ' ') +  "\033[37m 1. Tampilkan Akun\033[34m" + string(3, ' ') + " |");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m 2. Tambah Akun\033[34m" + string(3, ' ') + "    |");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m 3. Edit Akun\033[34m" + string(3, ' ') + "      |");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m 4. Hapus Akun\033[34m" + string(3, ' ') + "     |");
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m 0. Logout\033[34m" + string(8, ' ') + "    |");
        cout << "+-------------------------+" << WARNA_RESET + BOLD << endl;
        cout << "\n \u2022 Pilihan >> ";
        cin >> VarInput_Admin;

        if (cin.fail()) {
            cin.clear();
            cout << BOLD << WARNA_MERAH << "[ERROR] : Hanya angka!" << WARNA_RESET << endl;
            Fitur_pause_layar();
            continue;
        }

        switch (VarInput_Admin) {
            case 1:
                Fitur_bersihkan_layar();
                Admin_Tampilan_LihatAkun();
                Fitur_pause_layar();
                break;
            case 2:
                Fitur_bersihkan_layar();
                Admin_Tambah_Akun();
                Fitur_pause_layar();
                break;
            case 3:
                Fitur_bersihkan_layar();
                Admin_Edit_Akun();
                Fitur_pause_layar();
                break;
            case 4:
                Fitur_bersihkan_layar();
                Admin_Hapus_Akun();
                Fitur_pause_layar();
                break;
            case 0:
                {
                    string pilih_logout;
                    cout << WARNA_KUNING + BOLD << "[KONFIRMASI] : " << WARNA_RESET + BOLD << " Apakah Anda yakin ingin Logout (Y/N)?";
                    cin >> pilih_logout;
                    if (pilih_logout == "y" || pilih_logout == "Y") {
                        Fitur_pause_layar();
                        currentUser = NULL; // Logout pengguna
                        return true; // Kembalikan true saat logout
                    } else {
                        Fitur_pause_layar();
                        continue;
                    }
                    break;
                }
            default:
                cout << BOLD << WARNA_MERAH << "[ERROR] : Pilihan tidak valid. Silakan coba lagi." << WARNA_RESET << endl;
                Fitur_pause_layar();
                break;
        }
    }

    return false; // Kembalikan false saat pengguna kembali ke menu utama
}



void Proses_Daftar() {
    string username, password;
    bool username_ada;

    do {
        cout << BOLD  << " \u2022 Masukkan Username  >>  ";
    	cin >> username;

        // Periksa apakah username sudah digunakan di vektor users
        username_ada = false;
        for (const User &user : users) {
            if (user.username == username) {
                username_ada = true; // Username sudah ada dalam vektor users
                cout << WARNA_MERAH <<"[ERROR] : " << WARNA_RESET << " Username sudah digunakan. Silakan coba lagi." << endl;
                break; // Hentikan iterasi karena username sudah ditemukan
            }
        }

        if (!username_ada) {
            for (const Cabang &cabang : cabangs) {
                if (cabang.username == username) {
                    username_ada = true; 
                    cout << WARNA_MERAH <<"[ERROR] : " << WARNA_RESET << " Username sudah digunakan. Silakan coba lagi." << endl;
                    break; // Hentikan iterasi karena username sudah ditemukan
                }
            }
        }
    } while (username_ada);

    cout << BOLD  << " \u2022 Masukkan Password >>  ";
    cin >> password;
	
    users.push_back({username, password, "pelanggan", 0});
    cout << WARNA_HIJAU << "[BERHASIL] : " << WARNA_RESET << " Registrasi "<< WARNA_HIJAU+BOLD << "berhasil " << WARNA_RESET << "sebagai pelanggan."<< WARNA_RESET << endl;
    Fitur_pause_layar();
}


bool Proses_Login(int cabangChoice) {
	const char BACKSPACE = 8;
    const char ENTER = 13;
    char ch = ' ';
	cout << WARNA_BIRU << BOLD  << "==============================================" << endl;
    cout << "|           Selamat datang di Warmindo        |" << endl;
    cout << "==============================================" << WARNA_RESET << endl;
    string username, password;

    cout << BOLD  << " \u2022 Masukkan Username >>  ";
    cin >> username;

    cout << BOLD << " \u2022 Masukkan Password >>  ";
    while (true) {
        ch = _getch();  // Menggunakan _getch() untuk membaca karakter tanpa menampilkan di layar

        if (ch == ENTER) {
            break;  // Keluar dari loop jika tombol Enter ditekan
        } else if (ch == BACKSPACE) {
            if (password.length() > 0) {
                cout << "\b \b";  // Hapus karakter terakhir dari layar
                password.pop_back();  // Hapus karakter terakhir dari string password
            }
        } else {
            password += ch;  // Tambahkan karakter ke string password
            cout << '*';  // Tampilkan karakter pengganti (bisa diganti dengan karakter lain jika diinginkan)
        }
    }

 

    User* loggedInUser = nullptr;

    // Cari pengguna dengan username dan password yang cocok
    for (User& user : users) {
        if (user.username == username && user.password == password) {
            loggedInUser = &user;
            break;
        }
    }

    // Cek apakah pengguna adalah admin cabang yang sesuai dengan pilihan cabang
    if (loggedInUser) {
        // Pengguna bukan admin cabang, lanjutkan proses login
        cout << WARNA_BIRU <<"\n\n===================================================" << endl;
	   	cout << "|          Terima kasih, " << BOLD << WARNA_RESET << setw(25) << username << WARNA_BIRU  <<  "|" << endl;
	    cout << "|         Login berhasil. Selamat datang!         |" << endl;
    	cout << "===================================================" << WARNA_RESET << endl;
        cout << BOLD << WARNA_HIJAU  << "[BERHASIL] : " << WARNA_RESET << "Login" << BOLD << WARNA_HIJAU <<  " berhasil " << WARNA_RESET << "sebagai " << BOLD << loggedInUser->role <<endl;
        currentUser = loggedInUser; // Atur currentUser sesuai pengguna yang saat ini login
        Fitur_pause_layar();
        return true;
    } else {
        for (Cabang& cabang : cabangs) {
            if (cabang.id_cabang == cabangChoice && cabang.username == username && cabang.password == password) {
                currentAdminCabang = &cabang;
                cout << WARNA_BIRU <<"\n\n===================================================" << endl;
			   	cout << "|          Terima kasih, " << BOLD << WARNA_RESET << setw(25) << username << WARNA_BIRU  <<  "|" << endl;
			    cout << "|         Login berhasil. Selamat datang!         |" << endl;
		    	cout << "===================================================" << WARNA_RESET << endl;
                cout << BOLD << WARNA_HIJAU  << "[BERHASIL] : "<< WARNA_RESET << " Login "<< WARNA_HIJAU+BOLD << "berhasil "<< WARNA_RESET << "sebagai Admin Cabang" << endl;
                Fitur_pause_layar();
				return true;
                
            } else if (cabang.id_cabang != cabangChoice && cabang.username == username && cabang.password == password) {
                cout << "\n" << WARNA_MERAH << "[ERROR] : \033[37m:Kamu bukan pemilik cabang, " << WARNA_MERAH + BOLD << "akses ditolak!" << WARNA_RESET << endl;
                Fitur_pause_layar();
                return false;
            }
        }
    }

   	cout << "\n" << WARNA_MERAH << "[ERROR] : \033[37m: Login Gagal, periksa kembali Username dan Password." << WARNA_RESET << endl;
   	Fitur_pause_layar();
    return false;
}





/*
Menu Utama, 

Pada awal program akan ditanya terlebih ingin melakukan kegiatan penjualan ini di cabang apa, jika sudah memilih 
cabang maka Akan menampilkan kamu sedang dicabang apa. Dan setelah itu melakukan login yang dimana jika memasukkan username dan password yang tepat,
akan diarahkan ke menu tampilan peran/role masing masing.

Jika memilih angka 1 akan diarahkan ke tampilan untuk login, 
Jika memilih angka 2 akan diarahkan ke tampilan untuk Register/Daftar,
Jika memilih 3 maka akan keluar program.


Pada Struct Cabang() akan memiliki peran saat dipilih cabangnya, karena saat login hanya admin dari cabang tersebut saja bisa login.


Fitur :
 - Pada Line 1494, ini adalah cara untuk terminalnya bisa support menggunakan ANSI ataupun UNICODE lainnya agar bisa menggunakan simbol.
	#include windows.h adalah librarynya agar bisa menggunakan sintaks tersebut.
	
	

- Pada Line 1495, Itu membaca isi dari file menu.txt agar bisa mendapatkan data untuk di tampilkan maupun di modifikasi.

- setw() ini berfungsi sebagai mengatur jarak atau lebar dari whitespace dan ini menggunakan library #include <iomanip>


Error Handling :

- Jika salah dalam memilih cabang yang ingin dipilih maka akan dilakukan perulang sampai cabang yang dipilih benar.
- Jika memilih menu yang salah pada menu utama menggunakan huruf, maka akan dilakukan perulangan untuk memilih menu yang benar(true) menggunakan integer/bilangan bulat.
- Jika memilih menu yang diluar dari pilihan menu, maka akan dilakukan perulangan untuk memilih menu yang benar(true).
*/


int main() {
	SetConsoleOutputCP(CP_UTF8);

	
    File_Baca();
    //Data Statis Akun Pelanggan dan Kasir    
    users.push_back({ "pebri", "123", "kasir", 0 });
    users.push_back({ "p", "123", "pelanggan", 0 });
	
	//Data Statis Akun Admin Cabang
    cabangs.push_back({ 1, "Warmindo Jl Elang", "alip", "123", "admin" });
    cabangs.push_back({ 2, "Warmindo Awang Syahrani", "ucup", "123", "admin" });

    int menuChoice = 0;

    // Pilih cabang sebelum login
    int cabangChoice = 0;
    
    while (true) {
    	Fitur_bersihkan_layar();
    	cout << WARNA_RESET+BOLD << "Pilih cabang Anda:" << endl;
	     cout << "+----+-----------------------------+" << endl;
        cout << "| " << setw(2) << BOLD << "No" << setw(3) << "| " << setw(13) << BOLD << "Nama Cabang" << WARNA_RESET << "        |" << endl;
        cout << "+----+-----------------------------+" << endl;

        for (int i = 0; i < cabangs.size(); i++) {
            cout << "| " << setw(2) << i + 1 << " | " << setw(25) << cabangs[i].nama_cabang << "   |" << endl;
        }
        cout << "+----+-----------------------------+" << endl;
    	cout << "Pilihan: ";
    	cin >> cabangChoice;
    	if (cin.fail()) {
			cout << "\n" << WARNA_MERAH << "[ERROR] : " << WARNA_RESET << ": Hanya angka!" << WARNA_RESET << endl;
            cin.clear();
            Fitur_pause_layar();
            continue;
        }
    	if (cabangChoice >= 1 && cabangChoice <= cabangs.size()) {
        currentAdminCabang = &cabangs[cabangChoice - 1];
        cout << "\n" << BOLD << WARNA_HIJAU  << "[BERHASIL] : "<< WARNA_RESET << " Telah memilih "<< WARNA_HIJAU+BOLD << "cabang "<< WARNA_RESET << currentAdminCabang->nama_cabang << endl;
        Fitur_pause_layar();
        break;
    } else {
        cout << "\n" << WARNA_MERAH << "[ERROR] : "<< WARNA_RESET << ":Pilihan cabang tidak valid!" << WARNA_RESET << endl;
        Fitur_pause_layar();
        continue;
    }
	}

    
	
    while (menuChoice != 3) {
    Fitur_bersihkan_layar();	
    int namaCabangWidth = 30; 
    cout << WARNA_HIJAU << BOLD << "+=========================================================+" << endl;
    cout << "|              Selamat datang di Warmindo                 |" << endl;
    cout << "|          Cabang : " << left << WARNA_RESET <<setw(namaCabangWidth) << currentAdminCabang->nama_cabang << WARNA_HIJAU << BOLD << "        |" << endl;
    cout << "+=========================================================+" << WARNA_HIJAU << endl;
	cout << "|" << setw(24) << WARNA_KUNING + BOLD << "1." << BOLD << "Login" << WARNA_HIJAU << "                                   |" << endl;
    cout << "|" << setw(20) << WARNA_KUNING << "2." << BOLD << "Register" << WARNA_HIJAU << "                                |" << endl;
    cout << "|" << setw(20) << WARNA_KUNING << "3."<<  BOLD << "Keluar Program" << WARNA_HIJAU << "                          |" << endl;
    cout << WARNA_HIJAU + BOLD << "+=========================================================+" << WARNA_RESET << endl;
    cout << WARNA_KUNING + BOLD << "\n>> Pilihan: " << WARNA_RESET;
    cin >> menuChoice;
        
		if (cin.fail()) {
			cout << "\n" << WARNA_MERAH << "[ERROR] : " << WARNA_RESET << ": Hanya angka!" << WARNA_RESET << endl;
            cin.clear();
            Fitur_pause_layar();
            continue;
        }
        
        if (menuChoice == 1) {
        	Fitur_bersihkan_layar();
            bool loggedIn = Proses_Login(cabangChoice);
            if (loggedIn) {
                if (currentUser != NULL) {
                    if (currentUser->role == "kasir") {
                        bool backToMain = false;
                        while (!backToMain) {
                            backToMain = Tampilan_Kasir();
                        }
                    } else if (currentUser->role == "pelanggan") {
                        bool backToMain = false;
                        while (!backToMain) {
                            backToMain = Tampilan_Pelanggan();
                        }
                    }
                } else if (currentAdminCabang) {
                    bool backToMain = false;
                    while (!backToMain) {
                        backToMain = Tampilan_Admin();
                    }
                }
            }
        } else if (menuChoice == 2) {
            Proses_Daftar();
            
		
        } else if(menuChoice == 3) {
			cout << "\n" << WARNA_MERAH << "[EXIT] "<< WARNA_RESET << ": Keluar Program."  <<endl;
			Fitur_pause_layar();
		}
		else {
        	cout << "\n" << WARNA_MERAH << "[ERROR] "<< WARNA_RESET << ": Pilihan Tidak Valid." <<endl;
        	Fitur_pause_layar();
		}
    }

    return 0;
}
