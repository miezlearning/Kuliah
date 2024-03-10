<?php
include 'koneksi.php';
// header("Location: ../halamanad   min.php");

date_default_timezone_set('Asia/Makassar');

if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['submit'])) {
    $username = $_POST['new_username'];
    $password = $_POST['new_password'];

    $image = $_FILES['user_image']['name'];
    $image = preg_replace('/\s+/', '_', $image);
    $directory = "../Gambar/gambar_pengguna/";

    $extension = pathinfo($image, PATHINFO_EXTENSION); // Mendapatkan ekstensi gambar
    $currentDate = date("Y-m-d");
    $newImageName = $currentDate . ' ' . $username . '.' . $extension;

    if (move_uploaded_file($_FILES['user_image']['tmp_name'], $directory . $newImageName)) {
        $username = mysqli_real_escape_string($conn, $username);
        $password = mysqli_real_escape_string($conn, $password);

        $insert_query = "INSERT INTO user (username, password, user_image) VALUES ('$username', '$password', '$newImageName')";

        if ($conn->query($insert_query) === true) {
            header('Location: ../halamanadmin.php');
            exit;
        } else {
            echo "Error: " . $insert_query . "<br>" . $conn->error;
        }
    } else {
        echo "Gagal mengunggah file gambar.";
    }
}

if (isset($_POST['update'])) {
    $userId = $_POST['user_id'];
    $newUsername = $_POST['new_username'];
    $newPassword = $_POST['new_password'];

    // Proses gambar yang diunggah
    $userImage = $_FILES['user_image']['name'];
    $userImage = preg_replace('/\s+/', '_', $userImage);
    $targetDirectory = "../Gambar/gambar_pengguna/";

    // Jika file gambar baru diunggah, tentukan nama file yang unik
    if ($_FILES['user_image']['error'] === UPLOAD_ERR_OK) {
        $currentDate = date("Y-m-d");
        $extension = pathinfo($userImage, PATHINFO_EXTENSION); // Mendapatkan ekstensi gambar
        $userImage = $currentDate . ' ' . $newUsername . '.' . $extension;

        // Pindahkan gambar ke direktori yang ditentukan
        move_uploaded_file($_FILES['user_image']['tmp_name'], $targetDirectory . $userImage);
    }

    // Update data pengguna ke database termasuk gambar jika file gambar diunggah
    if (isset($userImage) && $_FILES['user_image']['error'] === UPLOAD_ERR_OK) {
        $update_query = "UPDATE user SET username = '$newUsername', password = '$newPassword', user_image = '$userImage' WHERE id = $userId";
    } else {
        // Update data pengguna ke database tanpa mengubah gambar jika tidak ada file gambar yang diunggah
        $update_query = "UPDATE user SET username = '$newUsername', password = '$newPassword' WHERE id_user = $userId";
    }

    if ($conn->query($update_query) === true) {
        header('Location: ../halamanadmin.php');
        exit;
    } else {
        echo "Error: " . $update_query . "<br>" . $conn->error;
    }
}



if (isset($_POST['delete'])) {
    $userId = $_POST['user_id'];

    // Hapus data pengguna dari database
    $delete_query = "DELETE FROM user WHERE id_user = $userId";

    if ($conn->query($delete_query) === true) {
        // Hapus gambar terkait jika ada
        // Anda perlu mengambil nama gambar sebelum menghapus data pengguna
        // Misalnya, jika Anda menyimpan nama gambar dalam database
        // dan kemudian menghapusnya dari direktori

        header('Location: ../halamanadmin.php');
        exit;
    } else {
        echo "Error: " . $delete_query . "<br>" . $conn->error;
    }
}