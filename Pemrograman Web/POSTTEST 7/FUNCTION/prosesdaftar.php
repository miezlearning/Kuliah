<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $username = $_POST['username'];
    $password = $_POST['password'];
    $confirm_password = $_POST['confirm_password'];
    
    if ($password !== $confirm_password) {
        echo "Kata sandi tidak cocok. Coba lagi.";
    } else {
        include 'koneksi.php';
        $check_query = "SELECT * FROM posttest WHERE username = '$username'";
        $check_result = $conn->query($check_query);

        if ($check_result->num_rows > 0) {
            echo "Username sudah digunakan. Pilih username lain.";
            header('Location: ../daftar.php');
        } else {
            $role = "user";
            $insert_query = "INSERT INTO posttest (username, password, role) VALUES ('$username', '$password', '$role')";

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
