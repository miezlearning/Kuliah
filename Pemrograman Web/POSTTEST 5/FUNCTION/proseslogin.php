<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $username = $_POST['username'];
    $password = $_POST['password'];

    include 'koneksi.php';

    // Lakukan validasi login
    $sql = "SELECT * FROM posttest WHERE username = '$username' AND password = '$password'";
    $result = $conn->query($sql);

    if ($result->num_rows == 1) {
        $row = $result->fetch_assoc();
        if ($username === 'admin' && $password === 'admin') {
            // Login sebagai admin
            session_start();
            $_SESSION['username'] = $username;
            header('Location: ../halamanadmin.php'); // Arahkan ke halaman admin
            exit();
        } else {
            // Login berhasil selain sebagai admin
            session_start();
            $_SESSION['username'] = $username;
            header('Location: ../index.php'); // Ganti dengan halaman setelah login
            exit();
        }
    } else {
        // Login gagal
        echo "Login gagal. Coba lagi.";
    }

    $conn->close();
}

?>
