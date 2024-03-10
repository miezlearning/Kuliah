<?php
// Koneksi ke database MySQL
$db_host = "localhost";
$db_user = "root"; // Ganti dengan username MySQL Anda
$db_pass = ""; //
$db_name = "posttest"; // Ganti dengan nama database Anda

$conn = new mysqli($db_host, $db_user, $db_pass, $db_name);

if ($conn->connect_error) {
    die("Koneksi ke database gagal: " . $conn->connect_error);
}
?>