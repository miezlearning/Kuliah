<?php
session_start();

$user_id = $_SESSION['id_user']; // Sesuaikan dengan cara Anda menyimpan informasi pengguna
unset($_SESSION['id_user']);
unset($_SESSION['cart']);

session_destroy();
header('Location: ../login.php');
exit();
?>
