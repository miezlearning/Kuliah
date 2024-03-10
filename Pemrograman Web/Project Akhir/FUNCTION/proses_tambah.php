<?php
// memanggil file koneksi.php untuk melakukan koneksi database
include 'koneksi.php';

// membuat variabel untuk menampung data dari form
$nama = $_POST['nama'];
$harga = $_POST['harga'];
$gambar = $_FILES['gambar']['name'];


//cek dulu jika ada gambar produk jalankan coding ini
if ($gambar != "") {

  $tanggal_hari_ini = date("Ymd");

  $ekstensi_diperbolehkan = array('png', 'jpg'); //ekstensi file gambar yang bisa diupload 
  $x = explode('.', $_FILES['gambar']['name']); //memisahkan nama file dengan ekstensi yang diupload
  $ekstensi = strtolower(end($x));
  $file_tmp = $_FILES['gambar']['tmp_name'];
  $angka_acak = rand(1, 999);
  $nama_gambar_baru = $tanggal_hari_ini . '-' . $angka_acak . '.' . $ekstensi; //menggabungkan angka acak dengan nama file sebenarnya
  if (in_array($ekstensi, $ekstensi_diperbolehkan) === true) {
    move_uploaded_file($_FILES['gambar']['tmp_name'], '../Gambar/' . $nama_gambar_baru); //memindah file gambar ke folder gambar
    // jalankan query INSERT untuk menambah data ke database pastikan sesuai urutan (id tidak perlu karena dibikin otomatis)
    $query = "INSERT INTO skin (nama, harga, gambar) VALUES ('$nama', '$harga', '$nama_gambar_baru')";
    $result = mysqli_query($conn, $query);
    // periska query apakah ada error
    if (!$result) {
      die("Query gagal dijalankan: " . mysqli_errno($conn) .
        " - " . mysqli_error($conn));
    } else {
      echo "<script>alert('Data berhasil ditambah.');window.location='../skin.php';</script>";
    }

  } else {
    //jika file ekstensi tidak jpg dan png maka alert ini yang tampil
    echo "<script>alert('Ekstensi gambar yang boleh hanya jpg atau png.');window.location='tambah_produk.php';</script>";
  }
} else {
  $query = "INSERT INTO skin (nama, harga, gambar) VALUES ('$nama', '$harga', '$nama_gambar_baru')";
  $result = mysqli_query($conn, $query);
  // periska query apakah ada error
  if (!$result) {
    die("Query gagal dijalankan: " . mysqli_errno($conn) .
      " - " . mysqli_error($conn));
  } else {
    echo "<script>alert('Data berhasil ditambah.');window.location='../skin.php';</script>";
  }
}

?>