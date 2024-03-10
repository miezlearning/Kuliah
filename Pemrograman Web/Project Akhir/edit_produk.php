<?php
include('FUNCTION/koneksi.php');

if (isset($_GET['id'])) {

  $id = $_GET['id'];
  $query = "SELECT * FROM skin WHERE id_skin = '$id' ";
  $result = mysqli_query($conn, $query);

  if (!$result) {
    die("Query Error :" . mysqli_errno($conn) . " - " . mysqli_error($conn));
  }

  $data = mysqli_fetch_assoc($result);

  if (!count($data)) {
    echo "<script>alert('Data tidak ditemukan pada Table');window.location='test.php';</script>";

  }


} else {
  echo "<script>alert('Masukkan ID yang ingin di EDIT');window.location='test.php';</script>";
}


?>
<!DOCTYPE html>
<html>

<head>
  <title>CRUD DATA SKIN</title>
  <style type="text/css">
    * {
      font-family: "Trebuchet MS";
    }

    h1 {
      text-transform: uppercase;
      color: salmon;
    }

    button {
      background-color: salmon;
      color: #fff;
      padding: 10px;
      text-decoration: none;
      font-size: 12px;
      border: 0px;
      margin-top: 20px;
    }

    label {
      margin-top: 10px;
      float: left;
      text-align: left;
      width: 100%;
    }

    input {
      padding: 6px;
      width: 100%;
      box-sizing: border-box;
      background: #f8f8f8;
      border: 2px solid #ccc;
      outline-color: salmon;
    }

    div {
      width: 100%;
      height: auto;
    }

    .base {
      width: 400px;
      height: auto;
      padding: 20px;
      margin-left: auto;
      margin-right: auto;
      background: #ededed;
    }

    a {
      background-color: salmon;
      color: #fff;
      padding: 7.5px;
      text-decoration: none;
      font-size: 12px;
    }

    .back {
      text-align: left;
    }
  </style>
</head>

<body>
  <center>
    <h1>Edit Data
      <?php echo $data['nama']; ?>
    </h1>
    <center>
      <form method="POST" action="FUNCTION/proses_edit.php" enctype="multipart/form-data">
        <section class="base">
          <div>
            <label>Nama Skin</label>
            <input type="text" name="nama" autofocus="" required="" value="<?php echo $data['nama']; ?>" />
            <input type="hidden" name="id" value="<?php echo $data['id_skin']; ?>" />
          </div>
          <div>
            <label>Harga</label>
            <input type="text" name="harga" required="" value="<?php echo $data['harga']; ?>" />
          </div>
          <div>
            <label>Gambar Skin</label>
            <img src="Gambar/<?php echo $data['gambar']; ?>" style="width: 120px;float: left;margin-bottom: 5px;">
            <input type="file" name="gambar" />
            <i style="float: left;font-size: 11px;color: red;">Abaikan jika tidak merubah Gambar Skin</i>
          </div>
          <div>
            <br>
            <button type="submit">Simpan Perubahan</button>
          </div>
        </section>
      </form>
      <div class="back">
        <a href="skin.php"><-- &nbsp; Back</a>
      </div>
</body>

</html>