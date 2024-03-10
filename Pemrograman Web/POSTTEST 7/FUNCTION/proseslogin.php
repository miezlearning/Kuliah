<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $username = $_POST['username'];
    $password = $_POST['password'];
    


    include 'koneksi.php';

    // Lakukan validasi login
    $sql = "SELECT * FROM posttest WHERE username = '$username' AND password = '$password'";
    $result = $conn->query($sql);

    if ($result->num_rows == 1) {
        session_start();
        $row = $result->fetch_assoc();
        $role = $row['role'];   
        $_SESSION['username'] = $username;
        $_SESSION['role'] = $role;
        
        if ($role === 'admin') {
            header('Location: ../halamanadmin.php');
        } else {
            header('Location: ../index.php');
        }
        exit();
    } else {
        // Login gagal
        echo "Login gagal. Coba lagi.";
    }

    $conn->close();
}


?>
