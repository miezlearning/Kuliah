<?php

include('koneksi.php');

$id = $_GET['id'];
$query = "DELETE FROM skin WHERE id_skin = '$id'";
$result = mysqli_query($conn, $query);

if (!$result) {
  die("Query gagal dijalankan: " . mysqli_errno($conn) .
    " - " . mysqli_error($conn));
} else {
  echo "<script>alert('Data berhasil dihapus.');window.location='../skin.php';</script>";
}

?>