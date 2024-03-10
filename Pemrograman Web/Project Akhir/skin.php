<?php
include('FUNCTION/koneksi.php'); //agar index terhubung dengan database, maka koneksi sebagai penghubung harus di include

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

    table {
      border: solid 1px #DDEEEE;
      border-collapse: collapse;
      border-spacing: 0;
      width: 90%;
      margin: 10px auto 10px auto;
    }

    table thead th {
      background-color: #DDEFEF;
      border: solid 1px #DDEEEE;
      color: #336B6B;
      padding: 10px;
      text-align: left;
      text-shadow: 1px 1px 1px #fff;
      text-decoration: none;
    }

    table tbody td {
      border: solid 1px #DDEEEE;
      color: #333;
      padding: 10px;
      text-shadow: 1px 1px 1px #fff;
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
    <h1>Data Skin</h1>
    <center>
      <center><a href="FUNCTION/tambah_produk.php">+ &nbsp; Tambah Produk</a>
        <center>
          <br />
          <p>
            <?php date_default_timezone_set("Asia/Makassar");
            echo date("l, Y F d, H:i:s") ?>
          </p>

          <table>
            <thead>
              <tr>
                <th>No</th>
                <th>Nama Skin</th>
                <th>Harga</th>
                <th>Gambar</th>
                <th>Action</th>
              </tr>
            </thead>
            <tbody>
              <?php
              // jalankan query untuk menampilkan semua data diurutkan berdasarkan 
              $query = "SELECT * FROM skin ORDER BY id_skin ASC";
              $result = mysqli_query($conn, $query);
              //mengecek apakah ada error ketika menjalankan query
              if (!$result) {
                die("Query Error: " . mysqli_errno($conn) .
                  " - " . mysqli_error($conn));
              }


              $no = 1;

              while ($row = mysqli_fetch_assoc($result)) {
                ?>
                <tr>
                  <td>
                    <?php echo $no; ?>
                  </td>
                  <td>
                    <?php echo $row['nama']; ?>
                  </td>
                  <td>$
                    <?php echo $row['harga']; ?>
                  </td>
                  <td style="text-align: center;"><img src="Gambar/<?php echo $row['gambar']; ?>" style="width: 120px;">
                  </td>
                  <td>
                    <a href="edit_produk.php?id=<?php echo $row['id_skin']; ?>">Edit</a> |
                    <a href="FUNCTION/proses_hapus.php?id=<?php echo $row['id_skin']; ?>"
                      onclick="return confirm('Anda yakin akan menghapus data ini?')">Hapus</a>
                  </td>
                </tr>

                <?php
                $no++;
              }
              ?>
            </tbody>
          </table>

          <div class="back">
            <a href="halamanadmin.php"><-- &nbsp; Back</a>
          </div>

</body>

</html>