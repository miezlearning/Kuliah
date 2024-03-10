package com.pbo;

import java.util.ArrayList;
import java.util.Scanner;

public class App {

    public static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    static Job[] jobs = {
            new Job("Mage", 100, 50, 10, 20),
            new Job("Assassin", 80, 40, 20, 10),
            new Job("Fighter", 120, 60, 15, 15),
            new Job("Paladin", 150, 70, 5, 25)
    };

    static ArrayList<User> data_user = new ArrayList<>();
    static int percobaan = 3;
    static String role = "";
    static User currentUser = null;

    public static void main(String[] args) {
        User akun_akmin = new User("admin", "admin123", "admin");
        data_user.add(akun_akmin);
        menu_utama();

    }

    public static void menu_utama() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Dungeon Master Adventure |  Pilih login sebgai apa!");
        System.out.println("1. Player");
        System.out.println("2. Admin");
        System.out.println("3. Exit Game");
        System.out.print("Choice : ");
        int choice = scanner.nextInt();

        switch (choice) {
            case 1:
                clearScreen();
                player();
                break;
            case 2:
                clearScreen();
                loginAdmin();
                break;
            case 3:
                break;
            default:
                System.out.println("Invalid Choice.");
                menu_utama();
                break;
        }

    }

    public static void admin(User user) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Halo admin!");
        System.out.println("1. Tambah Data Player");
        System.out.println("2. Hapus Data Player");
        System.out.println("3. Edit Data Player");
        System.out.println("4. Lihat Data Player");
        System.out.println("0. Logout");
        System.out.print("Choice : ");
        int choice = scanner.nextInt();

        switch (choice) {
            case 1:
                clearScreen();
                tambahDataPlayer();
                admin(user);
                break;
            case 2:
                clearScreen();
                hapusDataPlayer();
                admin(user);
                break;
            case 3:
                clearScreen();
                editDataPlayer();
                admin(user);
                break;
            case 4:
                clearScreen();
                lihatDataPlayer();
                admin(user);
                break;
            case 0:
                clearScreen();
                menu_utama();
                break;
            default:
                System.out.println("Invalid Choice.");
                admin(user);
                break;
        }

    }

    ////// MENU ADMIN
    public static void tambahDataPlayer() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Tambah Data Player");
        System.out.print("Username Player Baru: ");
        String username = scanner.nextLine();
        System.out.print("Password Player Baru: ");
        String password = scanner.nextLine();
        data_user.add(new User(username, password, "player"));
        System.out.println("Data Player berhasil ditambahkan!");

    }

    public static void hapusDataPlayer() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Hapus Data Player:");
        System.out.print("Masukkan nickname karakter yang akan dihapus: ");
        String nickname = scanner.nextLine();

        boolean found = false;
        for (User user : data_user) {
            Character character = user.getCharacter();
            if (character != null && character.getNickname().equals(nickname)) {
                user.setCharacter(null); // Hapus karakter dari user
                System.out.println("Karakter dengan nickname " + nickname + " berhasil dihapus.");
                found = true;
                break;
            }
        }

        if (!found) {
            System.out.println("Karakter dengan nickname " + nickname + " tidak ditemukan.");
        }

    }

    public static void editDataPlayer() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Edit Data Player:");
        System.out.print("Masukkan nickname karakter yang akan diubah: ");
        String nickname = scanner.nextLine();

        boolean found = false;
        for (User user : data_user) {
            Character character = user.getCharacter();
            if (character != null && character.getNickname().equals(nickname)) {
                found = true;
                System.out.println("Karakter dengan nickname " + nickname + " ditemukan.");
                System.out.println("1. Edit Nickname");
                System.out.println("2. Edit Job");
                System.out.println("0. Kembali");
                System.out.print("Pilihan: ");
                int choice = scanner.nextInt();
                scanner.nextLine();

                switch (choice) {
                    case 1:
                        System.out.print("Masukkan nickname baru: ");
                        String newNickname = inputNickname(scanner);
                        character.setNickname(newNickname);
                        System.out.println("Nickname berhasil diubah.");
                        break;
                    case 2:
                        System.out.println("Pilih Job:");
                        for (int i = 0; i < jobs.length; i++) {
                            System.out.println((i + 1) + ". " + jobs[i].getName());
                        }

                        System.out.print("Pilihan: ");
                        int jobChoice = scanner.nextInt();
                        Job selectedJob = jobs[jobChoice - 1];
                        character.setJob(selectedJob.getName());
                        character.setAttack(selectedJob.getAttack());
                        character.setJob(selectedJob.getMp());
                        character.setHP(selectedJob.getHp());
                        character.setDefense(selectedJob.getDefense());
                        System.out.println("Job berhasil diubah.");
                        break;
                    case 0:
                        return;
                    default:
                        System.out.println("Pilihan tidak valid.");
                }
                break;
            }
        }

        if (!found) {
            System.out.println("Karakter dengan nickname " + nickname + " tidak ditemukan.");
        }

    }

    public static void lihatDataPlayer() {
        System.out.println("Data Player:");
        boolean characterFound = false;
        for (User user : data_user) {
            Character character = user.getCharacter();
            if (character != null) {
                // Tampilkan nickname
                System.out.println("Nickname: " + character.getNickname());
                characterFound = true;
            }
        }

        if (!characterFound) {
            System.out.println("Tidak ada karakter yang terdaftar.");
            return;
        }

        Scanner scanner = new Scanner(System.in);
        System.out.print("Masukkan nickname player yang ingin dilihat detailnya: ");
        String selectedNickname = scanner.nextLine();

        // Cari karakter dengan nickname yang sesuai
        for (User user : data_user) {
            Character character = user.getCharacter();
            if (character != null && character.getNickname().equals(selectedNickname)) {
                System.out.println("Detail Data Player:");
                System.out.println("Username: " + user.getUsername());
                System.out.println("Nickname: " + character.getNickname());
                System.out.println("Job: " + character.getJob());
                System.out.println("HP: " + character.getHp());
                System.out.println("MP: " + character.getMp());
                System.out.println("Attack: " + character.getAttack());
                System.out.println("Defense: " + character.getDefense());
                scanner.close(); // Tutup scanner setelah penggunaan selesai
                return; // Keluar dari metode setelah menemukan karakter yang sesuai
            }
        }
        System.out.println("Nickname tidak ditemukan.");
    }

    /////// BATAS MENU ADMIN
    public static void player() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Selamat datang Traveler!");
        System.out.println("1. Login");
        System.out.println("2. Register");
        System.out.println("0. Kembali");
        System.out.print("Choice : ");
        int choice = scanner.nextInt();

        switch (choice) {
            case 1:
                clearScreen();
                loginPlayer();
                break;
            case 2:
                clearScreen();
                register();
                break;
            case 0:
                menu_utama();
                break;
            default:
                System.out.println("Invalid Choice.");
                player();
                break;
        }

    }

    public static void loginAdmin() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Silakan login sebagai admin.");
        System.out.print("Username: ");
        String username = scanner.nextLine();
        // Fitur kembali
        if (username.equals("kembali")) {
            System.out.println("Kembali ke menu utama...");
            menu_utama();
            return;
        }
        System.out.print("Password: ");
        String password = scanner.nextLine();

        // Cek login
        currentUser = checkLogin(username, password, "admin"); // Berikan role "admin"
        if (currentUser != null && currentUser.getRole().equals("admin")) { // Pengecekan peran admin
            System.out.println("Login berhasil!");
            admin(currentUser);
        } else {
            System.out.println("Username atau password salah atau Anda tidak memiliki izin sebagai admin.");
            menu_utama();
        }

    }

    public static void loginPlayer() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Silakan login sebagai player.");
        System.out.print("Username: ");
        String username = scanner.nextLine();
        // Fitur kembali
        if (username.equals("kembali")) {
            System.out.println("Kembali ke menu utama...");
            menu_utama();
            return;
        }
        System.out.print("Password: ");
        String password = scanner.nextLine();

        // Cek login
        currentUser = checkLogin(username, password, "player"); // Berikan role "player"
        if (currentUser != null) {
            System.out.println("Login berhasil!");
            menuUtama(currentUser);
        }

    }

    public static User checkLogin(String username, String password, String role) {
        for (User user : data_user) {
            if (user.getUsername().equals(username) && user.getPassword().equals(password)) {
                if (role != null && role.equals("admin")) {
                    // Periksa apakah pengguna memiliki peran admin
                    if (user.getRole().equals("admin")) {
                        return user;
                    } else {
                        System.out.println("Anda tidak memiliki izin untuk mengakses sebagai admin.");
                        return null;
                    }
                }
                return user;
            }
        }
        // Pengguna tidak ditemukan, kurangi percobaan login
        percobaan--;
        if (percobaan == 0) {
            clearScreen();
            System.out.println("Anda telah melebihi jumlah percobaan login yang diizinkan.");
            // Jika sudah mencapai 0, akan direset lagi.
            percobaan = 3;
            menu_utama();
        } else {
            clearScreen();
            System.out.println("Username atau password salah. Silakan coba lagi.");
            System.out.println("Percobaan login tersisa : " + percobaan);
            System.out.println("Kamu bisa ketikkan \"kembali\" untuk kembali ke menu utama ");
            // Periksa peran pengguna untuk menentukan tindakan selanjutnya
            if (role != null && role.equals("admin")) {
                loginAdmin(); // Jika role admin, tampilkan menu login admin lagi
            } else {
                loginPlayer(); // Jika role player, tampilkan menu login player lagi
            }
        }
        return null;
    }

    public static void register() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Silakan melakukan pendaftaran.");
        System.out.print("Username: ");
        String username = scanner.nextLine();
        System.out.print("Password: ");
        String password = scanner.nextLine();

        // Cek apakah username sudah digunakan
        boolean usernameExists = false;
        for (User user : data_user) {
            if (user.getUsername().equals(username)) {
                usernameExists = true;
                System.out.println("Username sudah digunakan. Silakan coba username lain.");
                register();
                break;
            }
        }

        if (!usernameExists) {
            data_user.add(new User(username, password, "player"));
            System.out.println("Pendaftaran berhasil!");
            player(); // Setelah mendaftar, arahkan ke menu player
        }

    }

    public static void buatKarakter(User user) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Halo, " + user.getUsername()
                + "! Untuk memulai petualanganmu, mari kita buat karakter terlebih dahulu.");

        // Tampilkan pilihan job
        System.out.println("Pilih Job:");
        for (int i = 0; i < jobs.length; i++) {
            System.out.println((i + 1) + ". " + jobs[i].getName());
        }

        System.out.print("Pilihan: ");
        int jobChoice = scanner.nextInt();
        Job selectedJob = jobs[jobChoice - 1];

        scanner.nextLine();
        String nickname = inputNickname(scanner);

        // Buat karakter baru
        Character newCharacter = new Character(user.getUsername(), nickname, selectedJob.getName(), selectedJob.getHp(),
                selectedJob.getMp(), selectedJob.getAttack(), selectedJob.getDefense());
        user.setCharacter(newCharacter);

        System.out.println("Karakter berhasil dibuat!");
        menuUtama(user);
    }

    public static String inputNickname(Scanner scanner) {
        String nickname;
        boolean nicknameExists;
        do {
            System.out.print("Masukkan Nickname untuk karakter Anda: ");
            nickname = scanner.nextLine();

            // Cek apakah nickname sudah digunakan
            nicknameExists = false;
            for (User u : data_user) {
                Character c = u.getCharacter();
                if (c != null && c.getNickname().equals(nickname)) {
                    nicknameExists = true;
                    System.out.println("Nickname sudah digunakan. Silakan coba lagi.");
                    break;
                }
            }
        } while (nicknameExists);

        return nickname;
    }

    public static void menuUtama(User user) {
        Scanner scanner = new Scanner(System.in);
        Character pengguna = user.getCharacter();
        Menu_Player chara = new Menu_Player();
        if (pengguna == null) {
            System.out.println("Anda belum memiliki karakter. Silakan buat karakter terlebih dahulu.");
            buatKarakter(user);
            return;
        }
        System.out.println("Selamat datang, " + pengguna.getNickname() + "!");
        System.out.println("1. Mulai Petualangan");
        System.out.println("2. Cek Informasi Karakter");
        System.out.println("3. Logout");
        System.out.print("Choice : ");
        int choice = scanner.nextInt();

        switch (choice) {
            case 1:
                System.out.println("Petualangan dimulai! ");

                break;
            case 2:
                clearScreen();
                System.out.println("Informasi Akun : " + pengguna.getNickname());
                chara.cek_info(user);

                break;
            case 3:
                clearScreen();
                System.out.println("Logout berhasil.");
                player();
                break;
            default:
                System.out.println("Invalid Choice.");
                menuUtama(user);
                break;
        }

    }

}

// POSTTEST 1 CHECKPOINT
// =====================
/*
 * INSTRUKSI
 * 
 * Program dapat melakukan CRUD ( Create, Read, Update, Delete ) data dari
 * sebuah ArrayList.
 * 
 * Memiliki menu pilihan dan program dapat berjalan berulang - ulang sampai kita
 * memilih menu exit program.
 * 
 * Data yang dikelola merupakan data dari class sesuai dengan judul masing -
 * masing
 * 
 * PERHATIAN !!!
 * 1. Bersifat individu dan wajib dikerjakan bagi setiap peserta praktikum
 * 2. Kerjakan dengan sungguh-sungguh dan semaksimal mungkin
 * 3. Percaya pada diri sendiri , Tidak perlu mencontek Teman kalian
 * 4. Jika terindikasi meniru teman (hanya ganti tema, hanya ganti variabel,
 * hanya ganti tipe data, hanya ganti tampilan), Keduanya mendapat nilai E.
 * 5. Semangat Mengerjakan
 * 
 * 
 * Dikumpul melalui github, diclassroom hanya link repository terkait
 * 
 * NILAI TAMBAH
 * + Data class yang dikelola lebih dari 2 class
 */
