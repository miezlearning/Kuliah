#include <iostream>    // Header untuk input-output standar C++
#include <string>      // Header untuk manipulasi string
#include <vector>      // Header untuk menggunakan vektor khsuusnya pada struct untuk CRUD
#include <fstream>     // Header untuk operasi file
#include <sstream>     // Header untuk manipulasi string stream
#include <iomanip>     // Header untuk manipulasi output, seperti setw
#include <conio.h>     // Header untuk fungsi getch(), berfungsi untuk membaca input tanpa menekan Enter
#include <windows.h>   // Header untuk fungsi-fungsi khusus Windows, seperti manipulasi kursor dan warna teks

// Ini adalah library penting untuk slide text
#include <chrono>      // Header untuk waktu dan durasi
#include <thread>      // Header untuk mengatur thread (menunda eksekusi)



using namespace std;


// Struktur data untuk merepresentasikan Menu, Cabang, dan User
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


// Variabel global dan pointer untuk mengelola pesanan dan menu
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


Cabang* currentAdminCabang = NULL; // Pointer ke admin cabang saat ini
vector<User> users; // Vector untuk menyimpan informasi pengguna
vector<Cabang> cabangs; // Vector untuk menyimpan informasi cabang
Menu* menu = NULL;

User* currentUser = NULL; 
	
// Daerah Fungsi Utama pada program.

// Fungsi untuk membersihkan layar terminal
void Fitur_bersihkan_layar() {
	system("cls");
}

// Fungsi untuk memberhentikan layar dan menunggu input pengguna
void Fitur_pause_layar() {
	cout << "\n"<< WARNA_P <<"[BACK] : "<< WARNA_RESET+BOLD <<" Tekan enter untuk melanjutkan..." << WARNA_RESET  << endl;
    cin.ignore(1000, '\n');
    cin.get();
    Fitur_bersihkan_layar();
}


/*
Deskripsi Fungsi enqueue:

Fungsi ini digunakan untuk menambahkan pesanan ke dalam antrian.

Parameter:
- Pesanan** front: Pointer ke depan antrian.
- Pesanan** rear: Pointer ke belakang antrian.
- Pesanan* pesanan: Pointer ke pesanan yang akan ditambahkan.

Langkah-langkah:
1. Cek apakah rear (belakang antrian) kosong.
   - Jika kosong, artinya antrian masih kosong. Set front (depan antrian) ke pesanan.
   - Jika tidak kosong, artinya antrian sudah ada. Hubungkan pesanan ke belakang antrian.
2. Update rear (belakang antrian) ke pesanan baru.

---

Deskripsi Fungsi dequeue:

Fungsi ini digunakan untuk menghapus pesanan dari depan antrian.

Parameter:
- Pesanan** front: Pointer ke depan antrian.
- Pesanan** rear: Pointer ke belakang antrian.

Langkah-langkah:
1. Cek apakah front (depan antrian) kosong.
   - Jika kosong, tampilkan pesan bahwa antrian kosong dan kembali dari fungsi.
2. Buat pointer sementara temp untuk menyimpan pesanan pada depan antrian.
3. Cek apakah pesanan pada depan antrian milik pengguna yang sedang login.
   - Jika iya, hapus pesanan dari depan antrian.
   - Jika tidak, tampilkan pesan bahwa pengguna tidak memiliki pesanan dalam antrian.
4. Update front (depan antrian) ke pesanan berikutnya setelah yang dihapus.
5. Jika setelah penghapusan antrian menjadi kosong, update rear (belakang antrian) menjadi NULL.

Catatan:
- Fungsi ini diimplementasikan untuk manajemen antrian pesanan, khususnya untuk pengguna yang sedang login.
- Pada dequeue, pesanan dihapus hanya jika milik pengguna yang sedang login.
- Antrian diimplementasikan sebagai linked list dengan setiap pesanan memiliki pointer ke pesanan berikutnya.
*/

// Fungsi untuk menambahkan pesanan ke dalam antrian
void enqueue(Pesanan** front, Pesanan** rear, Pesanan* pesanan) {
    if (*rear == NULL) {
        *front = pesanan;
    } else {
        (*rear)->next = pesanan;
    }
    *rear = pesanan;
}


// Fungsi untuk menghapus pesanan dari antrian
void dequeue(Pesanan** front, Pesanan** rear) {
    if (*front == NULL) {
        cout << WARNA_P + BOLD << "[NULL] : " <<WARNA_RESET << "Antrian kosong." << endl;
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
        cout << WARNA_P + BOLD << "[NULL] : "<< WARNA_RESET <<" Anda tidak memiliki pesanan dalam antrian." << endl;
    }
}


/*
Deskripsi Fungsi File_Baca:

Fungsi ini bertugas untuk membaca informasi menu dari file "menu.txt" dan menginisialisasi array menu dengan data yang dibaca.

Langkah-langkah:
1. Buka file "menu.txt" untuk membaca (ifstream).
2. Cek apakah file berhasil dibuka.
   - Jika berhasil, lanjut ke langkah berikutnya.
   - Jika gagal, tampilkan pesan error dan keluar dari fungsi.
3. Baca jumlah menu dari baris pertama file dan simpan dalam variable menuSize.
4. Cek apakah array menu sudah terisi sebelumnya, jika iya, bebaskan memori.
5. Alokasikan ulang array menu dengan ukuran sesuai dengan jumlah menu (menuSize).
6. Loop untuk membaca setiap detail menu dari file dan menyimpannya ke dalam array menu.
   - Format: id_menu, nama, kategori, harga
7. Tutup file setelah selesai membaca data.

Catatan:
- Fungsi ini diimplementasikan untuk membaca menu dari file "menu.txt".
- Data menu disimpan dalam format teks di file.
- Setiap menu memiliki informasi seperti id_menu, nama, kategori, dan harga.
- Jumlah menu dan detail setiap menu dibaca dari file untuk menginisialisasi array menu.
*/
void File_Baca() {
    // Cek, kita lagi buka file "menu.txt" nih
    ifstream file("menu.txt");

    // Kalo berhasil dibuka, lanjut baca isinya
    if (file.is_open()) {
        // Baca jumlah menu dulu dari baris paling atas file
        file >> menuSize;

        // Cek, kalo menu nggak kosong, kita bersihin dulu
        if (menu != NULL) {
            delete[] menu;
        }

        // Nah, kita alokasi ulang array buat menu sesuai jumlahnya
        menu = new Menu[menuSize];

        // Lanjut baca setiap detail menu satu-satu
        for (int i = 0; i < menuSize; i++) {
            file >> menu[i].id_menu;
            file.ignore();  // Biar bisa baca koma dan spasi
            getline(file, menu[i].nama, ',');  // Baca nama menu
            getline(file, menu[i].kategori, ',');  // Baca kategori menu
            file >> menu[i].harga;  // Baca harga menu
        }

        // Udah selesai baca, kita tutup file-nya ya
        file.close();
    } else {
        // Kalo gagal buka file, kita kasih tau nih error-nya
       cout << WARNA_MERAH << BOLD << "[ERROR] : "<< WARNA_RESET << " Gagal membuka berkas menu.txt. " << endl;
    }
}


// Fungsi untuk menyimpan informasi menu ke dalam file
/*
Deskripsi Fungsi File_Simpan_Menu:

Fungsi ini bertugas untuk menyimpan informasi menu ke dalam file "menu.txt". Data menu disimpan dalam format teks di file.

Langkah-langkah:
1. Buka file "menu.txt" untuk penulisan (ofstream).
2. Cek apakah file berhasil dibuka.
   - Jika berhasil, lanjut ke langkah berikutnya.
   - Jika gagal, tampilkan pesan error dan keluar dari fungsi.
3. Tulis jumlah menu (menuSize) ke dalam file sebagai baris pertama.
4. Loop untuk menulis setiap detail menu ke dalam file.
   - Format: id_menu, nama, kategori, harga
5. Tutup file setelah selesai menyimpan data.

Catatan:
- Fungsi ini diimplementasikan untuk menyimpan menu dalam format teks di file.
- Array menu digunakan untuk menyimpan informasi setiap menu.
- Setiap menu memiliki informasi seperti id_menu, nama, kategori, dan harga.
- File "menu.txt" akan berisi data menu yang dapat digunakan untuk memulihkan daftar menu.
*/
void File_Simpan_Menu() {
    // Kita buka file-nya dulu nih, "menu.txt" yang bakal jadi rumahnya data menu.
    ofstream file("menu.txt");

    // Cek dulu, nih, apakah file-nya kebuka atau nggak.
    if (file.is_open()) {
        // Nah, kita tulis dulu jumlah menu yang kita punya di baris pertama.
        file << menuSize << endl;

        // Loop  buat nulis setiap detail menu ke file.
        for (int i = 0; i < menuSize; i++) {
            file << menu[i].id_menu << ", " << menu[i].nama << ", " << menu[i].kategori << ", " << menu[i].harga << endl;
        }

        // Udah selesai, kita tutup lagi file-nya.
        file.close();
    } else {
        // Kalo gagal buka file, ya kita tampilin pesan errornya biar pada tau.
        cout << WARNA_MERAH << BOLD << "[ERROR] : "<< WARNA_RESET << " Gagal membuka berkas menu.txt. Coba cek lagi ya, mungkin file nggak ada." << endl;
    }
}




// Fungsi buat save pesenan ke file teks "pesanan.txt"
/*
Deskripsi Fungsi File_Simpan_Pesanan:

Fungsi ini digunakan untuk menyimpan informasi pesanan ke dalam file "pesanan.txt". Data pesanan disimpan dalam format teks di file.

Langkah-langkah:
1. Buka file "pesanan.txt" untuk penulisan (ofstream).
2. Cek apakah file berhasil dibuka.
   - Jika berhasil, lanjut ke langkah berikutnya.
   - Jika gagal, tampilkan pesan error dan keluar dari fungsi.
3. Gunakan pointer (JalanJalan) untuk mengiterasi melalui linked list pesanan, dimulai dari simpul awal (depan).
   - Simpan informasi setiap pesanan ke dalam file "pesanan.txt".
4. Tutup file setelah selesai menyimpan data.

Catatan:
- Fungsi ini diimplementasikan untuk menyimpan pesanan dalam format teks di file.
- Linked list Pesanan digunakan untuk menyimpan pesanan secara dinamis.
- Setiap pesanan memiliki informasi seperti orderID, nama_pelanggan, id_menu, jumlah, total_harga, dan dikonfirmasi.
- File "pesanan.txt" akan berisi data pesanan yang dapat digunakan untuk memulihkan status pesanan.
*/

void File_Simpan_Pesanan(Pesanan* depan) {
    // Buka file "pesanan.txt" buat nulis
    ofstream file("pesanan.txt");

    // Cek apakah file berhasil dibuka
    if (file.is_open()) {
        // Pointer Jalan-Jalan buat muterin linked list pesenan, mulai dari simpul awal (depan)
        Pesanan* JalanJalan = depan;

        // Jalanin satu-satu pesenan yang ada
        while (JalanJalan != NULL) {
            // Simpen info pesenan ke file
            file << JalanJalan->orderID << " "
                 << JalanJalan->nama_pelanggan << " "
                 << JalanJalan->id_menu << " "
                 << JalanJalan->jumlah << " "
                 << JalanJalan->total_harga << " "
                 << JalanJalan->dikonfirmasi << endl;

            // Jalan ke pesenan berikutnya dalam daftar
            JalanJalan = JalanJalan->next;
        }

        // Tutup file setelah selesai nyimpen data
        file.close();
    } else {
        // Kasih tau kalo gagal buka file
        cout << WARNA_MERAH << BOLD << "[ERROR] : "<< WARNA_RESET << " Gagal buka file pesanan.txt" << endl;
    }
}


// Akhir Daerah Fungsi Utama pada program.

// Daerah Searching Booyer moore untuk Kategori
/*
Deskripsi Fungsi Searching_BM_Kategori:

Fungsi ini mengimplementasikan algoritma Boyer-Moore untuk mencari pola (pattern) dalam teks (text). Algoritma ini digunakan untuk mencari kategori menu berdasarkan nama kategori.

Parameter:
- text: String teks tempat pencarian dilakukan.
- pattern: String pola yang dicari dalam teks.

Langkah-langkah Algoritma Boyer-Moore:
1. Inisialisasi variabel m dan n sebagai panjang pola dan teks.
2. Buat array badchar dengan ukuran 256 dan inisialisasi semua elemennya dengan -1.
3. Isi array badchar dengan indeks karakter dalam pola dan posisi karakter tersebut.
4. Inisialisasi variabel s (start) sebagai indeks awal untuk pencarian dalam teks.
5. Lakukan loop pencarian selama s <= (n - m):
   a. Lakukan pencocokan karakter dari belakang pola ke teks.
   b. Jika pencocokan berhasil (j < 0), kembalikan posisi awal s sebagai hasil.
   c. Jika pencocokan gagal, geser indeks pencarian s sejauh maksimum antara 1 dan (j - badchar[(int)text[s + j]]).

Hasil:
- Jika pencocokan ditemukan, fungsi mengembalikan posisi awal pencocokan dalam teks.
- Jika pencocokan tidak ditemukan, fungsi mengembalikan -1.

Catatan:
- Algoritma Boyer-Moore digunakan untuk meningkatkan efisiensi pencarian pola dalam sebuah teks.
- Fungsi ini dapat membantu dalam mencari kategori menu berdasarkan nama kategori.
*/
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
/*
Deskripsi Fungsi merge dan mergeSort:

Fungsi merge:
- Menerima array menu (arr), indeks awal (l), indeks tengah (m), indeks akhir (r), dan parameter boolean (ascending) untuk menentukan pengurutan naik/turun berdasarkan harga.
- Menggabungkan dua subarray yang sudah diurutkan menjadi satu array utama.
- Membandingkan nilai harga untuk menentukan urutan penggabungan.

Fungsi mergeSort:
- Menerima array menu (arr), indeks awal (l), indeks akhir (r), dan parameter boolean (ascending) untuk menentukan pengurutan naik/turun berdasarkan harga.
- Menggunakan algoritma Merge Sort untuk mengurutkan array menu berdasarkan harga.
- Rekursif membagi array menjadi dua bagian, kemudian menggabungkan kembali setelah diurutkan.

Langkah-langkah algoritma Merge Sort:
1. Jika indeks awal (l) kurang dari indeks akhir (r):
   a. Temukan indeks tengah (m) dari array.
   b. Rekursif panggil mergeSort untuk dua bagian array, yaitu dari indeks awal ke indeks tengah dan dari indeks tengah+1 ke indeks akhir.
   c. Panggil fungsi merge untuk menggabungkan dua bagian yang sudah diurutkan.

Hasil:
- Setelah pemanggilan mergeSort, array menu akan terurut berdasarkan harga sesuai parameter boolean (ascending).
- Fungsi merge digunakan untuk menggabungkan dua subarray yang sudah diurutkan.

Catatan:
- Merge Sort adalah algoritma pengurutan yang efisien dan stabil.
- Dalam konteks ini, digunakan untuk mengurutkan menu berdasarkan harga.
*/

void merge(Menu arr[], int l, int m, int r, bool ascending) {
    // Menghitung ukuran dua subarray yang akan digabungkan
    int n1 = m - l + 1;
    int n2 = r - m;

    // Membuat dua array sementara untuk menyimpan data subarray
    Menu L[n1], R[n2];

    // Menyalin data ke dalam array sementara L[] dan R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Inisialisasi indeks awal untuk subarray yang akan digabungkan
    int i = 0, j = 0, k = l;

    // Menggabungkan dua subarray ke dalam array utama arr[]
    while (i < n1 && j < n2) {
        // Membandingkan nilai harga untuk pengurutan
        if ((ascending && L[i].harga <= R[j].harga) || (!ascending && L[i].harga >= R[j].harga)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Menyalin sisa elemen jika ada dari L[], jika ada
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Menyalin sisa elemen jika ada dari R[], jika ada
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Fungsi yang mengimplementasikan algoritma Merge Sort untuk menu berdasarkan harga
void mergeSort(Menu arr[], int l, int r, bool ascending) {
    if (l < r) {
        // Menemukan titik tengah array
        int m = l + (r - l) / 2;

        // Memanggil rekursif mergeSort untuk dua bagian array
        mergeSort(arr, l, m, ascending);
        mergeSort(arr, m + 1, r, ascending);

        // Menggabungkan dua bagian yang sudah diurutkan
        merge(arr, l, m, r, ascending);
    }
}



// Akhir Daerah Merge Sort Untuk Harga


// Daerah Menu Pelanggan
// Fungsi untuk pelanggan menambahkan pesanan ke dalam antrian
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

// Fungsi untuk menampilkan pesanan pelanggan
void Pesanan_Tampilkan() {
    // Mengecek apakah daftar pesanan kosong
    if (front == NULL) {
        cout << WARNA_P << BOLD << "[NULL] : " << WARNA_RESET << "Anda belum memiliki pesanan." << endl;
    } else {
        // Menampilkan header tabel
        cout << "+---------------------------------------------------------------------------------------------------------------+" << endl;
        cout << "| " << setw(10) << "ID Pesanan" << " | " << setw(20) << "Nama Menu" << " | " << setw(15) << "Harga (Rp)" << " | "
             << setw(10) << "Jumlah" << " | " << setw(20) << "Total Harga (Rp)" << " | " << setw(15) << "Status" << "     |" << endl;
        cout << "+---------------------------------------------------------------------------------------------------------------+" << endl;

        // Traversal digunakan untuk melewati setiap node pesanan
        Pesanan* Traversal = front;
        double totalHargaPesanan = 0;

        // Iterasi melalui setiap pesanan
        while (Traversal != NULL) {
            // Memeriksa apakah pesanan milik pengguna yang saat ini login
            if (Traversal->nama_pelanggan == currentUser->username) {
                const Menu* menuToDisplay = NULL;

                // Mencari menu yang sesuai dengan ID pesanan
                for (int i = 0; i < menuSize; i++) {
                    if (menu[i].id_menu == Traversal->id_menu) {
                        menuToDisplay = &menu[i];
                        break;
                    }
                }

                // Menampilkan detail pesanan
                totalHargaPesanan += Traversal->total_harga;
                cout << "| " << setw(10) << Traversal->orderID << " | " << setw(20) << menuToDisplay->nama << " | " << setw(15) << menuToDisplay->harga << " | "
                     << setw(10) << Traversal->jumlah << " | " << setw(20) << Traversal->total_harga << " | " << setw(10) << (Traversal->dikonfirmasi ? "Dikonfirmasi" : "Belum dikonfirmasi") << "|" << endl;
            }
            Traversal = Traversal->next; // Pindah ke pesanan berikutnya
        }

        // Menampilkan total harga pesanan jika ada pesanan
        if (totalHargaPesanan > 0) {
            cout << "+---------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "| " << setw(3) << "Total Harga Semua Pesanan:" << setw(5) << "Rp " << totalHargaPesanan << right << endl;
            cout << "+---------------------------------------------------------------------------------------------------------------+" << endl;
        } else {
            // Pesan jika pengguna tidak memiliki pesanan
            cout << WARNA_P << BOLD << "[NULL] : " << WARNA_RESET << "Anda belum memiliki pesanan." << endl;
        }
    }
}


// Fungsi untuk pelanggan membayar pesanan
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

// Fungsi untuk menampilkan item menu berdasarkan kategori tertentu
void Menu_Tampilkan_Berdasarkan_Kategori(const string& kategori) {
    // Membaca data dari file
    File_Baca();

    // Mengecek apakah daftar menu kosong
    if (menuSize == 0) {
        cout << WARNA_P << "[NULL] : " << WARNA_RESET << "Tidak ada menu yang tersedia." << endl;
    } else {
        bool found = false;

        // Menampilkan header tabel
        cout << "+-----+-----------------------+-------------+---------------------+" << endl;
        cout << "| ID  | Nama                  | Harga (Rp)  | Kategori            |" << endl;
        cout << "+-----+-----------------------+-------------+---------------------+" << endl;

        // Iterasi melalui setiap menu
        for (int i = 0; i < menuSize; i++) {
            // Mengecek apakah menu sesuai dengan kategori yang dicari
            if (Searching_BM_Kategori(menu[i].kategori, kategori) != -1) {
                found = true;
                // Menampilkan detail menu yang sesuai dengan kategori
                cout << "| " << setw(2) << left << menu[i].id_menu << "  | " << right << setw(21) << menu[i].nama << " | " << setw(11) << right << menu[i].harga << " | " << setw(19) << menu[i].kategori << " |" << endl;
            }
        }

        // Menampilkan pesan jika tidak ada menu dengan kategori yang dicari
        if (!found) {
            cout << "Menu dengan kategori '" << kategori << "' tidak ditemukan." << endl;
        }

        // Menampilkan penutup tabel
        cout << "+-----+-----------------------+-------------+---------------------+" << endl;
    }
}


// Fungsi untuk pelanggan menambahkan saldo mereka
void topUpSaldo() {
    // Mendeklarasikan variabel untuk jumlah top-up saldo
    int topUp_JumlahSaldo;
    
    // Meminta pengguna untuk memasukkan jumlah top-up
    cout << "\u2022 Masukkan jumlah top-up >>  Rp. ";
    cin >> topUp_JumlahSaldo;

    // Memeriksa apakah jumlah top-up valid
    if (topUp_JumlahSaldo <= 15000) {
        // Menambahkan jumlah top-up ke saldo pengguna
        currentUser->saldo += topUp_JumlahSaldo;

        // Menampilkan pesan berhasil jika top-up berhasil
        cout << WARNA_HIJAU + BOLD << "[BERHASIL] : "<< WARNA_RESET + BOLD << " Top-up berhasil. Saldo Anda sekarang: Rp " << currentUser->saldo << endl;
    } else {
        // Menampilkan pesan kesalahan jika jumlah top-up melebihi batas maksimal yaitu 15000
        cout << WARNA_MERAH + BOLD << "[ERROR] : "<< WARNA_RESET + BOLD << " Jumlah top-up tidak valid. Maksimal "<< WARNA_MERAH + BOLD << "Rp 15,000. "<< WARNA_RESET + BOLD << " Silakan coba lagi." << endl;
    }
}



// Fungsi untuk pelanggan menampilkan saldo mereka
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

// Fungsi untuk mengonfirmasi pesanan oleh kasir
void Pesanan_Konfirmasi(Pesanan** front) {
    if (*front == NULL) {
        cout << WARNA_P << BOLD << "[NULL] : "<<WARNA_RESET<<"Tidak ada pesanan yang perlu dikonfirmasi." << endl;
        return;
    }

    Pesanan* pesanan = *front;
    bool pesananDitemukan = false;
	
	 // Mencari pesanan yang belum dikonfirmasi
    while (pesanan != NULL && pesanan->dikonfirmasi) {
        pesanan = pesanan->next;
    }
	
	// Jika semua pesanan sudah dikonfirmasi
    if (pesanan == NULL) {
        cout << WARNA_P << BOLD << "[NULL] : "<<WARNA_RESET<<"Tidak ada pesanan yang perlu dikonfirmasi." << endl;
        return;
    }
	
	// Menampilkan pesanan yang belum dikonfirmasi
    cout << "+---------+------------------------+----------+--------+--------------+" << endl;
    cout << "| OrderID | Nama Pelanggan         | Menu ID  | Jumlah | Total Harga  |" << endl;
    cout << "+---------+------------------------+----------+--------+--------------+" << endl;

    cout << "|" << setw(8) << pesanan->orderID << " | " << setw(23) << pesanan->nama_pelanggan
         << " | " << setw(8) << pesanan->id_menu << " | " << setw(6) << pesanan->jumlah
         << " | Rp " << setw(11) << pesanan->total_harga << " |" << endl;
    cout << "+---------+------------------------+----------+--------+--------------+" << endl;
	
	// Meminta konfirmasi dari kasir
    char choice;
    cout << WARNA_KUNING << BOLD << "[KONFIRMASI] : "<< WARNA_RESET << " Apakah kamu yakin mengkonfirmasi pesanan ini "<< WARNA_P << BOLD << "(Y/N)? " << WARNA_RESET;
    cin >> choice;
	
	// Jika kasir yakin mengkonfirmasi pesanan
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

// Fungsi untuk menampilkan semua pesanan yang belum dikonfirmasi
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

// Fungsi untuk menampilkan menu sebelum dan setelah diurutkan berdasarkan harga
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



/*
Deskripsi Fungsi Menu_Buat:

Fungsi ini digunakan untuk menambahkan menu baru ke dalam array menu.

Langkah-langkah:
1. Memuat menu dari file menu.txt menggunakan fungsi File_Baca.
2. Meminta pengguna untuk memasukkan nama menu baru dengan melakukan validasi agar tidak kosong.
3. Meminta pengguna untuk memasukkan kategori menu baru dengan melakukan validasi agar tidak kosong.
4. Meminta pengguna untuk memasukkan harga menu baru dengan validasi agar merupakan angka positif.
5. Membuat array baru (newMenu) untuk menyimpan menu yang sudah ada dan menu baru.
6. Mengcopy data menu yang sudah ada ke dalam array baru.
7. Menambahkan data menu baru ke dalam array baru.
8. Menambahkan ukuran menuSize.
9. Menghapus array menu yang lama.
10. Menunjukkan array menu ke array baru.
11. Menyimpan perubahan ke dalam file menu.txt menggunakan fungsi File_Simpan_Menu.
12. Menampilkan pesan bahwa menu baru berhasil ditambahkan.

Catatan:
- Fungsi ini berfokus pada penambahan menu baru dengan meminta input pengguna.
- Melibatkan validasi input untuk memastikan data yang dimasukkan sesuai.
- Melibatkan pembacaan dan penulisan file menu.txt untuk mempertahankan data di antara sesi program.
*/

// Fungsi untuk menambahkan menu baru
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

    File_Simpan_Menu(); // Menyimpan perubahan ke dalam file menu.txt
    cout << WARNA_HIJAU << BOLD << "[BERHASIL] : "<< WARNA_RESET << BOLD << " Menu baru  "<<WARNA_HIJAU << BOLD << "berhasil ditambahkan."<< WARNA_RESET << BOLD  << endl;
}

// Fungsi untuk mengubah informasi menu yang sudah ada
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
    
    
    // Mencari menu berdasarkan ID
    for (int i = 0; i < menuSize; i++) {
        if (menu[i].id_menu == idToUpdate) {
        	// Meminta input pengguna untuk mengubah informasi menu
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


/*
Deskripsi Fungsi Menu_Hapus:

Fungsi ini digunakan untuk menghapus menu berdasarkan ID dari array menu.

Langkah-langkah:
1. Memuat menu dari file menu.txt menggunakan fungsi File_Baca.
2. Menampilkan daftar menu menggunakan fungsi Menu_Tampilkan.
3. Meminta pengguna untuk memasukkan ID menu yang ingin dihapus.
4. Mencari index menu yang akan dihapus berdasarkan ID yang dimasukkan.
5. Jika ID menu ditemukan, menggeser elemen menu ke posisi sebelumnya untuk menutupi menu yang dihapus.
6. Mengurangi ukuran menuSize.
7. Memperbarui ID menu setelah menghapus menu.
8. Membuat array baru (newMenu) untuk menyimpan menu yang sudah diperbarui.
9. Mengcopy data menu yang sudah diperbarui ke dalam array baru.
10. Menghapus array menu yang lama.
11. Menunjukkan array menu ke array baru.
12. Menyimpan perubahan ke dalam file menu.txt menggunakan fungsi File_Simpan_Menu.
13. Menampilkan pesan bahwa menu berhasil dihapus.

Catatan:
- Fungsi ini berfokus pada penghapusan menu berdasarkan ID yang dimasukkan pengguna.
- Melibatkan validasi untuk memastikan ID yang dimasukkan sesuai dengan menu yang ada.
- Melibatkan pembacaan dan penulisan file menu.txt untuk mempertahankan data di antara sesi program.
*/

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

// Menampilkan daftar akun pelanggan dengan format tertentu
// (Username dan Saldo)
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

// Menampilkan pilihan tampilan akun (Pelanggan, Kasir, Semua Akun)
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

// Meminta input untuk membuat akun baru (Username, Password, Role, Saldo)
// Meminta input untuk membuat akun baru (Username, Password, Role, Saldo)
void Admin_Tambah_Akun() {
    // Membuat objek baru untuk menyimpan data pengguna baru
    User Pengguna_Baru;

    // Loop untuk meminta input username yang valid (tanpa spasi dan tidak kosong)
    while (true) {
        cout << " \u2022 Masukkan Username baru >>  ";
        getline(cin >> ws, Pengguna_Baru.username);

        // Memeriksa jika username mengandung spasi atau kosong
        if (Pengguna_Baru.username.find(' ') == string::npos && !Pengguna_Baru.username.empty()) {
            break; // Jika memenuhi syarat, keluar dari perulangan
        } else {
            cout << " [ERROR]: Username tidak boleh kosong atau mengandung spasi. Silakan coba lagi." << endl;
        }
    }

    // Memeriksa apakah username sudah digunakan sebelumnya
    bool username_ada = false;
    for (const User &user : users) {
        if (user.username == Pengguna_Baru.username) {
            username_ada = true;
            break;
        }
    }

    // Menampilkan pesan kesalahan jika username sudah ada
    if (username_ada) {
        cout << WARNA_MERAH << "[ERROR] : "<< WARNA_RESET << " Username sudah digunakan. "<< WARNA_MERAH << "Tambahkan akun gagal."<< WARNA_RESET << endl;
        return;
    }

    // Meminta input untuk password baru
    cout << " \u2022 Masukkan Password baru >> ";
    cin >> Pengguna_Baru.password;
    
    // Loop untuk meminta input role yang valid (pelanggan/kasir)
    do {
        cout << "\u2022 Pilih role baru (pelanggan/kasir) >>  ";
        cin >> Pengguna_Baru.role;

        // Memeriksa apakah role yang dimasukkan valid
        if (Pengguna_Baru.role == "pelanggan" || Pengguna_Baru.role == "kasir") {
            cout << WARNA_HIJAU << "[BERHASIL] : "<< WARNA_RESET << " Role berhasil ditambahkan." << endl;
        } else {
            cout << WARNA_MERAH << "[ERROR] : "<< WARNA_RESET << " Pilih role yang "<<WARNA_HIJAU+BOLD <<" valid "<< WARNA_P+BOLD << "(pelanggan/kasir)." << WARNA_RESET << endl;
        }
    } while (Pengguna_Baru.role != "pelanggan" && Pengguna_Baru.role != "kasir");

    // Jika role adalah pelanggan, meminta input saldo awal
    if (Pengguna_Baru.role == "pelanggan") {
        cout << " \u2022 Masukkan saldo awal >>  Rp. ";
        cin >> Pengguna_Baru.saldo;
    } else {
        // Jika role adalah kasir, saldo diatur menjadi 0
        Pengguna_Baru.saldo = 0; 
    }

    // Menambahkan pengguna baru ke vektor pengguna
    users.push_back(Pengguna_Baru);
    
    // Menampilkan pesan berhasil jika akun berhasil ditambahkan
    cout << WARNA_HIJAU << BOLD << "[BERHASIL] : "<<WARNA_RESET << "Akun baru berhasil "<< WARNA_HIJAU << BOLD << "ditambahkan." <<WARNA_RESET<< endl;
}


// Menampilkan daftar akun, meminta input untuk memilih akun yang akan diubah
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

// Menampilkan daftar akun, meminta input untuk memilih akun yang akan dihapus
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

/*
Deskripsi Fungsi Fitur_SlideText:

Fungsi ini digunakan untuk menampilkan teks dengan efek sliding text, yaitu karakter demi karakter muncul satu per satu.

Parameter:
- teks: String yang akan ditampilkan dengan efek sliding text.

Langkah-langkah:
1. Loop melalui setiap karakter dalam string teks.
2. Tampilkan karakter tersebut ke layar menggunakan cout.
3. Flush output stream menggunakan cout.flush() untuk memastikan karakter langsung terlihat di layar.
4. Gunakan sleep_for untuk memberi jeda 1 milidetik antara setiap karakter.
5. Setelah selesai menampilkan semua karakter, tambahkan baris baru dengan cout << endl.

Catatan:
- Fungsi ini memberikan efek visual menarik dengan menampilkan teks secara bertahap.
- Penggunaan sleep_for memungkinkan jeda antara setiap karakter, jadi ada efek sliding text.
*/
void Fitur_SlideText(const string& teks) {
    for (char karakter : teks) {
        cout << karakter;
        cout.flush(); // Memastikan output langsung terlihat
        this_thread::sleep_for(chrono::milliseconds(1)); 
    }
    cout << endl; // Memberikan baris baru setelah selesai menampilkan slide
}


/*
Alur Program Tampilan Pelanggan:

1. Inisialisasi variabel VarInput_Pelanggan dan masuk ke dalam loop utama.
2. Tampilkan menu pelanggan menggunakan Fitur_SlideText untuk memberikan efek sliding text.
3. Baca input VarInput_Pelanggan dari pengguna.
4. Lakukan pemeriksaan apakah input berupa angka, jika tidak tampilkan pesan kesalahan dan lanjut ke iterasi berikutnya.
5. Gunakan switch-case untuk menangani berbagai pilihan menu pelanggan.
   a. Jika VarInput_Pelanggan = 1, tampilkan pesanan pelanggan dengan Pesanan_Tampilkan().
   b. Jika VarInput_Pelanggan = 2, tampilkan menu dan tambahkan pesanan baru dengan Pesanan_Tambah().
   c. Jika VarInput_Pelanggan = 3, minta input kategori dan tampilkan menu berdasarkan kategori dengan Menu_Tampilkan_Berdasarkan_Kategori().
   d. Jika VarInput_Pelanggan = 4, lakukan pembayaran pesanan dengan Pesanan_Pembayaran().
   e. Jika VarInput_Pelanggan = 5, tampilkan saldo pelanggan dengan Tampilan_Saldo().
   f. Jika VarInput_Pelanggan = 0, tampilkan konfirmasi logout dan kembalikan true jika pengguna yakin ingin logout.
   g. Jika VarInput_Pelanggan tidak sesuai dengan pilihan yang ada, tampilkan pesan kesalahan dan lanjut ke iterasi berikutnya.
6. Jika pengguna memilih logout, kembalikan true untuk keluar dari loop dan logout pengguna.
7. Jika pengguna memilih pilihan lainnya, lanjutkan ke iterasi berikutnya.

*/


// Fungsi untuk menampilkan tampilan pelanggan
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
        Fitur_SlideText("| " + string(2, ' ') + "\033[37m5. Saldo\033[33m" + string(13, ' ') + " |");
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
            	// Menampilkan pesanan pelanggan
                Fitur_bersihkan_layar();
                Pesanan_Tampilkan();
                Fitur_pause_layar();
                break;
            case 2:
            	{
            	// Menambah pesanan baru
                Fitur_bersihkan_layar();
                Menu_Tampilkan();
                Pesanan* pesananBaru = Pesanan_Tambah(&front, &rear);
                Fitur_pause_layar();
                break;
            }
            // Mencari menu berdasarkan kategori
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
            	// Melakukan pembayaran
            	Fitur_bersihkan_layar();
                Pesanan_Pembayaran(&front, &rear);
                Fitur_pause_layar();
                break;
            case 5:
            	// Menampilkan saldo pelanggan
                Fitur_bersihkan_layar();
                Tampilan_Saldo();
                Fitur_pause_layar();
                break;
            case 0:
            	// Logout pelanggan
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

/*
Alur Program Tampilan Kasir:

1. Inisialisasi variabel VarInput_Kasir dan masuk ke dalam loop utama.
2. Tampilkan menu kasir menggunakan Fitur_SlideText untuk memberikan efek sliding text.
3. Baca input VarInput_Kasir dari pengguna.
4. Lakukan pemeriksaan apakah input berupa angka, jika tidak tampilkan pesan kesalahan dan lanjut ke iterasi berikutnya.
5. Gunakan switch-case untuk menangani berbagai pilihan menu kasir.
   a. Jika VarInput_Kasir = 1, konfirmasi pesanan dengan Pesanan_Konfirmasi().
   b. Jika VarInput_Kasir = 2, tampilkan menu dengan Menu_Tampilkan().
   c. Jika VarInput_Kasir = 3, tambahkan menu baru dengan Menu_Buat().
   d. Jika VarInput_Kasir = 4, ubah menu dengan Menu_Ubah().
   e. Jika VarInput_Kasir = 5, hapus menu dengan Menu_Hapus().
   f. Jika VarInput_Kasir = 6, tampilkan pesanan dengan Pesanan_Seluruh_Pelanggan().
   g. Jika VarInput_Kasir = 0, tampilkan konfirmasi logout dan kembalikan true jika pengguna yakin ingin logout.
   h. Jika VarInput_Kasir tidak sesuai dengan pilihan yang ada, tampilkan pesan kesalahan dan lanjut ke iterasi berikutnya.
6. Jika pengguna memilih logout, kembalikan true untuk keluar dari loop dan logout pengguna.
7. Jika pengguna memilih pilihan lainnya, lanjutkan ke iterasi berikutnya.

*/

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


/*
Alur Program Tampilan Admin:

1. Inisialisasi variabel VarInput_Admin dan masuk ke dalam loop utama.
2. Tampilkan menu admin menggunakan Fitur_SlideText untuk memberikan efek sliding text.
3. Baca input VarInput_Admin dari pengguna.
4. Lakukan pemeriksaan apakah input berupa angka, jika tidak tampilkan pesan kesalahan dan lanjut ke iterasi berikutnya.
5. Gunakan switch-case untuk menangani berbagai pilihan menu admin.
   a. Jika VarInput_Admin = 1, tampilkan daftar akun dengan Admin_Tampilan_LihatAkun().
   b. Jika VarInput_Admin = 2, tambahkan akun baru dengan Admin_Tambah_Akun().
   c. Jika VarInput_Admin = 3, edit akun dengan Admin_Edit_Akun().
   d. Jika VarInput_Admin = 4, hapus akun dengan Admin_Hapus_Akun().
   e. Jika VarInput_Admin = 0, tampilkan konfirmasi logout dan kembalikan true jika pengguna yakin ingin logout.
   f. Jika VarInput_Admin tidak sesuai dengan pilihan yang ada, tampilkan pesan kesalahan dan lanjut ke iterasi berikutnya.
6. Jika pengguna memilih logout, kembalikan true untuk keluar dari loop dan logout pengguna.
7. Jika pengguna memilih pilihan lainnya, lanjutkan ke iterasi berikutnya.

*/


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


// Fungsi untuk proses pendaftaran pengguna
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

// Fungsi untuk memproses login pengguna atau admin cabang
bool Proses_Login(int cabangChoice) {
    const char BACKSPACE = 8;
    const char ENTER = 13;
    char ch = ' ';

    // Tampilan awal
    cout << WARNA_BIRU << BOLD << "==============================================" << endl;
    cout << "|           Selamat datang di Warmindo        |" << endl;
    cout << "==============================================" << WARNA_RESET << endl;

    // Input username
    string username, password;
    cout << BOLD << " \u2022 Masukkan Username >>  ";
    cin >> username;

    // Input password dengan menyembunyikan karakter menggunakan simbol *
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
        cout << WARNA_BIRU << "\n\n===================================================" << endl;
        cout << "|          Terima kasih, " << BOLD << WARNA_RESET << setw(25) << username << WARNA_BIRU <<  "|" << endl;
        cout << "|         Login berhasil. Selamat datang!         |" << endl;
        cout << "===================================================" << WARNA_RESET << endl;
        cout << BOLD << WARNA_HIJAU << "[BERHASIL] : " << WARNA_RESET << "Login" << BOLD << WARNA_HIJAU << " berhasil " << WARNA_RESET << "sebagai " << BOLD << loggedInUser->role << endl;
        currentUser = loggedInUser; // Atur currentUser sesuai pengguna yang saat ini login
        Fitur_pause_layar();
        return true;
    } else {
        for (Cabang& cabang : cabangs) {
            if (cabang.id_cabang == cabangChoice && cabang.username == username && cabang.password == password) {
                currentAdminCabang = &cabang;
                cout << WARNA_BIRU << "\n\n===================================================" << endl;
                cout << "|          Terima kasih, " << BOLD << WARNA_RESET << setw(25) << username << WARNA_BIRU <<  "|" << endl;
                cout << "|         Login berhasil. Selamat datang!         |" << endl;
                cout << "===================================================" << WARNA_RESET << endl;
                cout << BOLD << WARNA_HIJAU << "[BERHASIL] : " << WARNA_RESET << " Login " << WARNA_HIJAU + BOLD << "berhasil " << WARNA_RESET << "sebagai Admin Cabang" << endl;
                Fitur_pause_layar();
                return true;
            } else if (cabang.id_cabang != cabangChoice && cabang.username == username && cabang.password == password) {
                cout << "\n" << WARNA_MERAH << "[ERROR] : " << "\033[37m:Kamu bukan pemilik cabang, " << WARNA_MERAH + BOLD << "akses ditolak!" << WARNA_RESET << endl;
                Fitur_pause_layar();
                return false;
            }
        }
    }

    cout << "\n" << WARNA_MERAH << "[ERROR] : " << "\033[37m: Login Gagal, periksa kembali Username dan Password." << WARNA_RESET << endl;
    Fitur_pause_layar();
    return false;
}






/*
Program Utama:

1. Program dimulai dengan memberikan pilihan kepada pengguna untuk memilih cabang tempat kegiatan penjualan akan dilakukan.
   - Pengguna diminta untuk memilih cabang dengan memasukkan nomor cabang.
   - Setelah memilih cabang, program menampilkan informasi bahwa pengguna berada di cabang tersebut.

2. Setelah memilih cabang, pengguna diminta untuk melakukan login.
   - Pengguna diminta memasukkan username dan password.
   - Jika login berhasil, pengguna akan diarahkan ke menu tampilan sesuai dengan peran atau role pengguna (admin/kasir).

3. Menu Utama:
   - Pengguna dapat memilih beberapa opsi utama:
      a. Login (Memasukkan username dan password)
      b. Register (Membuat akun baru)
      c. Exit (Keluar dari program)

Fitur dan Library Penggunaan:

1. Pada Line 1494:
   - Penggunaan #include windows.h adalah untuk mendukung ANSI atau UNICODE di terminal, memungkinkan penggunaan simbol bisa support .

2. Pada Line 1495:
   - Membaca isi dari file menu.txt untuk mendapatkan data menu yang akan ditampilkan atau diubah dalam program.

3. Pada penggunaan setw():
   - Library #include <iomanip> digunakan untuk mengatur jarak atau lebar whitespace dalam tampilan output.

Error Handling:

1. Kesalahan dalam Memilih Cabang:
   - Jika pengguna salah memasukkan nomor cabang, program akan meminta input ulang sampai cabang yang dipilih benar.

2. Kesalahan Memilih Menu Utama:
   - Jika pengguna memasukkan huruf atau pilihan yang tidak valid pada menu utama, program akan melakukan perulangan hingga input yang valid diberikan.

3. Kesalahan Memilih Menu yang Diluar Pilihan:
   - Jika pengguna memasukkan angka yang tidak terdapat dalam pilihan menu utama, program akan meminta input ulang hingga pilihan yang valid diberikan.

Catatan: Penjelasan ini memberikan gambaran umum tentang bagaimana program diorganisir dan menangani kesalahan selama eksekusi.
*/


// Fungsi main() untuk menjalankan program utama
int main() {
	SetConsoleOutputCP(CP_UTF8);

	// Membaca data dari file menu.txt
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
    
    // Loop untuk memilih cabang
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
    	
    	// Error handling untuk input yang tidak valid
    	if (cin.fail()) {
			cout << "\n" << WARNA_MERAH << "[ERROR] : " << WARNA_RESET << ": Hanya angka!" << WARNA_RESET << endl;
            cin.clear();
            Fitur_pause_layar();
            continue;
        }
        
        // Memilih cabang yang benar
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

    
	// Loop untuk menampilkan menu utama
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
        
        // Error handling untuk input yang tidak valid
		if (cin.fail()) {
			cout << "\n" << WARNA_MERAH << "[ERROR] : " << WARNA_RESET << ": Hanya angka!" << WARNA_RESET << endl;
            cin.clear();
            Fitur_pause_layar();
            continue;
        }
        
        // Menjalankan aksi sesuai pilihan menu
        if (menuChoice == 1) {
        	Fitur_bersihkan_layar();
            bool loggedIn = Proses_Login(cabangChoice);
            if (loggedIn) {
            	// Menentukan tindakan berdasarkan peran/role pengguna yang login
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
        	// Proses registrasi pengguna baru
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
