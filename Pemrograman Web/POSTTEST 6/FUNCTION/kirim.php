<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  $name = $_POST['name'];
  $email = $_POST['email'];
  $message = $_POST['message'];

  // Lakukan sesuatu dengan data yang diterima, misalnya, simpan ke database

  // Kirim pesan respons
  $response = "Terima kasih, $name! Pesan Anda telah diterima.";
  echo $response;
}
?>