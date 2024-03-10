<?php
session_start();

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $username = $_POST['username'];
    $password = $_POST['password'];

    include 'koneksi.php';

    // Validate login for regular users
    $sql = "SELECT * FROM user WHERE username = '$username' AND password = '$password'";
    $result = $conn->query($sql);
    if ($result->num_rows == 1) {
        $row = $result->fetch_assoc();
        session_start();
        
        if ($username === 'admin' && $password === 'admin') {
            // Login sebagai admin
            $_SESSION['username'] = $username;
            $_SESSION['success_message'] = "Login berhasil sebagai admin.";
            header('Location: ../halamanadmin.php');
            exit();
        } else {
            // Login berhasil selain sebagai admin
            $_SESSION['id_user'] = $row['id_user']; // assuming user ID is stored in the 'id_user' column
            $_SESSION['username'] = $row['username'];
            $_SESSION['success_message'] = "Login berhasil.";
            header('Location: ../index.php');
            exit();
        }
    } else {
        // Login gagal
        session_start();
        $_SESSION['error_message'] = "Username atau password salah. Coba lagi.";
        header('Location: ../login.php');
        exit();
    }
    

    $conn->close();
}
?>
