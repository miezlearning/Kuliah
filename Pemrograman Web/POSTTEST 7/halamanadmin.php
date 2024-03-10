<?php
session_start();

if (!isset($_SESSION["role"]) || $_SESSION["role"] !== "admin") {
    header("Location: login.php");
    exit();
}
?>


<!-- KEKURANGNA PROGRAM INI, TIDAK MENGGUNAKAN ROLE -->
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Admin Dashboard</title>
    <link rel="stylesheet" href="CSS/halamanadmin.css">
</head>

<body>
    <h1>Admin Dashboard <a href="FUNCTION/logout.php">Logout</a></h1>

    <!-- Tambah Pengguna Form -->
    <h2>Tambah Pengguna</h2>
    <form method="post" action="FUNCTION/admin.php" enctype="multipart/form-data">
        <label for="new_username">Username:</label>
        <input type="text" name="new_username" id="new_username" required>
        <label for="new_password">Password:</label>
        <input type="password" name="new_password" id="new_password" required>
        <label for="user_image">Gambar Pengguna:</label>
        <input type="file" name="user_image" id="user_image" accept="image/*">
        <button type="submit" name="submit">Tambah</button>
    </form>

    <!-- Tampilkan Data Pengguna -->
    <h2>Data Pengguna</h2>
    <p>
        <?php
        $hari = array("Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu");
        $bulan = array("Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember");
        $currentDateTime = new DateTime("now", new DateTimeZone('Asia/Makassar'));
        $dayIndex = $currentDateTime->format('w');
        $formattedDate = $hari[$dayIndex] . ", " . $currentDateTime->format('d') . " " . $bulan[intval($currentDateTime->format('m')) - 1] . " " . $currentDateTime->format('Y');
        echo "Hari: " . $formattedDate . "<br>";
        echo "Zona Waktu: " . $currentDateTime->format('T') . "<br>";
        ?>
    </p>
    <table>
        <tr>
            <th>ID</th>
            <th>Username</th>
            <th>Password</th>
            <th>Gambar</th>
            <th>Action</th>
        </tr>
        <?php
        include 'FUNCTION/koneksi.php';
        $query = "SELECT * FROM posttest";
        $result = $conn->query($query);
        while ($row = $result->fetch_assoc()) {
            if ($row['username'] === 'admin' && $row['password'] === 'admin') {
                continue;
            } else {
                echo "<tr>";
                echo "<td>" . $row['id'] . "</td>";
                echo "<td>" . $row['username'] . "</td>";
                echo "<td>" . $row['password'] . "</td>";
                echo "<td><img src='Gambar/gambar_pengguna/" . $row['user_image'] . "' width='100' alt='Tidak ada Gambar' height='100'></td>";
                echo '<td>
                <form method="post" action="FUNCTION/admin.php" enctype="multipart/form-data">
                    <input type="hidden" name="user_id" value="' . $row['id'] . '">
                    <input type="text" name="new_username" placeholder="Edit Username" value="' . $row['username'] . '" required>
                    <input type="password" name="new_password" placeholder="Edit Password" value="' . $row['password'] . '" required>
                    <input type="file" name="user_image" accept="image/*">
                    <input type="hidden" name="user_image_existing" value="' . $row['user_image'] . '">
                    <button type="submit" name="update">Edit</button>
                    <button type="submit" name="delete">Hapus</button>
                </form>
            </td>';
                echo "</tr>";
            }
        }
        ?>
    </table>
</body>

</html>