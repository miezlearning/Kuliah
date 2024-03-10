<?php
// Initialize the variable to store the entered username
$enteredUsername = '';

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $username = $_POST['username'];
    $password = $_POST['password'];
    $confirm_password = $_POST['confirm_password'];

    // Validasi input
    if ($password !== $confirm_password) {
        echo "<script>alert('Kata sandi tidak cocok. Silakan coba lagi.');</script>";
        echo "<script>window.location.href='index.php';</script>";
        exit();
    } else {
        // Simpan data pengguna ke database (gunakan koneksi database Anda di sini)
        // Misalnya, Anda dapat menyimpannya dalam tabel "users" dengan kolom "username" dan "password"

        include 'koneksi.php';

        // Lakukan pengecekan apakah username sudah digunakan atau belum
        $check_query = "SELECT * FROM user WHERE username = '$username'";
        $check_result = $conn->query($check_query);

        if ($check_result->num_rows > 0) {
            // If username is already in use, store it in the variable
            $enteredUsername = $username;
            echo "<script>alert('Username sudah digunakan. Silakan pilih username lain.');</script>";
            echo "<script>window.location.href='../daftar.php';</script>";
            exit();
        } else {
            // Jika username belum digunakan, lakukan penyimpanan data pengguna ke database
            $insert_query = "INSERT INTO user (username, password) VALUES ('$username', '$password')";

            if ($conn->query($insert_query) === true) {
                echo "<script>alert('Pendaftaran berhasil. Silakan login.');</script>";
                echo "<script>window.location.href='../index.php';</script>";
                exit();
            } else {
                echo "Error: " . $insert_query . "<br>" . $conn->error;
            }
        }

        $conn->close();
    }
}
?>
