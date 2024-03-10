<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $username = $_POST['username'];
    $password = $_POST['password'];
    $confirm_password = $_POST['confirm_password'];

    // Validasi input
    if ($password !== $confirm_password) {
        echo "Kata sandi tidak cocok. Coba lagi.";
    } else {
        // Simpan data pengguna ke database (gunakan koneksi database Anda di sini)
        // Misalnya, Anda dapat menyimpannya dalam tabel "users" dengan kolom "username" dan "password"

       include 'koneksi.php';

        // Lakukan pengecekan apakah username sudah digunakan atau belum
        $check_query = "SELECT * FROM posttest WHERE username = '$username'";
        $check_result = $conn->query($check_query);

        if ($check_result->num_rows > 0) {
            echo "Username sudah digunakan. Pilih username lain.";
            header('Location: ../daftar.php');
        } else {
            // Jika username belum digunakan, lakukan penyimpanan data pengguna ke database
            $insert_query = "INSERT INTO posttest (username, password) VALUES ('$username', '$password')";

            if ($conn->query($insert_query) === true) {
                echo "Pendaftaran berhasil. Silakan login.";
                header('Location: ../index.php');
            } else {
                echo "Error: " . $insert_query . "<br>" . $conn->error;
            }
        }

        $conn->close();
    }
}
?>
