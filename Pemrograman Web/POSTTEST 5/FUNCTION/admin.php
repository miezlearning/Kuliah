<?php
include 'koneksi.php';

if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['submit'])) {
    $newUsername = $_POST['new_username'];
    $newPassword = $_POST['new_password'];

    // Lakukan validasi data yang diinput

    // Tambahkan data pengguna baru ke database
    $insert_query = "INSERT INTO posttest (username, password) VALUES ('$newUsername', '$newPassword')";

    if ($conn->query($insert_query) === true) {
        // Redirect kembali ke halaman admin setelah menambahkan pengguna baru
        header('Location: ../halamanadmin.php');
        exit;
    } else {
        echo "Error: " . $insert_query . "<br>" . $conn->error;
    }
}

if (isset($_POST['update'])) {
    $userId = $_POST['user_id'];
    $newUsername = $_POST['new_username'];
    $newPassword = $_POST['new_password'];

    // Lakukan validasi data yang diinput

    // Update data pengguna ke database
    $update_query = "UPDATE posttest SET username = '$newUsername', password = '$newPassword' WHERE id = $userId";

    if ($conn->query($update_query) === true) {
        // Redirect kembali ke halaman admin setelah mengupdate pengguna
        header('Location: ../halamanadmin.php');
        exit;
    } else {
        echo "Error: " . $update_query . "<br>" . $conn->error;
    }
}

if (isset($_POST['delete'])) {
    $userId = $_POST['user_id'];

    // Hapus data pengguna dari database
    $delete_query = "DELETE FROM posttest WHERE id = $userId";

    if ($conn->query($delete_query) === true) {
        // Redirect kembali ke halaman admin setelah menghapus pengguna
        header('Location: ../halamanadmin.php');
        exit;
    } else {
        echo "Error: " . $delete_query . "<br>" . $conn->error;
    }
}



?>